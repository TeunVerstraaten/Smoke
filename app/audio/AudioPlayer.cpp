//
// Created by pc on 05-11-21.
//

#include "AudioPlayer.h"

#include "../type/LinearBuffer.h"

#include <iostream>

namespace app::audio {

    bool AudioPlayer::init(const std::string& path_to_file) {
        if (not m_sound_buffer.loadFromFile(path_to_file))
            return false;

        const auto total_sample_count = m_sound_buffer.getSampleCount();
        auto*      samples            = m_sound_buffer.getSamples();
        unsigned   max                = 0;
        for (size_t i = 0; i != total_sample_count; ++i) {
            const auto current = std::abs(*(samples + i));
            if (current > static_cast<int>(max))
                max = current;
        }
        m_sound.setBuffer(m_sound_buffer);
        m_sample_rate = m_sound_buffer.getSampleRate() * m_sound_buffer.getChannelCount();
        m_sound.setLoop(true);
        return true;
    }

    void AudioPlayer::play() {
        if (m_is_paused) {
            m_sound.play();
            m_is_paused = false;
        }
    }

    void AudioPlayer::pause() {
        if (not m_is_paused) {
            m_sound.pause();
            m_is_paused = true;
        }
    }

    void AudioPlayer::set_paused(bool should_pause) {
        if (should_pause)
            pause();
        else
            play();
    }

    double AudioPlayer::duration() const {
        return static_cast<double>(m_sound_buffer.getSampleCount()) / static_cast<double>(m_sample_rate);
    }

    size_t AudioPlayer::current_offset() const {
        return  static_cast<size_t>(m_sound.getPlayingOffset().asSeconds() * static_cast<float>(m_sample_rate));
    }

    size_t AudioPlayer::sample_rate() const {
        return m_sample_rate;
    }

     AudioBuffer AudioPlayer::normalized_buffer(size_t offset) const {
        if (offset >  AudioBuffer::s_size)
            offset -=  AudioBuffer::s_size;

        const size_t total_sample_count = m_sound_buffer.getSampleCount();
        if (offset >= total_sample_count)
            return  AudioBuffer{};

        return  AudioBuffer(
            // Source ptr
            static_cast<const sf::Int16*>(m_sound_buffer.getSamples() + offset),
            // Transformation function that simply normalizes signal
            std::function<double(sf::Int16)>([](sf::Int16 s) { return static_cast<double>(s) / std::numeric_limits<sf::Int16>::max(); }),
            // Size
            std::min(total_sample_count - offset,  AudioBuffer::s_size));
    }

} // namespace app::audio