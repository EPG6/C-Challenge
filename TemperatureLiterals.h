#pragma once
#include <iostream>

namespace temperature_literals
{
	enum class unit
	{
		degrees,
		fahrenheit,
		kelvin,
	};

	template <unit U>
	class temperature
	{
		const double value;
	public:
		constexpr explicit temperature(double const a) : value(a) {}

		explicit operator double() const { return value; }
	};
	template <unit U>
	constexpr temperature<U> operator+(temperature<U> const& q1, temperature<U> const& q2)
	{
		return temperature<U>(static_cast<double>(q1) + static_cast<double>(q2));
	}

	template <unit U>
	constexpr temperature<U> operator-(temperature<U> const& q1, temperature<U> const& q2)
	{
		return temperature<U>(static_cast<double>(q1) - static_cast<double>(q2));
	}
	namespace temperature_conversion
	{
		 temperature<unit::degrees> from_kelvin_to_degrees(temperature<unit::kelvin> kelvinscale)
		{
			auto temp{ static_cast<double>(kelvinscale) };
			temp -= 273;
			return temperature<unit::degrees>{temp};
		}

		 temperature<unit::degrees> from_fahrenheit_to_degrees(temperature<unit::fahrenheit> fahrenheitscale)
		{
			auto temp{ static_cast<double>(fahrenheitscale) };
			temp -= 32;
			temp *= (5.0 / 9);
			return temperature<unit::degrees>{temp};
		}

		 temperature<unit::fahrenheit> from_degrees_to_fahrenheit(temperature<unit::degrees> degreesscale)
		{
			auto temp{ static_cast<double>(degreesscale) };
			temp *= (9.0 / 5);
			temp += 32;
			return temperature<unit::fahrenheit>{temp};
		}

	    temperature<unit::fahrenheit> from_kelvin_to_fahrenheit(temperature<unit::kelvin> kelvinscale)
		{
			auto temp{ from_kelvin_to_degrees(kelvinscale) };
			return from_degrees_to_fahrenheit(temp);
		}

	    temperature<unit::kelvin> from_degrees_to_kelvin(temperature<unit::degrees> degreesscale)
		{
			auto temp{ static_cast<double>(degreesscale) };
			temp += 273;
			return temperature<unit::kelvin>{temp};
		}

	    temperature<unit::kelvin> from_fahrenheit_to_kelvin(temperature<unit::fahrenheit> fahrenheitscale)
		{
			auto temp{ from_fahrenheit_to_degrees(fahrenheitscale) };
			return from_degrees_to_kelvin(temp);
		}
	}
	namespace unit_literals
	{
		constexpr temperature<unit::degrees> operator "" _deg(long double const amount)
		{
			return temperature<unit::degrees> {static_cast<double>(amount)};
		}

		constexpr temperature<unit::degrees> operator "" _deg(unsigned long long const amount)
		{
			return temperature<unit::degrees> {static_cast<double>(amount)};
		}

		constexpr temperature<unit::fahrenheit> operator "" _f(long double const amount)
		{
			return temperature<unit::fahrenheit> {static_cast<double>(amount)};
		}

		constexpr temperature<unit::kelvin> operator "" _k(long double const amount)
		{
			return temperature<unit::kelvin> {static_cast<double>(amount)};
		}

		constexpr temperature<unit::kelvin> operator "" _k(unsigned long long const amount)
		{
			return temperature<unit::kelvin> {static_cast<double>(amount)};
		}

		constexpr temperature<unit::fahrenheit> operator "" _f(unsigned long long const amount)
		{
			return temperature<unit::fahrenheit> {static_cast<double>(amount)};
		}
	}
	void execute()
	{
		using namespace unit_literals;
		using namespace temperature_conversion;
		auto temp1{ 15_deg };
		auto temp2{ 27_deg };
		auto temp3{ 72_f };
		auto temp4{ 122_f };
		auto temp5{ 373_k };
		auto temp6{ 173_k };
		std::cout << static_cast<double>(temp1 + temp2) <<" ";
		std::cout << static_cast<double>(temp3 + temp4) <<" ";
		std::cout << static_cast<double>(temp5 + temp6) <<" ";
		std::cout<<static_cast<double>(from_degrees_to_kelvin(temp1)) <<" ";
		std::cout << static_cast<double>(from_degrees_to_fahrenheit(temp2)) <<" ";
		std::cout << static_cast<double>(from_fahrenheit_to_degrees(temp3)) <<" ";
		std::cout << static_cast<double>(from_fahrenheit_to_kelvin(temp4)) <<" ";
		std::cout << static_cast<double>(from_kelvin_to_degrees(temp5)) <<" ";
		std::cout << static_cast<double>(from_kelvin_to_fahrenheit(temp6)) <<" ";

	}
}