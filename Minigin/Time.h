#pragma once
#include <memory>
#include <chrono>
#include "Singleton.h"

namespace dae 
{
    class Time final {
    public:

        static Time* GetInstance();
        static void DestroyInstance();
        static int GetInstanceCount();

        void UpdateElapsedTime();
        float GetElapsedSec() const;
        std::chrono::time_point<std::chrono::steady_clock> GetLastTime() const;
        float GetFixedStep() const;
        void StartTiming();

        // To keep the Singleton destructor protected the deleter that the unique_ptr uses,
        // has to be a friend class, to make it have access to the protected and private members
        friend struct std::default_delete<Time>;

    protected:
        ~Time() = default;

    private:
        Time() = default;
        Time(const Time&) = delete;
        Time(Time&&) = delete;
        Time& operator=(const Time&) = delete;
        Time& operator=(Time&&) = delete;

        inline static std::unique_ptr<Time> m_Instance{ nullptr };
        inline static int m_InstanceCount{ 0 };

        float m_ElapsedSec{};
        float m_FixedStep{ 0.0167f };
        std::chrono::time_point<std::chrono::steady_clock> m_LastTime{};
    };
}


