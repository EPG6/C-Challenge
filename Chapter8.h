#pragma once
#include <iostream>
#include "DesignPatterns.h"
#include <climits>

namespace Chapter8
{
	template <typename T>
	void print_type_properties()
	{
		std::cout
			<< "min="
			<< std::numeric_limits<T>::min() << '\n'
			<< "max="
			<< std::numeric_limits<T>::max() << '\n'
			<< "bits="
			<< std::numeric_limits<T>::digits << '\n'
			<< "decdigits="
			<< std::numeric_limits<T>::digits10 << '\n'
			<< "integral="
			<< std::numeric_limits<T>::is_integer << '\n'
			<< "signed="
			<< std::numeric_limits<T>::is_signed << '\n'
			<< "exact="
			<< std::numeric_limits<T>::is_exact << '\n'
			<< "infinity="
			<< std::numeric_limits<T>::has_infinity << '\n';
	}
	void execute()
	{
		/*{
			std::cout << Password::validate(StringGenerate::somestring(), 8) << std::endl;
			std::cout << Password::validate(StringGenerate::somestring(), 17) << std::endl;
			auto password{ StringGenerate::somestring(20) };
			password.append(":");
			std::cout << password << std::endl;
			std::cout << Password::validate(password, 17, Password::Settings::advanced) << std::endl;
			std::cout << Password::generate(15, Password::Settings::advanced);
		}*/
		/*{
			using namespace std::string_literals;
			using namespace std::chrono;
			std::stringstream ss{ "2012-05-17"s };
			year_month_day smday;
			from_stream(ss, "%F", smday);
			SocialSecurityNumber::Northeria Comp;
			SocialSecurityNumber::Southeria Comp1;

			auto SSN1 = Comp.generate(9, smday);
			auto SSN2 = Comp1.generate(1, smday);
			if(SSN1.has_value())
				std::cout << SSN1.value() << std::endl;
			if (SSN2.has_value())
				std::cout << SSN2.value() << std::endl;
		}*/
		{
			using namespace ApprovalSystem;
			Regular employee;
			std::cout << employee.report_current_state() << std::endl;
			employee.process_event(event::purchased {550});
			std::cout << employee.report_current_state() << std::endl;
			employee.process_event(event::purchased {450});
			std::cout << employee.report_current_state() << std::endl;
			employee.process_event(event::Reactivated {employee.get_limit()});
			std::cout << employee.report_current_state() << std::endl;
			std::cout << "____________" << std::endl;
			TeamManager manager;
			std::cout << manager.report_current_state() << std::endl;
			manager.process_event(event::purchased {5500});
			std::cout << manager.report_current_state() << std::endl;
			manager.process_event(event::purchased {4500});
			std::cout << manager.report_current_state() << std::endl;
			manager.process_event(event::Reactivated {manager.get_limit()});
			std::cout << manager.report_current_state() << std::endl;
			std::cout << "____________" << std::endl;
			DepartmentManager Manager;
			std::cout << Manager.report_current_state() << std::endl;
			Manager.process_event(event::purchased {55000});
			std::cout << Manager.report_current_state() << std::endl;
			Manager.process_event(event::purchased {45000});
			std::cout << Manager.report_current_state() << std::endl;
			Manager.process_event(event::Reactivated {Manager.get_limit()});
			std::cout << Manager.report_current_state() << std::endl;
		}
	}
	
}