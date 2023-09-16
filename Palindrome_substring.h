#pragma once
#include "StringLibrary.h"
#include <queue>
namespace Palindrome
{
	namespace
		{
		using namespace std::string_literals;
		std::string longest_substring_impl(const std::string& text,size_t i, size_t j)
		{
			auto longest_palindrome{ std::vector{""s}};
			for (size_t x{}; x < j - 2; x++)
			{
				for (size_t y{ j }; y >= x + 2; y--)
				{
					auto substring{ text.substr(x,y - x) };
					if (substring == string_library::reverse(substring))
					{
						longest_palindrome.push_back(substring);
					}
				}
			}
			std::sort(longest_palindrome.begin(), longest_palindrome.end(), [](auto x, auto y)
				{
					return x.size() > y.size();
				});
			return *longest_palindrome.begin();
		}
	}
	std::string longest_substring(const std::string& text)
	{
		return longest_substring_impl(text, 0, text.size());
	}
}