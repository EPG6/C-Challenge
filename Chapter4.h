#pragma once
#include "Pascal_Triangle.h"
#include "Processes.h"
#include "RemoveLine.h"
#include "Directory_size.h"
#include "LogClass.h"

namespace Chapter4
{
	using namespace std::string_literals;
	void execute()
	{
		//Pascal::print();
		/*auto table{ std::vector{Process::process{"chrome.exe", 1044, Process::state::Running, "marius.bancila", 25180, "32 - bit"},
		{"chrome.exe", 10100, Process::state::Running, "marius.bancila", 227756, "32 - bit"},
		{"cmd.exe", 512, Process::state::Running, "SYSTEM", 48, "64 - bit"},
		{"explorer.exe", 7108, Process::state::Running, "marius.bancila", 29529, "64 - bit"},
		{"skype.exe", 22456, Process::state::Suspended, "marius.bancila", 656, "64 - bit"}} };
	   Process::print(table);*/
		/*{
			auto text{ R"(Senor Roldan was sitting behind his desk at Escortes Belen congratulating himself for deftly sidestepping theGuardia’s newest pathetic attempt to trap him.
				 Having anofficer fake a German accent and request a girl for the night—it was entrapment; what would they think of next?
		
		
				The phone on his desk buzzed loudly. Senor Roldan scooped up the receiver with a confident flair. “Buenas noches, Escortes Belen.”
		
		
		
				“Buenas noches,” a man’s voice said inlightning-fast Spanish. He sounded nasal, like he had a slight cold. “Is this a hotel?”
		
		
				“No, sir. What number are you dialing?” Senor Roldan was not going to fall for any more tricks this evening.
		
		“34-62-10,” the voice said.)"s };
			std::cout << "Initially: \n" << text << std::endl << "After: \n";
			std::cout << EmptyLine::remove(text);
		}*/
		/*{
			using namespace std::chrono;
			using namespace std::chrono_literals;
			auto path{ std::filesystem::path(R"(C:\Users\hp\Desktop\test)") };
			std::cout << "Directory: " << path << " size: " << Directory::dir_size(path) << std::endl;
			Directory::output_last_write(path);
			auto tp = sys_days{ 2022y / November / 25 } + 11h + 19min + 0s;

			Directory::delete_older(path, tp);
			auto result{ Directory::file_match(path) };
			for (const auto& el : result)
				std::cout << el << std::endl;
		}*/
		auto info{ std::string{"This is a test."} };
		auto Mylog{ Log::LogClass{0} };
		if (Mylog.is_valid())
		{
			Mylog.write(info);
			Mylog.write("Info is always crucial"s);
		}
	}
}