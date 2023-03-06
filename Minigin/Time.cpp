#include "Time.h"

namespace dae
{
    Time* Time::GetInstance()
    {
        if (!m_Instance)
        {
            //dont use make ptr because singleton constructors are private
            m_Instance = std::unique_ptr<Time>{ new Time{} };
            ++m_InstanceCount;
        }

        // Get a non-owning pointer using the get() member function
        return m_Instance.get();
    }

    void Time::DestroyInstance()
    {
        m_Instance.reset();
    }

    int Time::GetInstanceCount()
    {
        return m_InstanceCount;
    }

    

    void Time::UpdateElapsedTime()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - m_LastTime;

        m_ElapsedSec = elapsedTime.count();
        m_LastTime = currentTime;
    }

    float Time::GetElapsedSec() const
    {
        return m_ElapsedSec;
    }

    float Time::GetFixedStep() const
    {
        return m_FixedStep;
    }

    std::chrono::time_point<std::chrono::steady_clock> Time::GetLastTime() const
    {
        return m_LastTime;
    }

    void Time::StartTiming()
    {
        m_LastTime = std::chrono::high_resolution_clock::now();
    }
}
