#include <iostream>
#include <vector>

#include <window/window.h>
#include <math/vec2.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    std::vector<mrld::KeyCode> keys = {mrld::W, mrld::S, mrld::A, mrld::D};

    mrld::vec2 v2(4, 6);
    mrld::vec2 v1(2);
    std::cout << v1 << std::endl;

    std::cout << v2.magnitude() << std::endl;
    std::cout << v2.normalized() << std::endl;
    std::cout << v2.normalized().magnitude() << std::endl;

    mrld::KeyboardHandler handler(keys);
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
