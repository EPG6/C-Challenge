#pragma once
#include <string>
#include <vector>
#include "StringLibrary.h"

namespace PhoneNumber
{
    auto filter(std::vector<std::string>List, std::string_view countrycode)
    {
        using namespace std::string_literals;
        auto filteredList{ std::vector<std::string>{} };
        for (auto& number : List)
        {
            number = string_library::remove(number, ' ');
            if (number.substr(0, countrycode.size()) == countrycode)
            {
                filteredList.push_back(number);
            }
            else if (auto ext{ "+"s + std::string{countrycode} };
                number.substr(0, ext.size()) == ext)
            {
				filteredList.push_back(number);
            }
        }
        return filteredList;
    }
    auto TranformCountryCode(std::vector<std::string>List, std::string_view countrycode)
    {
		using namespace std::string_literals;
		auto TransformedList{ std::vector<std::string>{} };
		for (auto& number : List)
		{
			number = string_library::remove(number, ' ');
			if (number.substr(0, countrycode.size()) == countrycode)
			{
				TransformedList.push_back("+"s + number);
			}
			else if (auto ext{ "+"s + std::string{countrycode} };
				number.substr(0, ext.size()) == ext)
			{
				TransformedList.push_back(number);
			}
            else if (number[0] == '+')
            {
                for (size_t i{}; i < ext.size(); i++)
                {
                    number[i] = ext[i];
                }
				TransformedList.push_back(number);
            }
            else
            {
                TransformedList.push_back(ext + number);
            }
		}
		return TransformedList;
    }
}