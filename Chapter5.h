#pragma once
#include "MyTime.h"
#include "DateOperation.h"
#include <iostream>

namespace Chapter5
{
	void execute() 
	{
		//Time::execute();
		{
			using namespace std::chrono_literals;
			auto first{ std::chrono::sys_days{2020y / std::chrono::March / 15} };
			auto last{ std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()) };
			auto diff{ DateOP::daydiff(std::chrono::sys_days(last), first) };
			std::cout << "Difference between " << first << " and " << last << " is " << diff << " days\n";
		}

		{
			using namespace std::chrono_literals;
			auto first{ std::chrono::sys_days{2020y / std::chrono::March / 18} };
			std::cout << "The day " << first << " is a " << DateOP::day_of_week(first) << std::endl;
			std::cout << first << " is the " << DateOP::day_of_year(first) <<" day(s) of the year." << std::endl;
			std::cout << first << " is the " << DateOP::week_of_year(first) << " week(s) of the year." << std::endl;
		}

		{
			auto Table{ std::vector<DateOP::Participant>{ {"Lea", "Europe/Paris"},
				{"John", "Asia/Dubai"},{"Flora","Africa/Djibouti"}} };
			DateOP::Convert_Time(Table);
		}

		{
			using namespace std::chrono;
			auto& db = std::chrono::get_tzdb();
			std
				::
				cout
				<<
				"Locate zone : "
				<< db.locate_zone(
					"US/Pacific"
				)->name() <<
				"\n"
				;
			std::cout << "Leap seconds:\n";
			std::for_each(db.leap_seconds.begin(), db.leap_seconds.end(),
				[](
					const
					leap_second& ls)
				{
					std
						::
						cout
						<< ls.date() <<
						"\n"
						;
				});
			std
				::
				cout
				<<
				"Links:\n"
				;
			std
				::for_each(db.links.begin(), db.links.end(),
					[](
						const
						time_zone_link& l)
					{
						std
							::
							cout
							<<
							"Name: "
							<< l.name() <<
							"\t\tTarget:"
							<< l.target() <<
							'\n'
							;
					});
			std
				::
				cout
				<<
				"\nTime Zone descriptions:\n"
				;
			std
				::for_each(db.zones.begin(), db.zones.end(),
					[](
						const
						time_zone& z)
					{
						std
							::
							cout
							<<
							"Zone: "
							<< z.name() <<
							"\n"
							;
					});
		}

		{
			using namespace std::chrono_literals;
			std::chrono::year_month amonth{ 2021y / std::chrono::June };
			DateOP::Calendar_weeks(amonth);
		}
	}
}