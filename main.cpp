#include <iostream>
#include <vector>

#include <window/window.h>
#include <math/vec4.h>
#include <input/keyboard_handler.h>
#include <input/mouse_handler.h>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    std::vector<mrld::KeyCode> keys = {mrld::W, mrld::S, mrld::A, mrld::D};

    mrld::vec4 v(4, 6, 10, -5);
    std::cout << v << std::endl;

    std::cout << v.magnitude() << std::endl;
    std::cout << v.normalized() << std::endl;
    std::cout << v.normalized().magnitude() << std::endl;

    mrld::KeyboardHandler handler(keys);
    mrld::MouseHandler m_handler({mrld::BUTTON_LEFT, mrld::BUTTON_RIGHT});

    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
