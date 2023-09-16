#pragma once
#include <vector>
#include <algorithm>

namespace Pairwise
{
	template<typename T>
	auto pair_elements(std::vector<T> List)
	{
		auto pairList{ std::vector<std::vector<T>>() };
		if (List.size() % 2 == 0)
		{
			for (auto it{ List.begin() }; it != List.end(); it += 2)
			{
				auto buff{ std::vector<T>() };
				buff.push_back(*it), buff.push_back(*(it + 1));
				pairList.push_back(buff);
			}
		}
		else
		{
			for (auto it{ List.begin() }; it != List.end() - 1; it += 2)
			{
				auto buff{ std::vector<T>() };
				buff.push_back(*it), buff.push_back(*(it + 1));
				pairList.push_back(buff);
			}
		}
		return pairList;
	}
}

namespace my_zip
{
	template<typename T>
	auto zip(std::vector<T> List1, std::vector<T> List2)
	{
		const auto size(std::min(List1.size(), List2.size()));
		auto pairList{ std::vector<std::vector<T>>() };
		for (size_t i{}; i < size; i++)
		{
			auto buff{ std::vector<T>() };
			buff.push_back(List1[i]), buff.push_back(List2[i]);
			pairList.push_back(buff);
		}
		return pairList;
	}
}

namespace Select
{
	template<typename T, typename F>
	auto select(std::vector<T> List, F&& func)
	{
		std::vector<decltype(func(List[0]))> Range;
		for (const auto& el : List)
		{
			auto result{ func(el) };
			Range.push_back(result);
		}
		return Range;
	}
}

namespace nsort
{
	template< typename Ranit,typename F=std::less<>>
	void sort(Ranit first, Ranit last)
	{
		F func{};
		std::sort(first, last, func);
	}
	template<typename Ranit, typename F>
	void sort(Ranit first, Ranit last, F&& Func)
	{
		std::sort(first, last, Func);
	}
}