//
// Created by pc on 08-11-21.
//

#include "MainWindow.h"

#include "../State.h"
#include "../audio/AudioPlayer.h"
#include "../audio/SoundWindow.h"
#include "../fluid/FluidSettings.h"
#include "../thr/ThreadPool.h"
#include "../thr/ThreadSettings.h"
#include "AudioWidget.h"
#include "DispSettings.h"
#include "SettingsWidget.h"
#include "SmokeWidget.h"

#include <QKeyEvent>
#include <QTimer>

namespace app::disp {

    MainWindow::MainWindow() : m_smoke_widget(new SmokeWidget(this)), m_mode(MODE::NO_AUDIO) {
        setCentralWidget(m_smoke_widget);
        build_settings_widget();
        m_timer.start(5, this);
        resize(1000, 1000);
    }

    MainWindow::MainWindow(const QString& audio_file)
        : m_smoke_widget(new SmokeWidget(this)),
          m_audio_player(new audio::AudioPlayer()),
          m_sound_window(new audio::SoundWindow(m_audio_player.get())),
          m_audio_widget(new AudioWidget(this)),
          m_mode(MODE::WITH_AUDIO) {
        setCentralWidget(m_smoke_widget);
        m_audio_widget->show();
        m_audio_player->init(("../songs/" + audio_file).toStdString());
        m_audio_player->play();
        m_elapsed_timer.start();
        m_timer.start(5, this);
        resize(1000, 1000);
    }

    MainWindow::~MainWindow() = default;

    audio::SoundWindow* MainWindow::sound_window() {
        return m_sound_window.get();
    }

    void MainWindow::keyPressEvent(QKeyEvent* e) {
        switch (e->key()) {
            case Qt::Key::Key_Space:
                State::get().toggle_paused();
                m_audio_player->set_paused(State::get().is_paused());
                break;
            case Qt::Key::Key_Escape:
                m_smoke_widget->clear();
                break;
            default:
                break;
        }
    }

    void MainWindow::closeEvent(QCloseEvent* event) {
        m_settings_widget->close();
        QWidget::closeEvent(event);
    }

    void MainWindow::timerEvent(QTimerEvent* e) {
        Q_UNUSED(e)

        double elapsed_seconds = static_cast<double>(m_elapsed_timer.elapsed()) / 1000.0f;
        m_elapsed_timer.restart();
        if (State::get().is_paused())
            return;

        switch (m_mode) {
            case MODE::WITH_AUDIO:
                m_smoke_widget->handle_beat(m_sound_window->current_beat_intensity());
                m_smoke_widget->step(elapsed_seconds);
                m_sound_window->update_by_player(elapsed_seconds);
                m_audio_widget->update_widgets();
                break;
            case MODE::NO_AUDIO:
                m_smoke_widget->step(elapsed_seconds);
                break;
        }
    }

    void MainWindow::build_settings_widget() {
        m_settings_widget = new SettingsWidget();
        m_settings_widget->add_section("Simulation");
        m_settings_widget->add(
            "Force", app::fluid::g_force_input, 0.01f * app::fluid::g_force_input, 100 * app::fluid::g_force_input, false);
        m_settings_widget->add("Particles",
                               app::fluid::g_particle_input,
                               0.01f * app::fluid::g_particle_input,
                               100 * app::fluid::g_particle_input,
                               false);
        m_settings_widget->add("Visc",
                               app::fluid::g_viscosity_coefficient,
                               0.01f * app::fluid::g_viscosity_coefficient,
                               100 * app::fluid::g_viscosity_coefficient,
                               false);
        m_settings_widget->add("Diff",
                               app::fluid::g_diffusion_coefficient,
                               0.01f * app::fluid::g_diffusion_coefficient,
                               100 * app::fluid::g_diffusion_coefficient,
                               false);
        m_settings_widget->add("Time update_widgets", app::fluid::g_dt, 0.001, 0.025, true);

        m_settings_widget->add_section("Performance");
        m_settings_widget->add("Multi thread", thr::g_multi_thread);
        m_settings_widget->add("Thread count", thr::g_thread_count, 1, 32, [](size_t v) { thr::ThreadPool::get().resize(v); });

        m_settings_widget->add_section("Display");
        m_settings_widget->add("Power scale", g_power_scale, 0.1f, 2.0f, false);
        m_settings_widget->add("Clamp counts", g_clamp_count, 2);
        m_settings_widget->add("Clamp coef", g_clamp_coefficient, 0.0, 1.0, true);
        m_settings_widget->add("Invert colors", g_invert_colors);
        m_settings_widget->add("Color mode",
                               g_color_mode,
                               {{"gray", COLOR_MODE::GRAY},
                                {"hsl", COLOR_MODE::HSL},
                                {"water", COLOR_MODE::WATER},
                                {"test1", COLOR_MODE::TEST_1},
                                {"test2", COLOR_MODE::TEST_2}});
        m_settings_widget->add("Pixel s_size", g_pixel_size, 1);

        m_settings_widget->add_section("Shots");
        m_settings_widget->add("Boom", [this]() {
            m_smoke_widget->zoom(g_zoom_depth);
            m_smoke_widget->set_random_shape(0.8);
        });

        m_settings_widget->show();
    }

} // namespace app::disp