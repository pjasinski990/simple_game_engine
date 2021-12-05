#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "recursive_position_correction_solver.h"
#include "../../body.h"

namespace mrld
{
    void RecursivePositionCorrectionSolver::solve(std::vector<collision> &cols, float dt)
    {
        std::vector<collision*> cq;
        cq.reserve(cols.size());
        for (auto &col : cols) {
            cq.push_back(&col);
        }
        solve_all(cq);
    }

    bool RecursivePositionCorrectionSolver::solve_body(
            Body *body,
            Body *previous_other,
            std::unordered_map<Body*, vec3> &body_to_displacement,
            std::unordered_map<Body*, std::vector<collision*>> &body_to_contacts,
            std::unordered_set<collision*> &affected)
    {
        vec3 displacement = body_to_displacement[body];
        for (auto *contact : body_to_contacts[body]) {
            Body *other = contact->b;
            vec3 normal = contact->coll_p.normal * -1.0f;

            float dx_on_normal = displacement.dot(normal);
            // First condition means body's correction is towards other. Second means that if there is a gap between bodies
            // (collision depths negative), the gap will be closed and body will penetrate other.
            if (dx_on_normal > 0.0f && dx_on_normal > -1.0f * contact->coll_p.collision_depth) {
                vec3 displacement_other;
                // other will be displaced only if it is not fixed and is not the same Body that caused displacement of body
                // if this is impossible, recursion is
                if (!other->is_dynamic() || other == previous_other) {
                    return false;
                }
                // if there is a gap, other will be moved only by a fraction of body displacement
                if (contact->coll_p.collision_depth < 0.0f) {
                    displacement_other = displacement * (dx_on_normal + contact->coll_p.collision_depth) / dx_on_normal;
                }
                else {
                    displacement_other = displacement;
                }
                // update displacement of other
                if (!body_to_displacement.contains(other) || displacement_other > body_to_displacement[other]) {
                    body_to_displacement[other] = displacement_other;
                    bool success = solve_body(other, body, body_to_displacement, body_to_contacts, affected);
                    if (!success) { return false; }
                }
            }
            affected.insert(contact);
        }
        return true;
    }

    void RecursivePositionCorrectionSolver::solve_all(std::vector<collision*> &cols)
    {
        std::unordered_map<Body*, std::vector<collision*>> body_to_contacts;
        for (collision *col : cols) {
            body_to_contacts[col->a].push_back(col);
        }

        while (!cols.empty()) {
            collision *col = *cols.begin();
//            if (!col->a->is_dynamic()) {
//                if (col->b->is_dynamic()) {
//                    Body *temp = col->a;
//                    col->a = col->b;
//                    col->b = temp;
//                    collision_point &cp = col->coll_p;
//                    cp.normal = cp.normal * -1.0f;
//                    vec3 temp_vec = cp.a;
//                    cp.a = cp.b;
//                    cp.b = temp_vec;
//                }
//                else {
//                    auto target = std::find(cols.begin(), cols.end(), col);
//                    if (target != cols.end()) {
//                        cols.erase(target);
//                    }
//                    continue;
//                }
//            }

            std::unordered_map<Body*, vec3> body_to_displacement;
            std::unordered_set<collision*> affected;
            Body* body = col->a;
            vec3 displacement = col->coll_p.normal * col->coll_p.collision_depth;
            body_to_displacement[body] = displacement;
            bool success = solve_body(body, nullptr, body_to_displacement, body_to_contacts, affected);

            if (!success) {
                auto target = std::find(cols.begin(), cols.end(), col);
                if (target != cols.end()) {
                    cols.erase(target);
                }
            }
            else {
                std::unordered_set<Body*> affected_bodies;
                for (auto &c : affected) {
                    affected_bodies.insert(c->a);
                }
                for (auto *b : affected_bodies) {
                    if (body_to_displacement.contains(b)) {
                        body->t.position += body_to_displacement[body];
                    }
                }
                for (auto *c: affected) {
                    vec3 displacement_a = body_to_displacement[c->a];
                    vec3 displacement_b = body_to_displacement[c->b];
                    vec3 normal_for_collision = c->coll_p.normal;
                    c->coll_p.a += displacement_a;
                    c->coll_p.b += displacement_b;
                    vec3 diff = c->coll_p.b - c->coll_p.a;
                    c->coll_p.collision_depth = diff.dot(normal_for_collision);
                    c->coll_p.has_collision = c->coll_p.collision_depth > _acceptable_collision_depth;
                    if (!c->coll_p.has_collision) {
                        auto target = std::find(cols.begin(), cols.end(), col);
                        if (target != cols.end()) {
                            cols.erase(target);
                        }
                    }
                    else {
                        c->coll_p.normal = diff.normalized();
                    }
                }
//                for (auto &[body, d] : body_to_displacement) {
//                    body->t.position += d;
//                    for (auto *c : body_to_contacts[body]) {
//                        c->coll_p.a += d;
//                        c->coll_p.collision_depth = (c->coll_p.b - c->coll_p.a).magnitude();
//                        c->coll_p.has_collision = c->coll_p.collision_depth < -5.0f;       // TODO threshold
//                        if (!c->coll_p.has_collision) {
//                            auto target = std::find(cols.begin(), cols.end(), c);
//                            if (target != cols.end()) {
//                                cols.erase(target);
//                            }
//                        }
//                    }
//                }
            }
        }
    }
}
