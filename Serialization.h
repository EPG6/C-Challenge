#pragma once
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// demo.cpp
//
// (C) Copyright 2002-4 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <typeinfo>
#include <concepts>

#include <vector>

#ifdef USE_BOOST_OPTIONAL
#  include <boost/optional.hpp>
using boost::optional;
#else
#  include <optional>
using std::optional;
#endif



#ifdef _WIN32
static const std::string fonts_dir = R"(c:\windows\fonts\)";
#elif defined (__APPLE__)
static const std::string fonts_dir = R"(/Library/Fonts/)";
#else
static const std::string fonts_dir = R"(/usr/share/fonts)";
#endif

#include<boost/json.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>


namespace fs = std::filesystem;
namespace boost_archive = boost::archive;
namespace boost_serialization = boost::serialization;

template<class T>
auto NVP(T name)
{
	return BOOST_SERIALIZATION_NVP(name);
}

namespace Select
{
	template <typename In>
	concept IsBool = requires (In a) { typeid(a) == typeid(bool); };
	template<typename T, typename F>
	auto select(std::vector<T> List, F&& func)
	{
		using type = decltype(func(List[0]));
		std::vector<type> Range;
		for (const auto& el : List)
		{
			auto res{ func(el) };
		    Range.push_back(res);
		}
		return Range;
	}
	template<typename T, typename F, IsBool V>
	auto select_if(std::vector<T> List, F&& func, V&& condition)
	{
		
		using type = decltype(func(List[0]));
		std::vector<type> Range;
		for (const auto& el : List)
		{
			if (condition(el))
			{
				auto res{ func(el) };
				Range.push_back(res);
			}
		}
		return Range;
	}
}

