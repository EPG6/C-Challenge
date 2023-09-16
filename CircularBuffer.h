#pragma once
#include <vector>

namespace CircularBuffer
{
	template<typename T>
	class CircBuffer
	{
	public:
		CircBuffer() = delete;
		CircBuffer(size_t size) : m_size(size)
		{
			data.reserve(size);
		}
		~CircBuffer() = default;
		void push(T element)
		{
			if (data.size() <= m_size)
				data.push_back(element);
			else
			{
				dist = dist % m_size;
				data[dist] = element;
				dist++;
			}
		}
		void erase()
		{
			data.erase(data.begin());
		}
		bool is_empty() const noexcept
		{
			return data.size() == 0;
		}
		bool is_full() const noexcept
		{
			return data.size() == m_size;
		}
		size_t size() const noexcept
		{
			return data.size();
		}
		size_t capacity() const noexcept
		{
			return m_size;
		}
		auto begin()
		{
			return data.begin();
		}
		auto end()
		{
			return data.end();
		}
		auto cbegin()
		{
			return data.cbegin();
		}
		auto cend()
		{
			return data.cend();
		}

	private:
		std::vector<T> data{};
		size_t m_size{};
		size_t dist{};
	};

	
}