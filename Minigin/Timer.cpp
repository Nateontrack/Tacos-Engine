#include "Timer.h"

namespace dae
{
    Timer* Timer::GetInstance()
    {
        if (!m_Instance)
        {
            //dont use make ptr because singleton constructors are private
            m_Instance = std::unique_ptr<Timer>{ new Timer{} };
            ++m_InstanceCount;
        }

        // Get a non-owning pointer using the get() member function
        return m_Instance.get();
    }

    void Timer::DestroyInstance()
    {
        m_Instance.reset();
    }

    int Timer::GetInstanceCount()
    {
        return m_InstanceCount;
    }

    

    void Timer::UpdateElapsedTime()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - m_LastTime;

        m_ElapsedSec = elapsedTime.count();
        m_LastTime = currentTime;
    }

    float Timer::GetElapsedSec() const
    {
        return m_ElapsedSec;
    }

    float Timer::GetFixedStep() const
    {
        return m_FixedStep;
    }

    std::chrono::time_point<std::chrono::steady_clock> Timer::GetLastTime() const
    {
        return m_LastTime;
    }

    void Timer::StartTiming()
    {
        m_LastTime = std::chrono::high_resolution_clock::now();
    }
}
