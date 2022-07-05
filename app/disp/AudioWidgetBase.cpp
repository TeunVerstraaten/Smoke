//
// Created by pc on 05-12-21.
//

#include "AudioWidgetBase.h"

namespace app::disp {

    AudioWidgetBase::AudioWidgetBase(QWidget* parent) : QWidget(parent) {
        setFixedHeight(140);
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor{158, 153, 175});
        setAutoFillBackground(true);
        setPalette(pal);
    }

    void AudioWidgetBase::set_bounds_type(AudioWidgetBase::BOUNDS_TYPE type) {
        m_type = type;
    }

} // namespace app::disp