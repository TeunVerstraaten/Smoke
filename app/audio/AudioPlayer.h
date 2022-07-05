//
// Created by pc on 05-11-21.
//

#ifndef H_APP_AUDIO_AUDIOPLAYER_H
#define H_APP_AUDIO_AUDIOPLAYER_H

#include "../type/BufferTypes.h"

#include <SFML/Audio.hpp>

namespace app::audio {

    class AudioPlayer {

      public:
        AudioPlayer() = default;

        bool                      init(const std::string& path_to_file);
        void                      play();
        void                      pause();
        void                      set_paused(bool should_pause);
        [[nodiscard]] double      duration() const;
        [[nodiscard]] size_t      current_offset() const;
        [[nodiscard]] size_t      sample_rate() const;
        [[nodiscard]] AudioBuffer normalized_buffer(size_t current_offset) const;

      private:
        bool            m_is_paused   = true;
        size_t          m_sample_rate = 0;
        sf::Sound       m_sound{};
        sf::SoundBuffer m_sound_buffer{};
    };

} // namespace app::audio

#endif // H_APP_AUDIO_AUDIOPLAYER_H