namespace Serialize
{
	struct role 
	{
		std::string Star{};
		std::string Name{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Star)& BOOST_SERIALIZATION_NVP(Name);
		}

	};
	struct director
	{
		std::string Name{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Name);
		}
	};
	struct writer
	{
		std::string Name{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Name);
		}
	};
	struct cast
	{
		std::vector<role> Actors{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Actors);
		}
	};
	struct directors
	{
		std::vector<director> Directors{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Directors);
		}
	};
	struct writers 
	{
		std::vector <writer> Writers{};
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Writers);
		}
	};
	struct movie
	{
		unsigned id{};
		std::string title{};
		unsigned year{};
		unsigned mins{};
		cast Cast{};
		directors Directors{};
		writers Writers{};

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(id)& BOOST_SERIALIZATION_NVP(title)&
				BOOST_SERIALIZATION_NVP(year)& BOOST_SERIALIZATION_NVP(mins)&
				BOOST_SERIALIZATION_NVP(Cast)& BOOST_SERIALIZATION_NVP(Directors)
				& BOOST_SERIALIZATION_NVP(Writers);
		}
	};
	struct Movies
	{
		std::vector<movie> Catalog;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file version*/)
		{
			ar& BOOST_SERIALIZATION_NVP(Catalog);
		}
	};

	void save(const Movies& M, std::string_view filename)
	{
		std::ofstream ofs(filename.data(), std::ios::app);
		assert(ofs.good());
		boost_archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(M);
	}

	void restore(Movies& M, std::string_view filename)
	{
		std::ifstream ifs(filename.data());
		assert(ifs.good());
		boost_archive::xml_iarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(M);
	}
	void execute()
	{
		using namespace std::string_literals;
		Movies PlayList;
		movie aMovie;
		aMovie.id = 9871;
		aMovie.title = "Forrest Gump"s;
		aMovie.year = 1994;
		aMovie.mins = 202;
		aMovie.Cast.Actors.push_back(role{ "Tom Hanks"s,"Forrest Gump"s });
		aMovie.Cast.Actors.push_back(role{ "Sally Field"s,"Mrs.Gump"s });
		aMovie.Cast.Actors.push_back(role{ "Robin Wright"s,"Jenny Curran"s });
		aMovie.Cast.Actors.push_back(role{ "Mykelti Williamson"s,"Bubba Blue"s });
		aMovie.Directors.Directors.push_back(director{ "Robert Zemeckis"s });
		aMovie.Writers.Writers.push_back(writer{ "Winston Groom"s });
		aMovie.Writers.Writers.push_back(writer{ "Eric Roth"s });
		movie sMovie;
		sMovie.id = 12751;
		sMovie.title = "Tarantula"s;
		sMovie.year = 2014;
		sMovie.mins = 100;
		sMovie.Cast.Actors.push_back(role{ "Chris Janet"s,"Laure Senge"s });
		sMovie.Cast.Actors.push_back(role{ "Walton Parks"s,"Tim Adams"s });
		sMovie.Cast.Actors.push_back(role{ "Robin Wright"s,"Tyler Yucks"s });
		sMovie.Cast.Actors.push_back(role{ "Williamson Frederick"s,"Bumbba T"s });
		sMovie.Directors.Directors.push_back(director{ "Valert Zemeckis"s });
		sMovie.Writers.Writers.push_back(writer{ "Winston Chum"s });
		sMovie.Writers.Writers.push_back(writer{ "Txiki Roth"s });
		PlayList.Catalog.push_back(sMovie);
		movie nMovie;
		nMovie.id = 13982;
		nMovie.title = "Queen Sugar"s;
		nMovie.year = 2021;
		nMovie.mins = 50;
		nMovie.Cast.Actors.push_back(role{ "Jefferson"s,"Rutina Wesley"s });
		nMovie.Cast.Actors.push_back(role{ "Marice"s,"Dawn Gardner"s });
		nMovie.Cast.Actors.push_back(role{ "John Rivalton"s,"Kofie Siroboe"s });
		nMovie.Cast.Actors.push_back(role{ "Theo"s,"Omar J Dorsey"s });
		nMovie.Directors.Directors.push_back(director{ "Nicholas L Asche"s });
		nMovie.Writers.Writers.push_back(writer{ "Kostas Mitoglou"s });
		nMovie.Writers.Writers.push_back(writer{ "Manolas P"s });
		PlayList.Catalog.push_back(nMovie);
		movie wMovie;
		wMovie.id = 15762;
		wMovie.title = "The Oval"s;
		wMovie.year = 2021;
		wMovie.mins = 50;
		wMovie.Cast.Actors.push_back(role{ "Nancy"s,"Ed Quinn"s });
		wMovie.Cast.Actors.push_back(role{ "Sam"s,"Kron Moore"s });
		wMovie.Cast.Actors.push_back(role{ "Richard"s,"Javon Johnson"s });
		wMovie.Cast.Actors.push_back(role{ "Donfred"s,"Ptosha Storey"s });
		wMovie.Directors.Directors.push_back(director{ "Vaughn W Hebron"s });
		wMovie.Writers.Writers.push_back(writer{ "Zaha Wilfire"s });
		wMovie.Writers.Writers.push_back(writer{ "Mack Toney"s });
		PlayList.Catalog.push_back(wMovie);
		movie fMovie;
		fMovie.id = 15762;
		fMovie.title = "The one"s;
		fMovie.year = 2001;
		fMovie.mins = 87;
		fMovie.Cast.Actors.push_back(role{ "Johnson"s,"Jet Li"s });
		fMovie.Cast.Actors.push_back(role{ "Kim"s,"Carla Gugino"s });
		fMovie.Cast.Actors.push_back(role{ "Wilder"s,"Delroy Lindo"s });
		fMovie.Cast.Actors.push_back(role{ "Bobby"s,"Jason Statham"s });
		fMovie.Directors.Directors.push_back(director{ "James Morrison"s });
		fMovie.Writers.Writers.push_back(writer{ "Zinger Feller"s });
		fMovie.Writers.Writers.push_back(writer{ "Paris Timmber"s });
		PlayList.Catalog.push_back(fMovie);
		std::string filename{ R"(C:\Users\hp\Desktop\test)"s };
		filename += "/Movie1.xml";
		//save(PlayList, filename);
		{
		Movies Another;
		restore(Another, filename);
		auto query = Select::select_if(Another.Catalog, [](const movie& Item)
			{
					return (Item.title);
			}, [](const movie& Item)
			{
				if (Item.year > 2020)
					return true;
				else
					return false;
			});
		auto query1 = Select::select(Another.Catalog, [](const movie& Item)
			{
				return (Item.Cast.Actors.back().Name);
			});
		std::copy(query.begin(), query.end(), std::ostream_iterator<decltype(query[0])>(std::cout, " "));
		std::cout << std::endl;
		std::copy(query1.begin(), query1.end(), std::ostream_iterator<decltype(query1[0])>(std::cout, ","));
		std::cout << std::endl;
		}
		
		std::cout << "END\n";
	}
}

