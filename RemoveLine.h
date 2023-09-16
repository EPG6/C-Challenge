#pragma once
#include "StringLibrary.h"

namespace EmptyLine
{
	std::string remove(std::string_view text)
	{
		auto lines{ string_library::split(std::string{text},'\n') };
		auto start = std::remove_if(
			std::begin(lines), std::end(lines),
			[=](auto line) {return line.empty(); });
		lines.erase(start, lines.end());
		auto out{ string_library::Concatenate(lines,'\n') };
		return out;
	}
}