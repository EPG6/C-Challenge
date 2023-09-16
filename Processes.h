#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace Process
{
	enum class state
	{
       Suspended,Running
	};
	using namespace std::string_literals;
	struct process
	{
		std::string name{};
		size_t id{};
		state status{};
		std::string account_name{};
		size_t mem_size{};
		std::string platform{};

	};
	auto print(const state& a)
	{
		if (a == state::Running)
			return "Running"s;
		else
			return "Suspended"s;
	}
	std::ostream& operator<<(std::ostream& stream, const process sample)
	{
		const auto size(20);
		stream << std::left << std::setw(size) << sample.name  
			<< std::left << std::setw(size) << sample.id <<
			std::left << std::setw(size) << print(sample.status) <<
			std::left << std::setw(size) << sample.account_name <<
			std::right << std::setw(size) << sample.mem_size / 1000 <<"  "<<
			std::left << std::setw(size) << sample.platform;
		return stream;
	}
	template<typename container>
	void print(container R)
	{
		std::sort(R.begin(), R.end(), [](const process& left, const process& right)
			{
				return left.name < right.name;
			});
		for (auto el : R)
			std::cout << el << std::endl;
	}
}