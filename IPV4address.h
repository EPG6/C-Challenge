#pragma once
#include <string>
#include <regex>
#include <iostream>
#include <vector>
#include <algorithm>
#include "StringLibrary.h"

namespace IPV4
{
	using namespace std::string_literals;
	bool ValidInput(std::string_view input)
	{
		auto pattern{ R"(^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]{1,}$)"s };
		auto rx = std::regex{ pattern, std::regex_constants::icase };
		auto valid = std::regex_match(std::string{ input }, rx);
		return valid;
	}
	struct IPv4_address
	{
		IPv4_address(std::string_view input)
		{
			if (ValidInput(input))
			{
				address = std::string{ input };
				components = string_library::split(address, '.');
			}
			else
				std::cout << "Invalid address " << input << std::endl;
		}
		std::string get_address()
		{
			return address;
		}
		auto get_components()
		{
			return components;
		}

		friend std::ostream& operator<<(std::ostream& stream, const IPv4_address& an_address)
		{
			std::cout << an_address.address << std::endl;
			return std::cout;
		}
		private:
			std::string address{};
			std::vector < std::string> components{};
	};
	void enumerate_IPV4_address(IPv4_address first_address, IPv4_address second_address)
	{
		auto first_component{ first_address.get_components() };
		auto second_component{ second_address.get_components() };
		for (int i{ std::stoi(first_component[0]) }; i <= std::stoi(second_component[0]); i++)
		{
			auto part1{ std::to_string(i) };
			for (int y{ std::stoi(first_component[1]) }; y <= std::stoi(second_component[1]); y++)
			{
				auto part2{ part1 + "." + std::to_string(y)};
				for (int z{ std::stoi(first_component[2]) }; z <= std::stoi(second_component[2]); z++)
				{
					auto part3{ part2 + "." + std::to_string(z)};
					for (int a{ std::stoi(first_component[3]) }; a <= std::stoi(second_component[3]); a++)
					{
						auto part4{ part3 + "." + std::to_string(a)};
						std::cout << part4 << std::endl;
					}
				}
			}
		}
	


	}
	int execute()
	{
		std::string input_address{};
		std::cout << "Input address: " << std::endl;
		std::cin >> input_address;
		IPv4_address Myaddress(input_address);
		std::cout << Myaddress;
		std::cout << "Input address range limits: " << std::endl;
		std::string input_lowbound{}, input_highbound{};
		std::cin >> input_lowbound >> input_highbound;
		IPv4_address lowbound(input_lowbound), highbound(input_highbound);
		enumerate_IPV4_address(lowbound, highbound);

		return 0;
	} 
}

