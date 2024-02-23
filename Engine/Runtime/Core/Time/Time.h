#pragma once

#include <Windows.h>
#include <cstdint>

namespace Engine::Time
{
    float GetLastFrameTime_ms();
    float CalculateLastFrameTime_ms();

    constexpr float DESIRED_FPS = 60.f;
    constexpr float DESIRED_FRAMETIME_MS = 1000.0f / DESIRED_FPS;
    constexpr float MAX_FRAMETIME_MS = 2 * DESIRED_FRAMETIME_MS;

    extern double pc_frequency_;
    extern double last_frame_start_tick_;
    extern float last_frame_time_ms_;

    inline float GetLastFrameTime_ms()
    {
        if (last_frame_time_ms_ > MAX_FRAMETIME_MS)
        {
            return MAX_FRAMETIME_MS;
        }
        return last_frame_time_ms_;
    }

    inline double GetCounter()
    {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return static_cast<double>(li.QuadPart);
    }

    inline double GetFrequency()
    {
        if (pc_frequency_ <= 0)
        {
            LARGE_INTEGER li;
            QueryPerformanceFrequency(&li);
            pc_frequency_ = static_cast<double>(li.QuadPart) / 1000.0;
        }
        return pc_frequency_;
    }

    inline float CalculateLastFrameTime_ms()
    {
        double current_tick = GetCounter();

        if (last_frame_start_tick_ != 0.f)
        {
            double elapsed_ticks = current_tick - last_frame_start_tick_;

            last_frame_time_ms_ = static_cast<float>(elapsed_ticks / GetFrequency());
        }
        else
        {
            last_frame_time_ms_ = 16.66667f; // 1000ms / 60 
        }

        last_frame_start_tick_ = current_tick;

        return last_frame_time_ms_;
    }
}
