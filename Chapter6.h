#pragma once
#include "MPriorityQueue.h"
#include "CircularBuffer.h"
#include "RandomString.h"
#include <iomanip>
#include "DoubleBuffer.h"
#include "MostFrequentElement.h"
#include "MyTime.h"
#include "LetterHistogram.h"
#include "FilterPhoneNumbers.h"
#include "StringPermutation.h"
#include "Movies.h"
#include "PairwiseAlgorithm.h"
#include "WeaselSim.h"
#include "CellSimu.h"

namespace Chapter6
{
	void execute()
	{
		/*{
			MyPriorityQueue::PriorityQueue<int> List;
			List.push(5);
			List.push(3);
			List.push(7);
			List.push(-1);
			List.push(1);
			std::cout << List.top() << std::endl;
			List.pop();
			List.pop();
			if (!List.is_empty())
			{
				List.push(7);
				List.push(4);
			}
			std::cout << List.top() << std::endl;
			std::cout << List.size() << std::endl;
		}*/
		/*{
			CircularBuffer::CircBuffer<std::string> Container(10);
			std::cout << "Introducing the new Circular Buffer \nTest with capacity "
				<< Container.capacity() << std::endl;
			if (Container.is_empty())
			{
				for (unsigned i{}; i < 10; i++)
				{
					Container.push(StringGenerate::somestring());
				}
			}
			for (const auto& el : Container)
				std::cout << el << std::endl;
			std::cout << std::setfill('_') << std::setw(15) << "" << std::endl;
			if (Container.is_full())
			{
				for (unsigned i{}; i < 5; i++)
				{
					Container.push(StringGenerate::somestring());
				}
				for (const auto& el : Container)
					std::cout << el << std::endl;
			}
			for (unsigned i{}; i < 5; i++)
			{
				Container.erase();
			}
			std::cout << "Buffer size is " << Container.size() << std::endl;
			for (const auto& el : Container)
				std::cout << el << std::endl;
		}
	}*/
	/*{
		auto Container = DoubleBuffer::DBuffer<int>(15);

		for (size_t i{}; i < 15; i++)
		{
			Container.write(i);
		}
		Container.synchronise();
		Container.print();
		for (auto it = Container.begin(); it != Container.end() - 5; it++)
		{
			*it = 17;
		}
		std::cout << "Before :\n";
		Container.print();
		std::cout << "After :\n";
		Container.synchronise();
		Container.print();
	}*/
	/*{
		auto List{ std::vector<int>{1,1,3,5,8,13,3,5,8,8,5} };
		auto then = std::chrono::high_resolution_clock::now();
		auto modeList = MostFrequentElement::mode(List);
		auto now = std::chrono::high_resolution_clock::now();
		std::cout <<"It took "
			<<std::chrono::duration_cast<std::chrono::microseconds>(now - then)
			<< std::endl;
		for (const auto& mode : modeList)
			std::cout << mode.first << "\t" << mode.second << std::endl;
	}*/
	/*{
		using namespace std::string_literals;
		auto input{ R"(Write a program that, given a text, determines and prints a histogram with the frequency of
						each letter of the alphabet. The frequency is the percentage of the number of appearances of
						each letter from the total count of letters. The program should count only the appearances
						of letters and ignore digits, signs, and other possible characters. The frequency must be
						determined based on the count of letters and not the text size.)" };
		LetterHisto::draw(input);
	}*/
	/*{
		using namespace std::string_literals;
		auto MyList{ std::vector{"075425689"s,"44569874123"s,"+44519874123"s,
								 "+27423589124"s,"44 89110 1052"s,"77252536014"s} };
		auto result{ PhoneNumber::filter(MyList,"44"s) };
		for (const auto& el: result)
		{
			std::cout << el << std::endl;
		}
		auto output{ PhoneNumber::TranformCountryCode(MyList,"44"s) };
		for (const auto& el : output)
		{
			std::cout << el << std::endl;
		}
	}*/
	/*{
	using namespace std::string_literals;
	 auto word{ "under"s };
	 auto t1 = Time::perf_timer<>::duration(PermutString::print_permutations, word);
	 std::cout << std::chrono::duration<double, std::milli>(t1).count()
		 << "ms" << '\n';
	t1 = Time::perf_timer<>::duration(PermutString::rec_permut, word);
			 std::cout << std::chrono::duration<double, std::milli>(t1).count()
				 << "ms" << '\n';
	 t1 = Time::perf_timer<>::duration(PermutString::permutations, word);
	 std::cout << std::chrono::duration<double, std::milli>(t1).count()
		 << "ms" << '\n';
	}*/
	/*{
	using namespace Movie;
	using namespace std::string_literals;
	std::vector<movie> List(10);
	std::random_device rd{};
	std::vector<int> seed_data(std::mt19937::state_size);
	std::generate(std::begin(seed_data), std::end(seed_data),
		std::ref(rd));
	std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
	auto eng = std::mt19937{ seq };
	auto dist1{ std::uniform_int_distribution{1,10} };
	for (auto& el : List)
	{
		auto sample{ std::vector<unsigned>(eng() % 10 + 90) };
		el.Title = StringGenerate::somestring(eng() % 10 + 6);
		std::generate(sample.begin(), sample.end(), [&dist1, &eng]() { return dist1(eng); });
		el.Ratings = sample;
	}
	print_average_ratings(List);
	}*/
	/*{
	auto numbers{ std::vector{1, 1, 3, 5, 8, 13, 21, 47} };
	auto number2{ std::vector{1, 1, 13, 5, 18, 13, 2} };
	auto result{ Pairwise::pair_elements(numbers) };
	auto other{ my_zip::zip(numbers,number2) };
	struct book
	{
		int id;
		std::string title;
		std::string author;
	};
	std::vector<book> books{
	{101, "The C++ Programming Language", "Bjarne Stroustrup"},
	{203, "Effective Modern C++", "Scott Meyers"},
	{404, "The Modern C++ Programming Cookbook", "Marius Bancila"} };
	auto titles = Select::select(books, [](book const& b) {return b.title; });
	auto myF = [](auto x, auto y) { return y < x; };
	nsort::sort <>(number2.begin(), number2.begin() + 5);
	nsort::sort(numbers.begin(), numbers.end(), myF);
	std::cout << "End\n";
	}*/
	/*{
	Weasel::weasel w("METHINKS IT IS LIKE A WEASEL");
	auto then = std::chrono::high_resolution_clock::now();
	w.run(100);
	auto after = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(after - then)
		<< "ms" << std::endl;
	}*/
	{
	using namespace std::chrono_literals;

	Cell::universe u(50, 20);
	u.run(Cell::universe::seed::random, 100, 100ms);
	}
	}
	
}