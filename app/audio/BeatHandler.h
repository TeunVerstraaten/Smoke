//
// Created by pc on 20-6-22.
//

#ifndef H_APP_AUDIO_BEATHANDLER_H
#define H_APP_AUDIO_BEATHANDLER_H

#include <cstddef>

namespace app::audio {

    class BeatHandler {

      public:
        void                 set_beat_score(double beat_score);
        void                 update(double elapsed_seconds);
        [[nodiscard]] double intensity() const;
        [[nodiscard]] bool   was_just_blocked() const;
        [[nodiscard]] double current_beat_impulse() const;

      private:
        void handle_coming_beat(double beat_score);
        void check_for_new_beat(double beat_score);

        bool   m_is_blocked              = false;
        bool   m_was_just_blocked        = false;
        bool   m_beat_is_coming          = false;
        double m_intensity               = 0.0f;
        double m_beat_cut_off            = 0.3f;
        double m_running_average         = 0.0f;
        double m_block_seconds_remaining = 0;
        size_t m_wait_until_force        = 10;
    };

} // namespace app::audio

#endif // H_APP_AUDIO_BEATHANDLER_H
