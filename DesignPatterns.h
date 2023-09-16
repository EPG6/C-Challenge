#pragma once
#include "RandomString.h"
#include <chrono>
#include <bitset>
#include <map>
#include <variant>

namespace Password
{
	enum class Settings
	{
		basic = 2,
		medium = 4,
		advanced = 8,
	};

	bool validate(std::string_view sample,size_t minsize)
	{
		if (sample.size() >= minsize)
			return true;
		return false;
	}

	bool validate(std::string_view sample, size_t minsize, Settings settings)
	{
		bool valid{ false };
		auto func{ std::vector{isdigit,islower,isupper,ispunct} };
		if (validate(sample, minsize))
		{
			std::vector<bool> pool(4);
			size_t i{};
			for (const auto& symbol : sample)
			{
					for (auto& funcs: func)
					{
						if(!pool[i])
						{
							pool[i] = static_cast<bool>(std::invoke(funcs, symbol));
						}
						i++, i %= pool.size();
					}
					if (settings == Settings::basic && (pool[0] || pool[2]) && pool[1])
						return true;
					else if (settings == Settings::medium && pool[0] && pool[2] && pool[1])
						return true;
					else if (settings == Settings::advanced && pool[0] && pool[2] && pool[1] && pool[3])
						return true;
			}
			return valid;
		}
		return valid;
	}

	auto generate(size_t minsize, Settings setting)
	{
		using namespace std::string_literals;
		auto List{ std::vector{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"s,
		"abcdefghijklmnopqrstuvwxyz"s,"0123456789"s, R"(,?;.:/§!%*^£$-{+@\=_[}]{&~')"s} };
		std::random_device rd{};
		std::vector<int> seed_data(std::mt19937::state_size);
		std::generate(std::begin(seed_data), std::end(seed_data),
			std::ref(rd));
		std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
		auto eng = std::mt19937{ seq };
		auto dist1{ std::uniform_int_distribution{0,2} };
		if (setting == Settings::advanced)
		{
			dist1 = std::uniform_int_distribution{ 0,3 };
		}
		auto out{ ""s };
		for (size_t i{}; i < minsize; i++)
		{
			auto choice{ dist1(eng) };
			auto in{ eng() % List[choice].size() };
			out += List[choice][in];
		}
		return out;
	}
}

namespace SocialSecurityNumber
{
	namespace
	{
		
		auto prepare_generator()
		{
			std::random_device rd{};
			std::vector<int> seed_data(std::mt19937::state_size);
			std::generate(std::begin(seed_data), std::end(seed_data),
				std::ref(rd));
			std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
			return std::mt19937(seq);
		}
		unsigned convert_date(unsigned n_day, unsigned n_month, unsigned n_year)
		{
			unsigned result = n_day + n_month * 100 + n_year * 10000;
			return result;
		}
		bool valid_gender_N(short sex)
		{
			if (sex == 9 || sex == 7)
				return true;
			return false;
		}

		bool valid_gender_S(short sex)
		{
			if (sex == 1 || sex == 2)
				return true;
			return false;
		}
		template<typename T>
		auto convert(T input)
		{
			return static_cast<unsigned> (input);
		}
		template<typename T>
		auto iconvert(T input)
		{
			return static_cast<int> (input);
		}


	}
	namespace ch = std::chrono;
	class Northeria
	{
	private:
		std::mt19937 eng{ prepare_generator() };
		std::map<unsigned, bool> DateRegister{};
		std::map<unsigned, bool> NumberRegister{};
		const unsigned randomnumbersize = 100000;
		const unsigned SSNsize = 15;
		const unsigned factor = 11;
		//std::bitset<17> filter{};
		auto valid_random_number(unsigned& format)
		{
			unsigned somenumber{};
			while (true)
			{
				somenumber = eng() % randomnumbersize;
				if (DateRegister.find(format) == DateRegister.end())
				{
					NumberRegister[somenumber] = 1;
					break;
				}
				if (NumberRegister.find(somenumber) == NumberRegister.end())
				{
					NumberRegister[somenumber] = 1;
					break;
				}
			}
			return somenumber;
		}
	public:
		Northeria() = default;
		std::optional<size_t> generate(short gender, ch::year_month_day birthday) noexcept
		{
			std::optional<size_t> out;
			if (!valid_gender_N(gender))
				return out;
			if (!birthday.ok())
				return out;
			auto format{ convert_date(convert(birthday.day()),
				convert(birthday.month()), iconvert(birthday.year())) };
			unsigned somenumber{ valid_random_number(format) };
			auto tempout{ std::to_string(gender) + std::to_string(iconvert(birthday.year())) };
			if (convert(birthday.month()) < 10)
				tempout += (std::to_string(0) + std::to_string(convert(birthday.month())));
			else
				tempout += (std::to_string(convert(birthday.month())));
			if (convert(birthday.day()) < 10)
				tempout += (std::to_string(0) + std::to_string(convert(birthday.day())));
			else
				tempout += (std::to_string(convert(birthday.day())));
			auto num_str{ std::to_string(somenumber) };
			for (size_t y{ num_str.size() }; y < 5; y++)
				tempout.append("0");
			tempout += num_str;
			auto count{ SSNsize };
			auto total{ 0 };
			for (auto& el : tempout)
			{
				total += (std::stoi(std::string{el}) * count);
				count--;
			}
			auto last{ total % factor };
			tempout.append(std::to_string(last));
			out = std::stoull(tempout);
			return out;
		}

	};

