//
// Created by pc on 17-11-21.
//

#ifndef H_APP_PRF_PROFILE_H
#define H_APP_PRF_PROFILE_H

#include "ScopedTimer.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace app::prf {

    struct Profiler {
        static inline std::unordered_map<std::string, size_t> s_profiler_map;

        static void show() {
            std::vector<std::pair<std::string, size_t>> vec{s_profiler_map.begin(), s_profiler_map.end()};
            std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) { return b.second < a.second; });
            std::cout << "=============== PROFILER =====================================\n";
            for (const auto& [key, value] : vec) {
                std::cout << std::setw(25) << key << ":\t\t" << static_cast<double>(value) / 1000000.0 << "s\n";
            }
            std::cout << "\n";
        }
    };

    struct Helper {
        explicit Helper(std::string name) : m_scoped_timer(std::move(name)) {
        }

        ~Helper() {
            Profiler::s_profiler_map[m_scoped_timer.name()] += m_scoped_timer.elapsed();
        }

        app::prf::ScopedTimer m_scoped_timer;
    };
} // namespace app::prf

#define PROFILE_NAMED(x) app::prf::Helper h(x)
#define PROFILE_FUNCTION() PROFILE_NAMED(__func__)
#define START_PROFILING()                                                                                                        \
    for (auto& [key, value] : app::prf::Profiler::s_profiler_map)                                                                \
    value = 0
#define PRINT_PROFILE() app::prf::Profiler::show()

#endif // H_APP_PRF_PROFILE_H
