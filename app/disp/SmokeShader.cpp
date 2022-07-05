//
// Created by pc on 08-11-21.
//

#include "SmokeShader.h"

#include "../fluid/Fluid.cuh"
#include "DispSettings.h"

namespace app::disp {

    bool SmokeShader::init() {
        return ShaderBase::init(":/SmokeVertexShader.glsl", ":/SmokeFragmentShader.glsl");
    }

    void SmokeShader::set_uniforms() {
        m_program.setUniformValue("time", s_time);
        m_program.setUniformValue("zoom", 1.0f + s_zoom);
        m_program.setUniformValue("color_mode", static_cast<int>(g_color_mode));
        m_program.setUniformValue("invert_colors", g_invert_colors);
        m_program.setUniformValue("clamp_coefficient", g_clamp_coefficient);
        m_program.setUniformValue("clamp_count", static_cast<int>(g_clamp_count));
        m_program.setUniformValue("power_scale", g_power_scale);
        m_program.setUniformValue("color_wash", g_color_wash);
        m_program.setUniformValue("width", static_cast<int>(m_width));
        m_program.setUniformValue("height", static_cast<int>(m_height));
    }

    void SmokeShader::resize(size_t width, size_t height) {
        m_width  = width;
        m_height = height;
    }

} // namespace app::disp
