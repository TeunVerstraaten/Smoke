//
// Created by pc on 08-11-21.
//

#include "SmokeRenderer.h"

#include "../fluid/Fluid.cuh"
#include "../prf/Profile.h"
#include "../thr/ThreadPool.h"
#include "../thr/ThreadSettings.h"
#include "DispSettings.h"
#include "SmokeShader.h"

namespace app::disp {

    SmokeRenderer::SmokeRenderer() {
        m_shader = std::unique_ptr<ShaderBase>(new SmokeShader);
    }

    void SmokeRenderer::fill_quad_pixel_thread(size_t start, size_t end, const fluid::Fluid& fluid) {
        for (size_t i = 0; i != m_horizontal_sample_points; ++i) {
            float i_frac = static_cast<float>(i) / static_cast<float>(m_horizontal_sample_points);
            for (size_t j = start; j != end; ++j) {
                float        j_frac        = static_cast<float>(j) / static_cast<float>(m_vertical_sample_points);
                const size_t index         = 5 * (i * m_vertical_sample_points + j);
                m_quad_vertices[index]     = 2 * i_frac - 1;
                m_quad_vertices[index + 1] = 2 * j_frac - 1;
                m_quad_vertices[index + 2] = fluid.sample_density_at(i_frac, j_frac);
                m_quad_vertices[index + 3] = fluid.sample_u_at(i_frac, j_frac);
                m_quad_vertices[index + 4] = fluid.sample_v_at(i_frac, j_frac);
            }
        }
    }

    void SmokeRenderer::fill(const fluid::Fluid& fluid) {
        if (not thr::g_multi_thread)
            fill_quad_pixel_thread(0, m_vertical_sample_points, fluid);
        else {
            for (size_t thread_idx = 0; thread_idx != thr::g_thread_count; ++thread_idx) {
                thr::ThreadPool::get().add([&, thread_idx] {
                    const size_t start = thread_idx * m_vertical_sample_points / thr::g_thread_count;
                    const size_t end   = (thread_idx + 1) * m_vertical_sample_points / thr::g_thread_count;
                    fill_quad_pixel_thread(start, end, fluid);
                });
            }
            thr::ThreadPool::get().wait();
        }
    }

    void SmokeRenderer::set_sample_points(size_t width, size_t height) {
        m_horizontal_sample_points = (width + 2 * g_pixel_size) / std::max(1ul, g_pixel_size - 1);
        m_vertical_sample_points   = (height + 2 * g_pixel_size) / std::max(1ul, g_pixel_size - 1);

        m_quad_vertices.resize(5 * m_horizontal_sample_points * m_vertical_sample_points);
        m_quad_indices.resize(m_horizontal_sample_points * m_vertical_sample_points);

        for (size_t i = 0; i != m_horizontal_sample_points; ++i)
            for (size_t j = 0; j != m_vertical_sample_points; ++j)
                m_quad_indices[i * m_vertical_sample_points + j] = i * m_vertical_sample_points + j;
    }

    void SmokeRenderer::resize(size_t width, size_t height) {
        dynamic_cast<SmokeShader*>(m_shader.get())->resize(width, height);
    }

} // namespace app::disp
