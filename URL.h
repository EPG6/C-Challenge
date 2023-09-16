#pragma once
#include <regex>
#include<string>

namespace my_URL
{
    using namespace std::string_literals;
    auto extract(std::string_view input)
    {
        auto an_URL{ std::string{ input } };
        auto markers{ std::vector{"Protocol: "s,"Domain: "s,"Path: "s, "Query: "s, "Fragment: "s} };
        auto URL_fragments{ std::vector(5,""s) };

        {
            auto pattern{ R"(^(http|https):(?://)(\w+\.\w+\.\w+)/([\w]+[\w_/-]*)\?([\w=&-]+)#([\w_/-]+)$)"s };
            auto rx = std::regex{ pattern,std::regex_constants::icase };
            /* auto valid{std::regex_match(an_URL,rx)};
             return valid;*/
            auto match = std::smatch{};
            if (std::regex_search(an_URL, match, rx))
            {
                auto optional{ "Port: "s };
                for (auto start{ match.begin() + 1 }; start != match.end(); start++)
                    URL_fragments[std::distance(match.begin() + 1, start)] = markers[std::distance(match.begin() + 1,
                        start)] + std::string{ (*start) };
                URL_fragments.insert(URL_fragments.begin() + 2, optional);
				return URL_fragments;
            }
        }
        {
            auto pattern{ R"(^(http|https):(?://)(\w+\.\w+\.\w+):([0-9]+)/([\w]+[\w_/-]*)\?([\w=&-]+)#([\w_/-]+)$)"s };
            auto rx = std::regex{ pattern,std::regex_constants::icase };
            auto match = std::smatch{};
            if (std::regex_search(an_URL, match, rx))
            {
                auto optional{ "Port: "s };
				markers.insert(markers.begin() + 2, optional);
                URL_fragments.resize(6, ""s);
                for (auto start{ match.begin() + 1 }; start != match.end(); start++)
                    URL_fragments[std::distance(match.begin() + 1, start)] = markers[std::distance(match.begin() + 1,
                        start)] + std::string{ (*start) };
            }
            return URL_fragments;
        }
    }
}