//
// Created by pc on 05-12-21.
//

#include "HistoryWidget.h"

#include <QPainter>
#include <iostream>

namespace app::disp {

    HistoryWidget::HistoryWidget(QWidget* parent, float scale, QString name)
        : AudioWidgetBase(parent), m_scale(scale), m_name(std::move(name)) {
    }

    void HistoryWidget::set_buffer(const HistoryBuffer& buffer) {
        m_history_buffer = buffer;
        for (size_t i = 0; i != HistoryBuffer::s_size; ++i)
            m_history_buffer[i] *= m_scale;
        repaint();
    }

    void HistoryWidget::paintEvent([[maybe_unused]] QPaintEvent* event) {
        QPainter painter(this);
        painter.setPen(QPen{QColor{100, 100, 100}});
        painter.drawLine(0, QWidget::height() / 2, QWidget::width(), QWidget::height() / 2);

        if (m_type == BOUNDS_TYPE::NON_NEGATIVE)
            draw_non_negative(painter);
        else
            draw_positive_and_negative(painter);

        draw_scale(painter);
        QWidget::paintEvent(event);
    }

    void HistoryWidget::draw_scale(QPainter& painter) {
        painter.setPen(QPen{QColor{255, 255, 255}});
        if (m_type == AudioWidgetBase::BOUNDS_TYPE::NON_NEGATIVE) {
            painter.drawText(0, QWidget::height() - 5, "0");
            painter.drawText(0, 15, QString::number(static_cast<float>(QWidget::height()) / m_scale));
        }
    }

    void HistoryWidget::draw_non_negative(QPainter& painter) {
        const int width           = QWidget::width();
        const int height          = QWidget::height();
        const int buffer_length   = HistoryBuffer::s_size;
        const int rectangle_width = (width + buffer_length - 1) / buffer_length;

        for (int i = 0; i != buffer_length; ++i)
            painter.fillRect(i * width / (buffer_length + 1),
                             height - static_cast<int>(m_history_buffer[i]),
                             rectangle_width + 1,
                             static_cast<int>(m_history_buffer[i]),
                             QBrush{QColor{0, 32, 128}});
    }

    void HistoryWidget::draw_positive_and_negative(QPainter& painter) {
        const int width           = QWidget::width();
        const int height          = QWidget::height();
        const int buffer_length   = HistoryBuffer::s_size;
        const int rectangle_width = (width + buffer_length - 1) / buffer_length;

        for (int i = 0; i != buffer_length; ++i)
            painter.fillRect(i * width / (buffer_length + 1),
                             height / 2 - static_cast<int>(m_history_buffer[i]),
                             rectangle_width,
                             static_cast<int>(m_history_buffer[i]),
                             QBrush{QColor{0, 32, 128}});
    }
} // namespace app::disp