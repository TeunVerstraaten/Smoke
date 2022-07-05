//
// Created by pc on 20-6-22.
//

#include "BeatHandler.h"

namespace app::audio {

    void BeatHandler::set_beat_score(double beat_score) {
        if (m_was_just_blocked)
            m_was_just_blocked = false;
        if (not(m_is_blocked)) {
            if (m_beat_is_coming)
                handle_coming_beat(beat_score);
            else
                check_for_new_beat(beat_score);
        }
    }

    void BeatHandler::update(double elapsed_seconds) {
        if (m_is_blocked) {
            m_block_seconds_remaining -= elapsed_seconds;
            if (m_block_seconds_remaining <= 0)
                m_is_blocked = false;
        }
    }

    double BeatHandler::intensity() const {
        return m_intensity;
    }

    bool BeatHandler::was_just_blocked() const {
        return m_was_just_blocked;
    }

    double BeatHandler::current_beat_impulse() const {
        return was_just_blocked() ? intensity() : 0.0f;
    }

    void BeatHandler::handle_coming_beat(double beat_score) {
        m_running_average = 0.5 * m_running_average + 0.5 * beat_score;
        if ((3 * m_running_average < m_intensity) || (m_wait_until_force == 0)) {
            m_is_blocked              = true;
            m_was_just_blocked        = true;
            m_beat_is_coming          = false;
            m_block_seconds_remaining = 0.35;
        }
        --m_wait_until_force;
    }

    void BeatHandler::check_for_new_beat(double beat_score) {
        if (beat_score > m_beat_cut_off) {
            m_intensity        = beat_score;
            m_beat_is_coming   = true;
            m_running_average  = 0.0f;
            m_wait_until_force = 10;
        }
    }

} // namespace app::audio