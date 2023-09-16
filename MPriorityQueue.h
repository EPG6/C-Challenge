#pragma once
#include<algorithm>
#include <vector>

namespace MyPriorityQueue
{
	template<typename T, typename Container = std::vector<T>, 
		class Func = std::less<T>>
	class PriorityQueue
	{
	public:
		PriorityQueue() = default;
		PriorityQueue(size_t size)
		{
			buffer.resize(size);
		}
		~PriorityQueue() = default;
		void push(T element)
		{
			if (buffer.size() == 0)
			{
				buffer.push_back(element);
				return;
			}
			buffer.push_back(element);
			std::push_heap(buffer.begin(), buffer.end(), cmp);
		}
		void pop() noexcept
		{
			if (buffer.size() == 1)
			{
				buffer.pop_back();
				return;
			}
			std::pop_heap(buffer.begin(), buffer.end(), cmp);
			buffer.pop_back();
		}
		T top() const noexcept
		{
			return buffer.front();
		}

		size_t size() const noexcept
		{
			return buffer.size();
		}

		bool is_empty() const noexcept
		{
			return buffer.size() == 0;
		}

	private:
		Container buffer{};
		Func cmp;
	};

	
}