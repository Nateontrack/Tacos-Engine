#pragma once
#include <vector>


namespace dae
{
	class GameObject;
	
	template <typename... Args>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Args... args) = 0;
		virtual void OnSubjectDestroy() = 0;
	};

	template <typename... Args>
	class Subject final
	{
	public:
		~Subject()
		{
			for (auto& observer : m_Observers)
			{
				observer->OnSubjectDestroy();
			}
		}

		void AddObserver(Observer<Args...>* observer)
		{
			m_Observers.push_back(observer);
		}

		void RemoveObserver(Observer<Args...>* observer)
		{
			m_Observers.erase(std::remove(
				m_Observers.begin(),
				m_Observers.end(), observer),
				m_Observers.end());
		}

		void Notify(Args... args)
		{
			for (const auto& observer : m_Observers)
			{
				observer->OnNotify(args...);
			}
		}

	private:
		std::vector<Observer<Args...>*> m_Observers;
	};
}
