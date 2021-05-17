#include <iostream>
#include <vector>

#include <window/window.h>
#include <math/mat4.h>
#include <math/matrix_factory.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    std::vector<mrld::KeyCode> keys = {mrld::W, mrld::S, mrld::A, mrld::D};

    mrld::mat4 matrix = mrld::MatrixFactory::zero();
    std::cout << matrix;
    matrix = mrld::MatrixFactory::identity();
    std::cout << matrix;

    mrld::KeyboardHandler handler(keys);
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
