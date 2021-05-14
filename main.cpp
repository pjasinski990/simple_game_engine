#include <iostream>
#include <window/window.h>
#include <input/keyboard_handler.h>
#include <vector>

int main() {
    mrld::Window w("Hello world!", 800, 600);
    std::vector<mrld::KeyCode> v = {mrld::W, mrld::S, mrld::A, mrld::D};
    mrld::KeyboardHandler handler(v);
    while (!w.should_close()) {
        w.update();
    }
    return 0;
}
