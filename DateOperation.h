#pragma once
#include <chrono>

namespace DateOP
{
	using namespace std::chrono;
	using namespace std::chrono_literals;
	struct Participant
	{
		std::string name{};
		std::string time_zone{ };
	};
	auto daydiff(sys_days start, sys_days end)
	{
		if (start < end)
			return (end - start).count();
		else
			return (start - end).count();
	}
	auto day_of_week(sys_days day)
	{
		return weekday(day);
	}
	auto day_of_year(sys_days t_day)
	{
		year_month_day someyear{ t_day };
		auto the_year = year{ someyear.year() };
		auto the_month = month{1};
		auto the_day = day{1};
		year_month_day bound{ the_year,the_month,the_day };
		auto low{ sys_days{bound} };
		return (t_day - low).count();
	}
	auto week_of_year(sys_days t_day)
	{
		year_month_day someday{ t_day };
		unsigned num{};
		for (unsigned i{1}; i < unsigned{ someday.month() }; i++)
		{
			year_month_day_last ymdl{ someday.year(),
              month_day_last{ month{ i } } };
			year_month_day last_day{ ymdl };
			year_month_weekday last_weekday{ last_day };
			num += last_weekday.index();
		}
		year_month_weekday its_weekday{ someday };
		num += its_weekday.index();
		return num;
	}
	void Convert_Time( std::vector<Participant> List )
	{
		auto now = system_clock::now();
		for (auto participant : List)
		{
			std::cout << participant.name << " local time: " 
				<< zoned_time(participant.time_zone, now) 
				<< std::endl;
		}
	}
	
	void Calendar_weeks(year_month somemonth)
	{
		year_month_day first_day{ somemonth.year(),somemonth.month(),day{1} };
		auto start_of_month{ day_of_week(first_day) };
		year_month_day_last ymdl{ somemonth.year(),
			  month_day_last{ month{ static_cast<unsigned>(somemonth.month())}} };
		auto last_of_month{ day_of_week(ymdl) };
		year_month_weekday last_weekday{ ymdl };
		for (unsigned i{}; i < 7; i++)
		{
			if(!i)
				std::cout << std::left << std::setw(4) << weekday(i);
			else
				std::cout << std::right << std::setw(4) << weekday(i);
		}
		std::cout << std::endl;
		unsigned num{1};
		for (unsigned x{}; x < last_weekday.index(); x++)
		{
			for (unsigned i{}; i < 7; i++, num++)
			{
				if (num == 1 && weekday(i) != start_of_month)
				{
					std::cout << std::right << std::setw(4) << "";
					num--;
				}
				else if (num > static_cast<unsigned>(ymdl.day()))
					break;
				else
					std::cout << std::right << std::setw(4) << num;
			}
			std::cout << std::endl;
		}
	}
}