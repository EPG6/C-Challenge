#pragma once
#include <regex>
#include<string>

namespace LicensePlate
{
	using namespace std::string_literals;
	bool validate(std::string_view input)
	{
		auto pattern{ R"(^[A-Z]{3}-[A-Z]{2}\s*[0-9]{3,4}$)"s };
		auto rx = std::regex(pattern, std::regex_constants::icase);
		auto valid = std::regex_match(std::string{ input }, rx);
		return valid;
	}
	void split_license_plate(std::string_view input)
	{
		auto text{ std::string{input} };
		auto pattern{ R"(^([A-Z]{3})-([A-Z]{2})\s*([0-9]{3,4})$)"s };
		auto rx = std::regex(pattern, std::regex_constants::icase);
		if (validate(input))
		{
			auto match = std::smatch{};
			if (std::regex_search(text, match, rx))
			{
				std::cout << *(match.end() - 1) << " ";
			}
		}
	}
}