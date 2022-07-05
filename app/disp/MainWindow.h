//
// Created by pc on 08-11-21.
//

#ifndef H_APP_DISP_MAINWINDOW_H
#define H_APP_DISP_MAINWINDOW_H

#include "AudioWidget.h"

#include <QBasicTimer>
#include <QElapsedTimer>
#include <QMainWindow>

namespace app::audio {
    class AudioPlayer;
    class SoundWindow;
} // namespace app::audio

namespace app::disp {

    class SettingsWidget;
    class SmokeWidget;
    class AudioWidget;

    class MainWindow final : public QMainWindow {
        Q_OBJECT
        enum class MODE { WITH_AUDIO, NO_AUDIO };

      public:
        // Without audio
        MainWindow();
        // This constructor plays the audio file and uses it as input to the smoke widget
        explicit MainWindow(const QString& audio_file);
        ~MainWindow() override;

        audio::SoundWindow* sound_window();
        void                keyPressEvent(QKeyEvent* e) override;

      protected:
        void closeEvent(QCloseEvent* event) override;
        void timerEvent(QTimerEvent* e) override;

      private:
        void build_settings_widget();

        // These will be owned by Qt framework
        SmokeWidget*    m_smoke_widget    = nullptr;
        SettingsWidget* m_settings_widget = nullptr;
        // The following need to be in this order because m_audio_widget relies on m_sound_window and m_audio_player and
        // m_sound_window relies on m_audio_player
        std::unique_ptr<audio::AudioPlayer> m_audio_player;
        std::unique_ptr<audio::SoundWindow> m_sound_window;
        std::unique_ptr<AudioWidget>        m_audio_widget;
        MODE                                m_mode;
        QBasicTimer                         m_timer;
        QElapsedTimer                       m_elapsed_timer;
    };

} // namespace app::disp

#endif // H_APP_DISP_MAINWINDOW_H
