#pragma once
#include <memory>
#include <atomic>
#include <mutex>

namespace kit
{
	template<typename T>
	class Singleton
	{
	public:
		template<typename... Args>
		static T& getInstance(Args... args)
		{
			static T instance = T(std::forward<Args>(args)...);
			// auto con = constructed.load();
			// if (!con && !instance)
			// {
			// 	std::lock_guard<std::mutex> lock(mtx);
			// 	if (!constructed.load())
			// 	{
			// 		instance = std::make_shared<T>(std::forward<Args>(args)...) ;
			// 		constructed.store(true);
			// 	}

			// }

			return instance;
		}
	
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator= (const Singleton&) = delete;
		Singleton() = default;

	protected:
	
		// static std::shared_ptr<T> instance;
		// static std::mutex mtx;
		// static std::atomic<bool> constructed;

	};
	
// 	template<typename T>
// 	std::shared_ptr<T> Singleton<T>::instance = nullptr;

// 	template<typename T>
// 	std::mutex Singleton<T>::mtx;

// 	template<typename T>
// 	std::atomic<bool> Singleton<T>::constructed = false;
}