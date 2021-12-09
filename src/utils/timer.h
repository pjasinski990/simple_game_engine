#pragma once

#include <cstdint>
#include <chrono>

namespace mrld
{
    class Timer
    {
    public:
        Timer() { reset(); }
        void reset();
        uint64_t get_elapsed_micros() const;
        uint64_t get_elapsed_millis() const;
    private:
        uint64_t get_now_micros() const;
        uint64_t get_now_millis() const;

        uint64_t _last_millis;
        uint64_t _last_micros;
    };
}