	class Southeria
	{
	private:
		std::mt19937 eng{ prepare_generator() };
		std::map<unsigned, bool> DateRegister{};
		std::map<unsigned, bool> NumberRegister{};
		const unsigned randomnumbersize = 10000;
		const unsigned SSNsize = 14;
		const unsigned factor = 10;
		//std::bitset<17> filter{};
		auto valid_random_number(unsigned& format)
		{
			unsigned somenumber{};
			while (true)
			{
				somenumber = eng() % randomnumbersize;
				if (DateRegister.find(format) == DateRegister.end())
				{
					NumberRegister[somenumber] = 1;
					break;
				}
				if (NumberRegister.find(somenumber) == NumberRegister.end())
				{
					NumberRegister[somenumber] = 1;
					break;
				}
			}
			return somenumber;
		}
	public:
		Southeria() = default;
		std::optional<size_t> generate(short gender, ch::year_month_day birthday) noexcept
		{
			std::optional<size_t> out;
			if (!valid_gender_S(gender))
				return out;
			if (!birthday.ok())
				return out;
			auto format{ convert_date(convert(birthday.day()),
				convert(birthday.month()), iconvert(birthday.year())) };
			unsigned somenumber{valid_random_number(format)};
			auto tempout{ std::to_string(gender) + std::to_string(iconvert(birthday.year())) };
			if (convert(birthday.month()) < 10)
				tempout += (std::to_string(0) + std::to_string(convert(birthday.month())));
			else
				tempout += (std::to_string(convert(birthday.month())));
			if (convert(birthday.day()) < 10)
				tempout += (std::to_string(0) + std::to_string(convert(birthday.day())));
			else
				tempout += (std::to_string(convert(birthday.day())));
			auto num_str{ std::to_string(somenumber) };
			for (size_t y{ num_str.size() }; y < 4; y++)
				tempout.append("0");
			tempout += num_str;
			auto count{ SSNsize };
			auto total{ 0 };
			for (auto& el : tempout)
			{
				total += (std::stoi(std::string{ el }) * count);
				count--;
			}
			auto last{ total % factor };
			tempout.append(std::to_string(last));
			out = std::stoull(tempout);
			return out;
		}

	};
}

namespace ApprovalSystem
{
	namespace Status
	{
		struct Active 
		{
			unsigned allocated_sum;
		};
		struct Disabled{};
	}
	using state = std::variant<Status::Active, Status::Disabled>;

	namespace event
	{
		struct purchased
		{
			unsigned amount;
		};
		struct Reactivated
		{
			unsigned sum;
		};
	}

	state on_event(Status::Active available, event::purchased purchased) {
		available.allocated_sum -= purchased.amount;
		if (available.allocated_sum > 0)
			return available;
		return Status::Disabled{};
	}

	state on_event(Status::Disabled, event::Reactivated signal)
	{
		return Status::Active{ signal.sum };
	}
	template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
	template<class... Ts> overload(Ts...)->overload<Ts...>;
	
	struct employee_data
	{
		std::string Name{};
	};

	class Regular
	{
	public:
		Regular() = default;
		template <typename Event> void process_event(Event&& event) {
			state_ = std::visit(overload{
			[&] (const auto& State) requires std::is_same_v<
			decltype(on_event(State, std::forward<Event>(event))), state> {
			return on_event(State, std::forward<Event>(event));
			},
			[](const auto& unsupported_state) -> state {
			throw std::logic_error{"Unsupported state transition"};
			}
				},
				state_);
		}
		std::string report_current_state() {
			return std::visit(
				overload{ [](const Status::Active& state) -> std::string {
				return std::to_string(state.allocated_sum) +
				" units available";
				},
				[](const Status::Disabled) -> std::string {
				return "Regular account disabled";
				} },
				state_);
		}
		auto get_limit() const noexcept
		{
			return limit;
		}
	private:
		const unsigned limit{ 1000 };
		state state_{Status::Active{limit}};
	};

	class TeamManager
	{
	public:
		TeamManager() = default;
		template <typename Event> void process_event(Event&& event) {
			state_ = std::visit(overload{
			[&] (const auto& State) requires std::is_same_v<
			decltype(on_event(State, std::forward<Event>(event))), state> {
			return on_event(State, std::forward<Event>(event));
			},
			[](const auto& unsupported_state) -> state {
			throw std::logic_error{"Unsupported state transition"};
			}
				},
				state_);
		}
		std::string report_current_state() {
			return std::visit(
				overload{ [](const Status::Active& state) -> std::string {
				return std::to_string(state.allocated_sum) +
				" units available";
				},
				[](const Status::Disabled) -> std::string {
				return "TeamManager account disabled";
				} },
				state_);
		}
		auto get_limit() const noexcept
		{
			return limit;
		}
	private:
		const unsigned limit{ 10000 };
		state state_{ Status::Active{limit} };
	};

	class DepartmentManager
	{
	public:
		DepartmentManager() = default;
		template <typename Event> void process_event(Event&& event) {
			state_ = std::visit(overload{
			[&] (const auto& State) requires std::is_same_v<
			decltype(on_event(State, std::forward<Event>(event))), state> {
			return on_event(State, std::forward<Event>(event));
			},
			[](const auto& unsupported_state) -> state {
			throw std::logic_error{"Unsupported state transition"};
			}
				},
				state_);
		}
		std::string report_current_state() {
			return std::visit(
				overload{ [](const Status::Active& state) -> std::string {
				return std::to_string(state.allocated_sum) +
				" units available";
				},
				[](const Status::Disabled) -> std::string {
				return "DepartmentManager account disabled";
				} },
				state_);
		}
		auto get_limit() const noexcept
		{
			return limit;
		}
	private:
		const unsigned limit{ 100000 };
		state state_{ Status::Active{limit} };
	};
	
}
