#pragma once
#include<memory>
#include <string>
#include <array>
#include <iostream>

namespace my_handle
{
	template<typename handle_type>
	using handle = std::unique_ptr<handle_type>;
	
	template<typename handle_type>
	class Filehandle
	{
	public:
		Filehandle() = default;
		Filehandle(handle_type resource):m_handle(std::make_unique<handle_type>(resource) )
		{

		}
		Filehandle(const Filehandle&) = delete;
		Filehandle& operator=(const Filehandle&) = delete;
		Filehandle(Filehandle&&) = default;
		Filehandle& operator=(Filehandle&&) = default;
		~Filehandle() = default;
		auto release()
		{
			if (m_handle != nullptr)
				return m_handle.release();
		}
		bool is_handle_valid()
		{
			if (m_handle != nullptr)
				return true;
		    return false;
		}

	private:
		handle<handle_type> m_handle;
	};

	void execute()
	{
		std::array<std::string,3> table = { "All of them", "None of them", "Any of them" };
		auto a_handle{ Filehandle(table)};
		std::cout << "Is a_handle valid: " << (a_handle.is_handle_valid() ? "yes" : "no") << std::endl;
		auto another_handle{ std::move(a_handle) };
		std::cout << "After moving the control of the resource, is a_handle still valid: " << (a_handle.is_handle_valid() ? "yes" : "no") << std::endl;
		std::cout << "Is another_handle still valid: " << (another_handle.is_handle_valid() ? "yes" : "no") << std::endl;

		auto resource{another_handle.release()};
		std::cout << "Is another_handle still valid after releasing its resource: " << (another_handle.is_handle_valid() ? "yes" : "no") << std::endl;
		std::cout << "The content of the resource is/are: \n";
		for (auto el : *resource)
			std::cout << el << std::endl;

	}
}