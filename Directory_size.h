#pragma once
#include <filesystem>
#include <chrono>
#include <regex>

namespace Directory
{
	namespace fs = std::filesystem;
	std::uintmax_t dir_size(fs::path const& path)
	{
		auto size = static_cast<uintmax_t>(-1);
		if (fs::exists(path) && fs::is_directory(path))
		{
			for (auto const& entry : fs::recursive_directory_iterator(path))
			{
				if (fs::is_regular_file(entry.status()) ||
					fs::is_symlink(entry.status()))
				{
					auto err = std::error_code{};
					auto filesize = fs::file_size(entry);
					if (filesize != static_cast<uintmax_t>(-1))
						size += filesize;
				}
			}
		}
		return size;
	}
	template <typename TP>
	const std::time_t to_time_t(TP tp)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
			+ system_clock::now());
		const auto out{ system_clock::to_time_t(sctp) };
		return out;
	}
	void output_last_write(fs::path& path)
	{
		using namespace std::chrono;
		using namespace std::chrono_literals;
		auto today = floor<std::chrono::days>(std::chrono::system_clock::now());
		if (fs::exists(path) && fs::is_directory(path))
		{
			{
				auto err{ std::error_code{} };
				auto lwt{ fs::last_write_time(path, err) };
				auto time = to_time_t(lwt);
				auto ltime{ tm{} };
				auto local = localtime_s(&ltime, &time);
				std::cout << path << ": " << std::put_time(&ltime, "%c") << std::endl;
			}
			for (auto const& entry : fs::recursive_directory_iterator(path))
			{
				{
					auto err{ std::error_code{} };
					auto lwt{ fs::last_write_time(entry, err) };
					auto time = to_time_t(lwt);
					auto ltime{ tm{} };
					auto local = localtime_s(&ltime, &time);
					std::cout << entry << ": " << std::put_time(&ltime, "%c") << std::endl;
					
				}
			}
		}
	}
	template<typename Duration>
	void delete_older(fs::path& path, Duration sometime)
	{
		using namespace std::chrono;
		using namespace std::chrono_literals;
		sometime = sometime - 1h;
		auto stime = system_clock::to_time_t(sometime);
		auto ltime{ tm{} };
		auto local = localtime_s(&ltime, &stime);
		std::cout << std::put_time(&ltime, "%c") << std::endl;
		if (fs::exists(path) && fs::is_directory(path))
		{
			{
				auto err{ std::error_code{} };
				auto lwt{ fs::last_write_time(path, err) };
				auto time = to_time_t(lwt);
				if (stime > time)
				{
					auto success = fs::remove_all(path, err);
					if (!success)
					{
						std::cerr <<"Error when deleting file "<< path<<": "<< err << std::endl;
					}
					else
						std::cout << path << " has been deleted" << std::endl;
				}
			}
			for (auto const& entry : fs::recursive_directory_iterator(path))
			{
				if (fs::is_directory(entry) && fs::exists(entry))
				{
					auto err{ std::error_code{} };
					auto lwt{ fs::last_write_time(entry, err) };
					auto time = to_time_t(lwt);
					if (stime > time)
					{
						auto success = fs::remove_all(entry, err);
						if (!success)
						{
							std::cerr << "Error when deleting file " << entry << ": " << err << std::endl;
						}
						else
							std::cout << entry << " has been deleted" << std::endl;
					}
				}
				else if (fs::is_regular_file(entry.status()))
				{
					auto err{ std::error_code{} };
					auto lwt{ fs::last_write_time(entry, err) };
					auto time = to_time_t(lwt);
					if (stime > time)
					{
						auto success = fs::remove(entry, err);
						if (!success)
						{
							std::cerr << "Error when deleting file " << entry << ": " << err << std::endl;
						}
						else
							std::cout<<entry<<" has been deleted"<<std::endl;
					}

				}
			}
		}
	}
	auto file_match(fs::path& path)
	{
		using namespace std::string_literals;
		auto List{ std::vector<fs::path>() };
		if (fs::exists(path) && fs::is_directory(path))
		{
			for (auto const& entry : fs::recursive_directory_iterator(path))
			{
				if (fs::is_regular_file(entry.status()) ||
					fs::is_symlink(entry.status()))
				{
					auto err = std::error_code{};
					auto pattern{ R"(^([\w\d]+)_([\w\d]+))"s };
					auto rx{ std::regex(pattern,std::regex_constants::icase) };
					auto match = std::smatch{};
					auto entry_path{ (entry.path().filename()) };
					auto entry_string{ entry_path.generic_string() };
					if (std::regex_search(entry_string,rx))
					{
						List.push_back(entry_path);
					}
				}
			}
		}
		return List;
	}
}