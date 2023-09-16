#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <regex>
#include <bitset>
#include <map>
#include "StringLibrary.h"

namespace Binary_to_String
{
	
	std::map < std::string, std::string> Binarymap
	{
		{"0000","0"},{"0001","1"},{"0010","2"},{"0011","3"},{"0100","4"},
		{"0101","5"},{"0110","6"},{"0111","7"},{"1000","8"},{"1001","9"},
		{"1010","A"},{"1011","B"},{"1100","C"},{"1101","D"},{"1110","E"},
		{"1111","F"},
	};

	std::map < std::string, std::string> Stringmap
	{
		{"0","0000"},{"1","0001"},{"2","0010"},{"3","0011"},{"4","0100"},
		{"5","0101"},{"6","0110"},{"7","0111"},{"8","1000"},{"9","1001"},
		{"A","1010"},{"B","1011"},{"C","1100"},{"D","1101"},{"E","1110"},
		{"F","1111"},
	};

	auto stringify(size_t& byte)
	{
		std::string string_byte{ "" };
		std::string string_nipple{ "" };
		std::bitset<8> b1{ byte };
		string_nipple = b1.to_string();
		string_byte += (Binarymap[string_nipple.substr(0, 4)] + Binarymap[string_nipple.substr(4)]);
		return string_byte;
	}
	auto binarify(std::string&& string_byte)
	{
		std::string bitset_string{ "" };
		bitset_string += (Stringmap[std::string{ string_byte[0] }]
			+ Stringmap[std::string{ string_byte[1] }]);
		std::bitset<8> b1{ bitset_string };
		return b1.to_ulong();
	}
	auto to_string(std::vector<size_t> BinaryContainer)
	{
		std::string out{ "" };
		for (auto& byte : BinaryContainer)
		{
			out += stringify(byte);
		}
		return out;
	}
	auto split_to_substring(std::string_view view)
	{
		std::vector<std::string> stringList{};
		for (size_t i{}; i < view.size(); i += 2)
		{
			stringList.push_back(std::string{ view.substr(i, 2) });
		}
		return stringList;
	}
	void to_binary(std::vector<std::string> StringBitContainer)
	{
		for (auto& s_byte : StringBitContainer)
		{
			auto result{ binarify(string_library::to_upper(s_byte)) };
			std::cout << std::hex << result << " ";
		}
	}
	 void execute()
	 {
		 std::vector<size_t> array{ 1,2,3,4,5,6 };
		 auto result{ to_string(array) };
		 std::cout << result << " or " << string_library::to_lower(result) << std::endl;
		 std::string hexlist{ "BAADF00D" };
		 to_binary(split_to_substring(hexlist));
	}
}