namespace JsonSerialization
{
	namespace js = boost::json;
	using namespace js;
	struct role
	{
		std::string Star{};
		std::string Name{};
	};
	struct director
	{
		std::string Name{};
	};
	struct writer
	{
		std::string Name{};
	};
	struct cast
	{
		std::vector<role> Actors{};
	};
	struct directors
	{
		std::vector<director> Directors{};
	};
	struct writers
	{
		std::vector <writer> Writers{};
	};
	struct movie
	{
		unsigned id{};
		unsigned year{};
		unsigned mins{};
		std::string title{};
		cast Cast{};
		directors Directors{};
		writers Writers{};
	};
	struct Movies
	{
		std::vector<movie> Catalog;
	};
	void tag_invoke(js::value_from_tag, js::value& jv, role const& c)
	{
		jv = {
			{ "Star" , c.Star },
			{ "Name", c.Name }
		};
	}
	void tag_invoke(js::value_from_tag, js::value& jv, director const& c)
	{
		jv = {
			{ "Name", c.Name }
		};
	}
	void tag_invoke(js::value_from_tag, js::value& jv, writer const& c)
	{
		jv = {
			{ "Name", c.Name }
		};
	}
	void tag_invoke(js::value_from_tag, js::value& jv, cast const& c)
	{
		jv = {{"actor(s)",value_from(c.Actors)}};
	}
	void tag_invoke(js::value_from_tag, js::value& jv, directors const& c)
	{
		jv = { {"director(s)",value_from(c.Directors)} };
	}
	void tag_invoke(js::value_from_tag, js::value& jv, writers const& c)
	{
		jv = { {"writer(s)",value_from(c.Writers)} };
	}
	void tag_invoke(js::value_from_tag, js::value& jv, movie const& c)
	{
		jv = {
			{ "id" , c.id },
			{ "Title", c.title },
			{"year",c.year},
			{"min",value_from(c.mins)},
			{"Cast",value_from(c.Cast)},
			{"Directors",value_from(c.Directors)},
			{"Writers",value_from(c.Writers)},
		};
	}
	void tag_invoke(js::value_from_tag, js::value& jv, Movies const& c)
	{
		jv = { {"Movies",value_from(c.Catalog)} };
	}

	template<class T>
	void extract(object const& obj, T& t, string_view key)
	{
		t = value_to<T>(obj.at(key));
	}

	role tag_invoke(value_to_tag< role >, value const& jv)
	{
		object const& obj = jv.as_object();
		return role{
			value_to<std::string>(obj.at("Star")),
			value_to<std::string>(obj.at("Name"))
		};
	}

	director tag_invoke(value_to_tag< director >, value const& jv)
	{
		object const& obj = jv.as_object();
		return director{
			value_to<std::string>(obj.at("Name")),
		};
	}

