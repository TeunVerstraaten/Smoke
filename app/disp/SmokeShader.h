//
// Created by pc on 08-11-21.
//

#ifndef H_APP_DISP_SMOKESHADER_H
#define H_APP_DISP_SMOKESHADER_H

#include "ShaderBase.h"

namespace app::fluid {
    class Fluid;
}

namespace app::disp {

    class SmokeShader : public ShaderBase {

      public:
        bool init() override;
        void set_uniforms() override;
        void resize(size_t width, size_t height);

      private:
        size_t m_width;
        size_t m_height;
    };

} // namespace app::disp

#endif // H_APP_DISP_SMOKESHADER_H
