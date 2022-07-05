//
// Created by pc on 03-11-21.
//

#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace app::fluid {

    struct IntFrac {
        int   integer_part;
        float fractional_part;
    };

    static IntFrac mod_one(float x) {
        float i;
        float f = std::modf(x, &i);
        return {static_cast<int>(std::round(i)), f};
    }

    Matrix::Row<float> Matrix::operator[](size_t row) {
        assert(row < g_point_count);
        return Row<float>{m_array.data() + g_point_count * row};
    }

    Matrix::Row<const float> Matrix::operator[](size_t row) const {
        assert(row < g_point_count);
        return Row<const float>{m_array.data() + g_point_count * row};
    }

    float Matrix::sample_at(float x, float y) const {
        assert(x <= 1.0f);
        assert(x >= 0.0f);
        assert(y <= 1.0f);
        assert(y >= 0.0f);
        const auto ri  = mod_one(x * (g_point_count - 1));
        const auto rj  = mod_one(y * (g_point_count - 1));
        const auto i   = ri.integer_part;
        const auto f_i = ri.fractional_part;
        const auto j   = rj.integer_part;
        const auto f_j = rj.fractional_part;

        // Bi-linear interpolation
        return (*this)[i][j] * (1.0f - f_i) * (1.0f - f_j) + (*this)[i + 1][j] * f_i * (1.0f - f_j) +
               (*this)[i + 1][j + 1] * f_i * f_j + (*this)[i][j + 1] * (1.0f - f_i) * f_j;
    }

    Matrix& Matrix::operator+=(const Matrix& rhs) {
        assert(m_array.size() == rhs.m_array.size());
        const auto& rhs_array = rhs.m_array;
        auto        rhs_it    = rhs_array.cbegin();
        for (auto it = m_array.begin(); it != m_array.end(); ++it, ++rhs_it)
            *it += *rhs_it;

        return *this;
    }

    float* Matrix::data() {
        return m_array.data();
    }

    float Matrix::max() const {
        return *std::max_element(m_array.begin(), m_array.end());
    }

    float Matrix::min() const {
        return *std::min_element(m_array.begin(), m_array.end());
    }

    Matrix& Matrix::operator*=(float multiplier) {
        for (auto& el : m_array)
            el *= multiplier;
        return *this;
    }
} // namespace app::fluid