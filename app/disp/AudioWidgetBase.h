//
// Created by pc on 05-12-21.
//

#ifndef H_APP_DISP_AUDIOWIDGETBASE_H
#define H_APP_DISP_AUDIOWIDGETBASE_H

#include <QWidget>

namespace app::disp {

    class AudioWidgetBase : public QWidget {
        Q_OBJECT

      public:
        enum class BOUNDS_TYPE { NON_NEGATIVE, POSITIVE_AND_NEGATIVE };

        explicit AudioWidgetBase(QWidget* parent);

        void set_bounds_type(BOUNDS_TYPE type);

      protected:
        BOUNDS_TYPE m_type      = BOUNDS_TYPE::NON_NEGATIVE;
    };

} // namespace app::disp

#endif // H_APP_DISP_AUDIOWIDGETBASE_H