	writer tag_invoke(value_to_tag< writer >, value const& jv)
	{
		object const& obj = jv.as_object();
		return writer{
			value_to<std::string>(obj.at("Name")),
		};
	}

	cast tag_invoke(value_to_tag< cast >, value const& jv)
	{
		object const& obj = jv.as_object();
		return cast{
			value_to<std::vector<role>>(obj.at("actor(s)")),
		};
	}

	directors tag_invoke(value_to_tag< directors >, value const& jv)
	{
		object const& obj = jv.as_object();
		return directors{
			value_to<std::vector<director>>(obj.at("director(s)")),
		};
	}

	writers tag_invoke(value_to_tag< writers >, value const& jv)
	{
		object const& obj = jv.as_object();
		return writers{
			value_to<std::vector<writer>>(obj.at("writer(s)")),
		};
	}

	movie tag_invoke(value_to_tag< movie >, value const& jv)
	{
		object const& obj = jv.as_object();
		return movie{
			value_to<unsigned>(obj.at("id")),
			value_to<unsigned>(obj.at("year")),
			value_to<unsigned>(obj.at("min")),
			value_to<std::string>(obj.at("Title")),
			value_to<cast>(obj.at("Cast")),
			value_to<directors>(obj.at("Directors")),
			value_to<writers>(obj.at("Writers"))
		};
	}
	Movies tag_invoke(value_to_tag< Movies >, value const& jv)
	{
		object const& obj = jv.as_object();
		return Movies{
			value_to<std::vector<movie>>(obj.at("Movies"))
		};
	}
	void save(const Movies& M, std::string_view filename)
	{
		std::ofstream ofs(filename.data(), std::ios::app);
		assert(ofs.good());
		ofs << serialize(value_from(M));
	}
	value read_json(std::istream& is, error_code& ec)
	{
		stream_parser p;
		std::string line;
		while (std::getline(is, line))
		{
			p.write(line, ec);
			if (ec)
				return nullptr;
		}
		p.finish(ec);
		if (ec)
			return nullptr;
		return p.release();
	}
	void restore(Movies& M, std::string_view filename)
	{
		std::ifstream ifs(filename.data());
		assert(ifs.good());
		error_code err;
		value jv;
		ifs >> jv;
		if (jv != nullptr)
		{
			M = value_to<Movies>(jv);
		}
			
	}
	void execute()
	{
		using namespace std::string_literals;
		Movies PlayList;
		movie aMovie;
		aMovie.id = 9871;
		aMovie.title = "Forrest Gump"s;
		aMovie.year = 1994;
		aMovie.mins = 202;
		aMovie.Cast.Actors.push_back(role{ "Tom Hanks"s,"Forrest Gump"s });
		aMovie.Cast.Actors.push_back(role{ "Sally Field"s,"Mrs.Gump"s });
		aMovie.Cast.Actors.push_back(role{ "Robin Wright"s,"Jenny Curran"s });
		aMovie.Cast.Actors.push_back(role{ "Mykelti Williamson"s,"Bubba Blue"s });
		aMovie.Directors.Directors.push_back(director{ "Robert Zemeckis"s });
		aMovie.Writers.Writers.push_back(writer{ "Winston Groom"s });
		aMovie.Writers.Writers.push_back(writer{ "Eric Roth"s });
		movie sMovie;
		sMovie.id = 12751;
		sMovie.title = "Tarantula"s;
		sMovie.year = 2014;
		sMovie.mins = 100;
		sMovie.Cast.Actors.push_back(role{ "Chris Janet"s,"Laure Senge"s });
		sMovie.Cast.Actors.push_back(role{ "Walton Parks"s,"Tim Adams"s });
		sMovie.Cast.Actors.push_back(role{ "Robin Wright"s,"Tyler Yucks"s });
		sMovie.Cast.Actors.push_back(role{ "Williamson Frederick"s,"Bumbba T"s });
		sMovie.Directors.Directors.push_back(director{ "Valert Zemeckis"s });
		sMovie.Writers.Writers.push_back(writer{ "Winston Chum"s });
		sMovie.Writers.Writers.push_back(writer{ "Txiki Roth"s });
		PlayList.Catalog.push_back(sMovie);
		movie nMovie;
		nMovie.id = 13982;
		nMovie.title = "Queen Sugar"s;
		nMovie.year = 2021;
		nMovie.mins = 50;
		nMovie.Cast.Actors.push_back(role{ "Jefferson"s,"Rutina Wesley"s });
		nMovie.Cast.Actors.push_back(role{ "Marice"s,"Dawn Gardner"s });
		nMovie.Cast.Actors.push_back(role{ "John Rivalton"s,"Kofie Siroboe"s });
		nMovie.Cast.Actors.push_back(role{ "Theo"s,"Omar J Dorsey"s });
		nMovie.Directors.Directors.push_back(director{ "Nicholas L Asche"s });
		nMovie.Writers.Writers.push_back(writer{ "Kostas Mitoglou"s });
		nMovie.Writers.Writers.push_back(writer{ "Manolas P"s });
		PlayList.Catalog.push_back(nMovie);
		movie wMovie;
		wMovie.id = 15762;
		wMovie.title = "The Oval"s;
		wMovie.year = 2021;
		wMovie.mins = 50;
		wMovie.Cast.Actors.push_back(role{ "Nancy"s,"Ed Quinn"s });
		wMovie.Cast.Actors.push_back(role{ "Sam"s,"Kron Moore"s });
		wMovie.Cast.Actors.push_back(role{ "Richard"s,"Javon Johnson"s });
		wMovie.Cast.Actors.push_back(role{ "Donfred"s,"Ptosha Storey"s });
		wMovie.Directors.Directors.push_back(director{ "Vaughn W Hebron"s });
		wMovie.Writers.Writers.push_back(writer{ "Zaha Wilfire"s });
		wMovie.Writers.Writers.push_back(writer{ "Mack Toney"s });
		PlayList.Catalog.push_back(wMovie);
		movie fMovie;
		fMovie.id = 15762;
		fMovie.title = "The one"s;
		fMovie.year = 2001;
		fMovie.mins = 87;
		fMovie.Cast.Actors.push_back(role{ "Johnson"s,"Jet Li"s });
		fMovie.Cast.Actors.push_back(role{ "Kim"s,"Carla Gugino"s });
		fMovie.Cast.Actors.push_back(role{ "Wilder"s,"Delroy Lindo"s });
		fMovie.Cast.Actors.push_back(role{ "Bobby"s,"Jason Statham"s });
		fMovie.Directors.Directors.push_back(director{ "James Morrison"s });
		fMovie.Writers.Writers.push_back(writer{ "Zinger Feller"s });
		fMovie.Writers.Writers.push_back(writer{ "Paris Timmber"s });
		PlayList.Catalog.push_back(fMovie);
		std::string filename{ R"(C:\Users\Philippe\Documents\Test)"s };
		filename += "/Movie.json";
		save(PlayList, filename);
		{
			Movies Another;
			restore(Another, filename);
			auto query = Select::select_if(Another.Catalog, [](const movie& Item)
				{
					return (Item.title);
				}, [](const movie& Item)
				{
					if (Item.year > 2020)
						return true;
					else
						return false;
				});
			auto query1 = Select::select(Another.Catalog, [](const movie& Item)
				{
					return (Item.Cast.Actors.back().Name);
				});
			std::copy(query.begin(), query.end(), std::ostream_iterator<decltype(query[0])>(std::cout, " "));
			std::cout << std::endl;
			std::copy(query1.begin(), query1.end(), std::ostream_iterator<decltype(query1[0])>(std::cout, ","));
			std::cout << std::endl;
		}
		Movies Copied;
		try
		{
			restore(Copied, filename);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
		std::cout << "END\n";
	}
}


