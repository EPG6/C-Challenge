#pragma once
#include <string>
#include <algorithm>
#include <vector>

namespace PermutString
{
	std::vector<std::string> List{};
	namespace
	{
		void permut_impl(std::string_view text, size_t i)
		{
			if (i == text.size())
				return;
			auto next{ std::string{text[i]} };
			auto len{ List.size() };
			auto templist{ std::vector<std::string>{} };
			for (auto& el : List)
			{
				auto temp{ el };
				
				for (size_t x{}; x < temp.size(); x++)
				{
					auto buff{ temp };
					if (std::string{ buff[x] } != next)
					{
						buff.insert(x, next);
						if (std::find(templist.begin(), templist.end(), buff) == templist.end()
							&& std::find(List.begin(), List.end(), buff) == List.end())
							templist.push_back(buff);
					}
				}
			if (std::find(List.begin(), List.end(), temp + next) == List.end()
				&& std::find(templist.begin(), templist.end(), temp + next) == templist.end())
					el = el.append(next);
			}
			std::copy(templist.begin(), templist.end(), std::back_inserter(List));
			return permut_impl(text, i + 1);
		}
	}
	std::vector<std::string> permutations(std::string_view mtext)
	{
		auto text{ std::string{mtext} };
		std::sort(text.begin(), text.end());
		List.push_back({text[0]});
		permut_impl(text, 1);
		auto start = std::remove_if(List.begin(), List.end(), [&text](auto x) {return x.size() != text.size(); });
		List.erase(start, List.end());
		return List;
	}
	std::vector<std::string> recList{};
	void next_permutation(std::string str, std::string perm)
	{
		if (str.empty())
		{
			if(std::find(recList.begin(), recList.end(), perm) == recList.end())
					recList.push_back(perm);
		}
		else
		{
			for (size_t i = 0; i < str.size(); ++i)
			{
				next_permutation(str.substr(1), perm + str[0]);
				std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
			}
		}
	}
	auto rec_permut(std::string str)
	{
		std::sort(str.begin(), str.end());
		next_permutation(str, "");
		return recList;
	}
	void print_permutations(std::string str)
	{
		std::vector<std::string> Another{};
		std::sort(std::begin(str), std::end(str));
		do
		{
			//std::cout << str << std::endl;
			Another.push_back(str);
		} while (std::next_permutation(std::begin(str), std::end(str)));
	}
}