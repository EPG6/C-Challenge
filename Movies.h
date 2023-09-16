#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>

namespace Movie
{
	struct movie
	{
		std::string Title{};
		std::vector<unsigned>Ratings{};
	};
	void print_average_ratings(std::vector<movie> List)
	{
		std::cout << std::left << std::setw(16) << "Movie(s)"
			<< std::right << std::setw(16) << "Av. ratings" << std::endl;
		for (auto& el : List)
		{
			auto ratings{ el.Ratings };
			auto limit{ static_cast<unsigned>(ratings.size() * 0.05) };
			for (size_t i{}; i < limit; i++)
			{
				std::pop_heap(ratings.begin(), ratings.end(), std::less());
				ratings.pop_back();
			}
			for (size_t i{}; i < limit; i++)
			{
				std::pop_heap(ratings.begin(), ratings.end(), std::greater());
				ratings.pop_back();
			}
			auto total{ std::accumulate(ratings.begin(), ratings.end(), 0) };
			std::cout << std::left << std::setw(16) << el.Title
				<< std::right << std::setw(16) << std::setprecision(2)
				<< static_cast<double>(total / floor(ratings.size())) << std::endl;
		}
	}
}