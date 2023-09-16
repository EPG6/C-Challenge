#pragma once
#include<random>
#include <string>
#include <vector>

namespace StringGenerate
{
	std::string somestring(size_t end = 13)
	{
		using namespace std::string_literals;
		auto List{ std::vector{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"s,
		"abcdefghijklmnopqrstuvwxyz"s,"0123456789"s} };
		std::random_device rd{};
		std::vector<int> seed_data(std::mt19937::state_size);
		std::generate(std::begin(seed_data), std::end(seed_data),
			std::ref(rd));
		std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
		auto eng = std::mt19937{ seq };
		auto dist1{ std::uniform_int_distribution{0,2} };
		auto out{ ""s };
		for (size_t i{}; i < end; i++)
		{
			auto choice{ dist1(eng) };
			auto in{ eng() % List[choice].size() };
			out += List[choice][in];
		}
		return out;
	}
}