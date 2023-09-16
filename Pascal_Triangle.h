#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
namespace Pascal
{
	void print(size_t size = 10)
	{
		if (size > 10)
			size = 10;
		{
			auto table{ std::vector<std::vector<int>>{ {1},{1,2,1}} };
			for (size_t i{}; i < 2; i++)
			{
				size_t count{};
				for (auto el : table[i])
				{
					
					if (i == 1 && count)
						std::cout << std::setw(4) << el;
					else
					{
						std::cout << el;
					}
					count++;
				}
				std::cout << std::endl;
			}
		}
		auto table{ std::vector{{1,2,1}} };
		
		for (size_t i{ 1 }; i < size; i++)
		{
			auto current{ std::vector<int>{1} };
			std::cout << *current.begin();
			for (auto it{ size_t{} }; it <table.size() - 1; it++)
			{
				auto el{ table[it] + table[it + 1] };
				current.push_back(el);
				std::cout << std::setw(4) << el;
			}
			current.push_back(1);
			std::cout << std::setw(4) << current.back();
			std::cout << std::endl;
			table = current;
		}
	}
}