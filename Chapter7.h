#pragma once
#include "RandomString.h"
#include "ParallelTransform.h"
#include <vector>

namespace Chapter7
{
	std::mutex g_mutex;
	void thread_func()
	{
		using namespace std::chrono_literals;
		{
			std::lock_guard<std::mutex> lock(g_mutex);
			std::cout << "running thread "
				<< std::this_thread::get_id() << '\n';
		}
		std::this_thread::yield();
		std::this_thread::sleep_for(2s);
		{
			std::lock_guard<std::mutex> lock(g_mutex);
			std::cout << "done in thread "
				<< std::this_thread::get_id() << '\n';
		}
	}
	void execute()
	{
		//thread_func();
		/*auto func{ [](int& x) {x *= 2; } };
		auto List{ std::vector<int>(10) };
		std::fill(List.begin(), List.end(), 15);
		auto P{ std::vector<int>(13) };
		auto random{ StringGenerate::somestring() };
		int i{0};
		std::generate(P.begin(), P.end(),
			[&random, &i]() {return static_cast<int>(random[(i++) % random.size()]); });
		//auto out{ Parallel::pmin_max(P.begin(),P.end()) };
		//auto out{ Parallel::async_minmax(P.begin(),P.end()) };
		//{ Parallel::async_quick_sort(P.begin(), P.end() - 1); }
		//Parallel::Transform(List.begin(), List.end(), func);
		thread_safe::logscreen();
		auto x{ 1 };*/
		ClientSimulate::simulate();
	}
}