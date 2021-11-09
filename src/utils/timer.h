#pragma once

#include <cstdint>
#include <chrono>

namespace mrld
{
    class Timer
    {
    public:
        void reset();
        uint64_t get_elapsed_time() const;
    private:
        uint64_t get_now_millis() const;
        uint64_t _last_millis;
    };
}
