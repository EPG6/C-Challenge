#pragma once
#include <thread>
#include <mutex>
#include <algorithm>
#include <execution>
#include <future>

namespace Parallel
{
	template<typename RanIt, typename F>
	void Transform(RanIt start, RanIt end, F&& func)
	{
		std::for_each(std::execution::par, start, end, func);
	}
	template< typename RanIt>
	auto pmin_max(RanIt start, RanIt end)
	{
		return std::minmax_element(std::execution::par, start, end);
	}
	template< typename RanIt>
	auto async_minmax(RanIt start, RanIt end)
	{
		auto fmin{ std::async(std::launch::async,std::minmax_element<RanIt>,start,end) };
		return fmin.get();
	}
	template< typename RanIt>
	auto partition(RanIt start, RanIt end)
	{
		auto pivot{ start };
		auto left{ pivot + 1 };
		auto right{ end };
		while (true)
		{
			while ((*left) <= (*pivot) && std::distance(left, right) > 0)
				left++;
			while ((*right) > (*pivot) && std::distance(left, right) > 0)
				right--;
			if (left == right)
				break;
			else
				std::iter_swap(left, right);
		}
		if (*pivot > *right)
			std::iter_swap(pivot, right);
		return right;
	}
	template< typename RanIt>
	void async_quick_sort(RanIt start, RanIt end)
	{
		if (std::distance(start, end) >= 1)
		{
			auto part{ partition(start,end) };
			auto fleft = std::async(std::launch::async, async_quick_sort<RanIt>, start, part - 1);
			auto fright = std::async(std::launch::async, async_quick_sort<RanIt>, part, end);
			fleft.wait();
			fright.wait();
		}

	}
}
namespace thread_safe
{
	std::mutex io_mutex;
	void logging(std::string_view text)
	{
		std::lock_guard lock(io_mutex);
		std::cout << "Thread: " << std::this_thread::get_id()
			<< " has info " << text.data() << std::endl;
	}
	void logscreen()
	{
		std::vector<std::thread> Buff;
		for (size_t i{}; i < 5; i++)
		{
			Buff.emplace_back(logging, StringGenerate::somestring());
		}
		for (auto& t : Buff)
			t.join();
	}
}

namespace ClientSimulate
{
	std::mutex counter_mutex, io_mutex;
	size_t counter;
	bool done{ false };
	void serve()
	{
		while(!done)
		{
			size_t itscount;
			{
				std::lock_guard counter_lock(counter_mutex);
				if (counter == 100)
				{
					done = true;
					break;
				}
				counter++;
				itscount = counter;
			}

			{

				{

					std::lock_guard io_lock(io_mutex);
					std::cout << "Thread: " << std::this_thread::get_id()
						<< " Serving client... " << itscount << "...\n";

				}
				{
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(500ms);
					std::lock_guard io_lock(io_mutex);
					std::cout << "Thread: " << std::this_thread::get_id()
						<< " Done with client... " << itscount << "...\n";
				}

			}
		}

	}
	void simulate(size_t clients = 100)
	{
		std::vector<std::thread> Desks;
		for (size_t i{}; i < 3; i++)
		{
			Desks.emplace_back(serve);
		}
		for (auto& desk : Desks)
		{
			desk.join();
		}
	}
}
