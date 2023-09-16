#pragma once
#include <chrono>


namespace Time
{
	auto func = [](int x) {return x * 2; };
	template <typename Time = std::chrono::microseconds,
		typename Clock = std::chrono::high_resolution_clock>
	struct perf_timer
	{
		template <typename F, typename... Args>
		static Time duration(F&& f, Args... args)
		{
			auto start = Clock::now();
			std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
			auto end = Clock::now();
			return std::chrono::duration_cast<Time>(end - start);
		}
	};
	void execute()
	{
		auto t = perf_timer<>::duration(func, 100000000);
		std::cout << std::chrono::duration<double, std::milli>(t).count()
			<< "ms" << '\n';
		std::cout << std::chrono::duration<double, std::nano>(t).count()
			<< "ns" << '\n';
	}
}