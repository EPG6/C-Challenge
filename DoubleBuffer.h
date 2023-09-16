#pragma once
#include <vector>

namespace DoubleBuffer
{
	template<typename T>
	class DBuffer
	{
	public:
		DBuffer() = delete;
		DBuffer(size_t size) 
		{
			oldbuff.reserve(size);
			 newbuff.reserve(size);
		}
		~DBuffer() = default;
		void print() const
		{
			std::copy(oldbuff.begin(), oldbuff.end(), std::ostream_iterator<T>(std::cout, " "));
		}
		T read(size_t index) const noexcept
		{
			return *(oldbuff.cbegin() + index % oldbuff.size());
		}
		void write(T element) noexcept
		{
			newbuff.push_back(element);
		}
		void synchronise() 
		{
			oldbuff = newbuff;
		}
		auto begin()
		{
			return newbuff.begin();
		}
		auto end()
		{
			return newbuff.end();
		}
		auto cbegin()
		{
			return newbuff.cbegin();
		}
		auto cend()
		{
			return newbuff.cend();
		}


	private:
		std::vector<T> oldbuff{};
		std::vector<T> newbuff{};
	};
}