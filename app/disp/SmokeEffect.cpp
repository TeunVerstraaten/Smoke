//
// Created by pc on 21-6-22.
//

#include "SmokeEffect.h"

#include "../fluid/FluidSettings.h"
#include "../math/Math.h"
#include "DispSettings.h"
#include "SmokeWidget.h"

namespace app::disp {

    SmokeEffectDetail SmokeEffectManager::clamp_coefficient_slow_upwards() {
        double p      = 0.2;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(ManipulatorBase<float>(9.0f, 0.3f, 0.9f, &g_clamp_coefficient));
        };

        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::set_polygon() {
        double p      = 110.3;
        auto   effect = [](SmokeWidget& smoke_widget, double intensity) {
            smoke_widget.zoom(intensity / 20.0);
            smoke_widget.set_random_shape(intensity);
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::switch_color_mode() {
        double p      = 0.25;
        auto   effect = []([[maybe_unused]] SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            const auto current_mode = g_color_mode;
            while (g_color_mode == current_mode)
                g_color_mode =
                    static_cast<COLOR_MODE>(math::random_number_in_range(0, static_cast<int>(COLOR_MODE::NUM_MODES) - 1));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::invert_colors() {
        double p      = 0.2;
        auto   effect = []([[maybe_unused]] SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            g_invert_colors = !g_invert_colors;
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::clamp_coefficient_slow_downwards() {
        double p      = 0.3;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(ManipulatorBase<float>(5.0f, 0.8f, 0.0f, &g_clamp_coefficient));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::clamp_count_fast() {
        double p      = 0.4;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<size_t>(0.3f * static_cast<float>(intensity), 6, g_clamp_count, &g_clamp_count));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::power_scale_fast() {
        double p      = 0.59;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<float>(0.7f * static_cast<float>(intensity), 0.2f, g_power_scale, &g_power_scale));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::clamp_coefficient_fast() {
        double p      = 0.3;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<float>(0.6f * static_cast<float>(intensity), 0.9f, g_clamp_coefficient, &g_clamp_coefficient));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::pixel_size() {
        double p      = 0.2;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<size_t>(0.5f * static_cast<float>(intensity), 16, 4, &g_pixel_size));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::color_wash_up() {
        double p      = 0.1;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<float>(0.6f * static_cast<float>(intensity), 0.0, 0.2, &g_color_wash));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::color_wash_down() {
        double p      = 0.1;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<float>(0.6f * static_cast<float>(intensity), 0.2, 0.0, &g_color_wash));
        };
        return {effect, p};
    }

    SmokeEffectDetail SmokeEffectManager::time_slow_down() {
        double p      = 0.4;
        auto   effect = [](SmokeWidget& smoke_widget, [[maybe_unused]] double intensity) {
            smoke_widget.try_adding_manipulator(
                ManipulatorBase<float>(0.9f * static_cast<float>(intensity), 0.002f, 0.005f, &fluid::g_dt));
        };
        return {effect, p};
    }

    std::vector<SmokeEffectDetail> SmokeEffectManager::s_effects = {clamp_coefficient_slow_upwards(),
                                                                    set_polygon(),
                                                                    switch_color_mode(),
                                                                    invert_colors(),
                                                                    clamp_coefficient_slow_downwards(),
                                                                    clamp_count_fast(),
                                                                    power_scale_fast(),
                                                                    clamp_coefficient_fast(),
                                                                    pixel_size(),
                                                                    color_wash_down(),
                                                                    color_wash_up(),
                                                                    time_slow_down()};

} // namespace app::disp
