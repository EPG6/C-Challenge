#pragma once
#include "IPV4address.h"
#include "VariadicMinimum.h"
#include <assert.h>
#include <array>
#include <list>
#include "FileHandle.h"
#include "TemperatureLiterals.h"*
//#include "Binary_to_String.h"
//#include "Palindrome_substring.h"
//#include "LicensePlateValidation.h"
//#include "URL.h"
#include "Date.h"

namespace Chapter2
{
	using namespace std::string_literals;
	//IPV4::execute();
	//std::cout << var_min::extract(1, 2, 3, 0, 5, -7);
	/*std::vector<int> table{};
	var_pushback::range_pushback(table, 1, 2, 3, 0, 5, -7);
	for (const auto& el:table)
	{
		std::cout << el << " ";
	}
	std::cout << std::endl;
	std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
	assert(verify_content::contains_any(v, 0, 3, 30));
	std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
	assert(verify_content::contains_all(a, 1, 3, 5, 6));
	std::list<int> l{ 1, 2, 3, 4, 5, 6 };
	assert(!verify_content::contains_none(l, 0, 6));
	//my_handle::execute();
	temperature_literals::execute();*/
	//Binary_to_String::execute();
	//std::cout << string_library::replace(std::string{ "the c++ challenger" }, ' ', '$') << std::endl;
	/*std::vector<std::string> input{"this","is","an","example"};
	std::cout << string_library::Concatenate(input, ' ');*/
	//auto output{ string_library::split(std::string{"this,is.a sample!!"},std::string_view{",.! "}) };
	/*using namespace std::string_literals;

	auto text{ "amatoutaammaaou"s };
	std::cout << Palindrome::longest_substring(text);*/
	//LicensePlate::split_license_plate(std::string_view{ "NWE-BH 2100" });
// 	auto parts{ my_URL::extract("https://www.microsoft.com:8080/tutorials/what-is-a-url?irclickid=yIdW6JVaaxyNR4K0-Lw1QVHwUkAQm5Tfx0zuRs0&irgwc=1&PID=357605#What_Is_an_Example_of_a_URL_Address"s) };
// 	for (auto part : parts)
// 		std::cout << part << " ";

	auto input{ R"(12-05-2023 27-06-2015)"s };
	std::cout << date::reverse(input);
}