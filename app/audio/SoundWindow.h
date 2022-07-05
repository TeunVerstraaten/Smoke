//
// Created by pc on 05-11-21.
//

#ifndef H_APP_AUDIO_SOUNDWINDOW_H
#define H_APP_AUDIO_SOUNDWINDOW_H

#include "../type/BufferTypes.h"
#include "../type/CircularBuffer.h"
#include "../type/Complex.h"
#include "../type/LinearBuffer.h"
#include "BeatHandler.h"

#include <SFML/System/Clock.hpp>

namespace app::audio {

    class AudioPlayer;

    class SoundWindow {

      public:
        explicit SoundWindow(AudioPlayer* audio_player);

        void                                 update_by_player(double elapsed_seconds);
        void                                 update_by_time_point(double current_time_seconds, double elapsed_seconds);
        [[nodiscard]] double                 current_beat_intensity() const;
        [[nodiscard]] const HistoryBuffer&   waveform() const;
        [[nodiscard]] const DftBufferBuffer& dft_buffers() const;
        [[nodiscard]] const HistoryBuffer&   low_beat_buffer() const;
        [[nodiscard]] const HistoryBuffer&   mid_beat_buffer() const;
        [[nodiscard]] const HistoryBuffer&   high_beat_buffer() const;

      private:
        void   process_buffer(const AudioBuffer& buffer);
        void   handle_energy(const AudioBuffer& buffer);
        void   set_waveform_value(const AudioBuffer& buffer);
        void   update_beat_handlers(double elapsed_seconds);
        double energy_difference(size_t i_start, size_t i_end);

        audio::AudioPlayer* m_audio_player = nullptr;
        HistoryBuffer       m_waveform{};
        DftBufferBuffer     m_dft_buffers{};
        DftAverageBuffer    m_averaged_dft_buffers{};
        HistoryBuffer       m_low_beat_buffer{};
        HistoryBuffer       m_mid_beat_buffer{};
        HistoryBuffer       m_high_beat_buffer{};
        BeatHandler         m_low_beat_handler;
        BeatHandler         m_mid_beat_handler;
        BeatHandler         m_high_beat_handler;
    };

} // namespace app::audio

#endif // H_APP_AUDIO_SOUNDWINDOW_H
