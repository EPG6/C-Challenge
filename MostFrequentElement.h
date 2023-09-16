#pragma once
#include <algorithm>
#include <vector>

namespace MostFrequentElement
{
	template<typename T>
	auto mode(std::vector<T> container)
	{
		std::vector<T> elements{};
		std::vector<size_t> frequency{};
		elements.push_back(*container.begin());
		frequency.push_back(1);
		for (auto it{ container.begin() + 1 }; it != container.end(); it++)
		{
			auto index{ std::find(elements.begin(), elements.end(), *it) };
			if ( index != elements.end())
			{
				frequency[std::distance(elements.begin(), index)]++;
			}
			else
			{
				elements.push_back(*it);
				frequency.push_back(1);
			}
		}
		std::vector<std::pair<T, size_t>> Modes{};
		auto max_frq{ std::max_element(frequency.begin(),frequency.end()) };
		for (auto it{ elements.begin()}; it != elements.end(); it++)
		{
			if (frequency[std::distance(elements.begin(), it)] == *max_frq)
			{
				auto tuple{ std::make_pair(*it,*max_frq) };
				Modes.push_back(tuple);
			}
		}
		return Modes;
	}
}