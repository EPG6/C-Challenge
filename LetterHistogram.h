#pragma once
#include<algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

namespace LetterHisto
{
	void draw(std::string_view text)
	{
		std::vector<char> elements{};
		std::vector<size_t> frequency{};
		elements.push_back(tolower(*text.begin()));
		frequency.push_back(1);
		for (auto it{ text.begin() + 1 }; it != text.end(); it++)
		{
			if(isalpha(*it))
			{
				auto index{ std::find(elements.begin(), elements.end(), tolower(*it) )};
				if (index != elements.end())
				{
					frequency[std::distance(elements.begin(), index)]++;
				}
				else
				{
					elements.push_back(*it);
					frequency.push_back(1);
				}
			}
			else
				continue;
		}
		auto total{ std::accumulate(frequency.begin(),frequency.end(),0) };
		for (int i{total}; i > 0; i -= 5)
		{
			for (const auto& el : frequency)
			{
				if (el >= i)
				{
					std::cout << std::left << std::setw(3) << static_cast<char>(219);
				}
				else
					std::cout << std::left << std::setw(3) << "";
			}
			std::cout << std::endl;
		}
		for (const auto& el : elements)
		{
			std::cout << std::left << std::setw(3) << el;
		}
		std::cout << "\tLetter(s) ";
		std::cout << std::endl;
		for (const auto& el : frequency)
		{
			std::cout << std::left << std::setw(3) << el;
		}
		std::cout << "\tfrequency ";
		std::cout << std::endl;
	}
}