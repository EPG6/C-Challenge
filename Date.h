#pragma once
#include <regex>
#include "StringLibrary.h"

namespace date
{
	using namespace std::string_literals;
	std::string reverse(std::string input)
	{
		auto stream{ std::stringstream{} };
		auto pattern{ R"(([0-9]{1,2})-([0-9]{1,2})-([0-9]+)(?:\s*))"s };
		auto rx{ std::regex(pattern,std::regex_constants::icase) };
		auto end{ std::sregex_iterator{} };
		for (auto it = std::sregex_iterator{ std::begin(input),
				std::end(input), rx };	it != end; ++it)
		{
			stream << (*it)[3] << "-"
				<< (*it)[2] << "-" << (*it)[1] << "\t";
		}
		return stream.str();
	}
}