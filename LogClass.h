#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>
#include "RandomString.h"

namespace Log
{
	
	class LogClass final
	{
	
	public:
		LogClass(bool delete_file = true) : is_file_deleted(delete_file)
		{
			using namespace std::filesystem;
			using namespace std::string_literals;
			auto path{ temp_directory_path() };
			std::cout << "Temporary folder" << path << std::endl;
			auto file_name{ StringGenerate::somestring() + ".txt"s };
			auto temp_path{ path / file_name };
			auto handle{ std::ofstream(temp_path,std::ios::trunc) };
			if (!handle.is_open())
			{
				std::cout << "Error occurred when trying to create the logging file" << std::endl;
				return;
			}
			success = true;
			temp = temp_path;
			handle.close();
		}
		~LogClass() noexcept
		{
			using namespace std::filesystem;
			if (is_file_deleted)
			{
				std::cout << "Destroying the temporary file..." << std::endl;
				auto err{ std::error_code{} };
				auto success = remove(temp, err);
				if (!success)
					std::cout << "Error occured: " << err << std::endl;
			}
			else
			{
				using namespace std::filesystem;
				auto permanent{ std::filesystem::path(R"(C:\Users\hp\Desktop\test)") };
				auto perm_path{ permanent / temp.filename() };
				auto err{ std::error_code{} };
				std::filesystem::copy(temp, perm_path, err);
				if (err)
				{
					std::cout << "Error occured: " << err << std::endl;
					std::cout << "Destroying the temporary file..." << std::endl;
					auto err{ std::error_code{} };
					auto success = remove(temp, err);
					if (!success)
						std::cout << "Error occured: " << err << std::endl;
				}
			}
		}

		bool is_valid() const
		{
			return success;
		}

		bool write(std::string_view text)
		{
			if (!success)
		    {
				std::cout << "The Logfile is invalid" << std::endl;
				return 0;
			}
			auto handle{ std::ofstream(temp,std::ios::app) };
			if (!handle.is_open())
			{
				std::cout << "The Logfile is invalid" << std::endl;
				return 0;
			}
			std::cout << "Writing the logging info..." << std::endl;
			handle.write(text.data(), text.size());
			handle << std::endl;
			std::cout << "Terminated" << std::endl;
			handle.close();
			return 1;
		}
	
	private:
		bool is_file_deleted{ 1 };
		std::filesystem::path temp{};
		bool success{ 0 };
	};
}