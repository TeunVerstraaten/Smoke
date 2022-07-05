//
// Created by pc on 03-11-21.
//

#ifndef H_FLUID_MATRIX_H
#define H_FLUID_MATRIX_H

#include "FluidSettings.h"

#include <array>
#include <cassert>

namespace app::fluid {

    class Matrix {

      public:
        template <class T>
        struct Row {
            T& operator[](size_t index) const {
                assert(index < g_point_count);
                return *(m_p + index);
            }
            T* m_p;
        };
        [[nodiscard]] Row<float>       operator[](size_t row);
        [[nodiscard]] Row<const float> operator[](size_t row) const;
        [[nodiscard]] float*           data();
        [[nodiscard]] float            sample_at(float x, float y) const;
        [[nodiscard]] float            max() const;
        [[nodiscard]] float            min() const;

        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator*=(float multiplier);

      private:
        std::array<float, g_point_count * g_point_count> m_array;
    };
} // namespace app::fluid

#endif // H_FLUID_MATRIX_H
