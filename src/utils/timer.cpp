#include <chrono>

#include "timer.h"

namespace mrld
{
    void Timer::reset()
    {
        _last_micros = get_now_micros();
        _last_millis = get_now_millis();
    }

    uint64_t Timer::get_now_micros() const
    {
        auto now = std::chrono::system_clock::now();
        auto now_us_time_point = std::chrono::time_point_cast<std::chrono::microseconds>(now);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now_us_time_point.time_since_epoch());
        return duration.count();
    }

    uint64_t Timer::get_now_millis() const
    {
        auto now = std::chrono::system_clock::now();
        auto now_us_time_point = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now_us_time_point.time_since_epoch());
        return duration.count();
    }

    uint64_t Timer::get_elapsed_micros() const
    {
        return get_now_micros() - _last_micros;
    }

    uint64_t Timer::get_elapsed_millis() const
    {
        return get_now_millis() - _last_millis;
    }
}
