//
// Created by pc on 17-11-21.
//

#ifndef H_APP_DISP_DISPSETTINGS_H
#define H_APP_DISP_DISPSETTINGS_H

#include <cstddef>

namespace app::disp {

    enum class COLOR_MODE : int { GRAY = 0, HSL = 1, WATER = 2, TEST_1 = 3, TEST_2 = 4, NUM_MODES = 5 };

    extern COLOR_MODE g_color_mode;
    extern bool       g_invert_colors;
    extern float      g_zoom_depth;
    extern float      g_zoom_decay;
    extern float      g_clamp_coefficient;
    extern float      g_power_scale;
    extern size_t     g_pixel_size;
    extern size_t     g_clamp_count;
    extern float      g_color_wash;

} // namespace app::disp

#endif // H_APP_DISP_DISPSETTINGS_H
