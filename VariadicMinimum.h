#pragma once
#include <algorithm>
#include<vector>

namespace var_min
{
	template <typename T> // [1] overload with fixed
	T extract(T value) // number of arguments
	{
		return value;
	}
	template <typename T, typename... Ts> // [2] typename... Ts
	T extract(T head, Ts... rest) // [3] Ts... rest
	{
		return std::min(head , extract(rest...)); // [4] rest...
	}
}

namespace var_pushback
{
	template <typename T> // [1] overload with fixed
	void range_pushback(std::vector<T>& container, T value) // number of arguments
	{
		container.push_back(std::move(value));
	}
	template <typename T, typename... Ts> // [2] typename... Ts
	void range_pushback(std::vector<T>& container, T head, Ts... rest) // [3] Ts... rest
	{
		container.push_back(std::move(head));
		range_pushback(container, rest...);// [4] rest...
	}
}

namespace verify_content
{
	template <typename R, typename T> // [1] overload with fixed
	bool contains_all(R& container, T value)
	{
		if (std::find(container.begin(), container.end(), value) == container.end())
			return 0;
		return 1;
	}
	template <typename R, typename T, typename... Ts> // [2] typename... Ts
	bool contains_all(R& container, T head, Ts... rest)
	{
		if (std::find(container.begin(), container.end(), head) == container.end())
			return 0;
		return contains_all(container, rest...);
	}
	template <typename R, typename T> // [1] overload with fixed
	bool contains_any(R& container, T value)
	{
		if (std::find(container.begin(), container.end(), value) != container.end())
			return 1;
		return 0;
	}
	template <typename R, typename T, typename... Ts> // [2] typename... Ts
	bool contains_any(R& container, T head, Ts... rest)
	{
		if (std::find(container.begin(), container.end(), head) != container.end())
			return 1;
		return contains_any(container, rest...);
	}
	template <typename R, typename T> // [1] overload with fixed
	bool contains_none(R& container, T value)
	{
		if (std::find(container.begin(), container.end(), value) == container.end())
			return 1;
		return 0;
	}
	template <typename R, typename T, typename... Ts> // [2] typename... Ts
	bool contains_none(R& container, T head, Ts... rest)
	{
		if (std::find(container.begin(), container.end(), head) != container.end())
			return 0;
		return contains_none(container, rest...);
	}
}