//
// Created by pc on 23-6-22.
//

#include "RenderToFile.h"

#include "audio/AudioPlayer.h"
#include "audio/SoundWindow.h"
#include "disp/SmokeWidget.h"

#include <iostream>

namespace app {

    void render_to_file(const std::string& audio_file) {
        audio::AudioPlayer player;
        if (not player.init("../songs/" + audio_file))
            return;

        disp::SmokeWidget smoke_widget(nullptr);
        smoke_widget.resize(1000, 1000);
        audio::SoundWindow sound_window(&player);

        system(("mkdir " + audio_file).c_str());
        system(("cp ../songs/" + audio_file + " " + audio_file + "/song.wav").c_str());

        size_t       elapsed_in_msec  = 0;
        size_t       duration_in_msec = 1000 * player.duration();
        const size_t msec_per_frame   = 16;
        size_t       i                = 0;
        for (; elapsed_in_msec < duration_in_msec; elapsed_in_msec += msec_per_frame) {
            smoke_widget.handle_beat(sound_window.current_beat_intensity());
            smoke_widget.step(static_cast<double>(msec_per_frame) / 1000.0);
            sound_window.update_by_time_point(static_cast<double>(elapsed_in_msec) / 1000.0, msec_per_frame / 1000.0);

            QPixmap pixmap = smoke_widget.grab();
            pixmap.save(QString::fromStdString(audio_file + "/fr" + std::to_string(i) + ".png"));
            ++i;

            std::cout << "%=" << elapsed_in_msec / static_cast<double>(duration_in_msec) << "\n";
        }
        system(("ffmpeg -y -framerate 60 -i \"" + audio_file + "/fr%d.png\" " + audio_file + "/output.mp4 -c:v libx264 -crf 18 -preset veryslow").c_str());
        system(("ffmpeg -y -i " + audio_file + "/output.mp4 -i " + audio_file + "/song.wav -c:v copy -c:a aac -c:v libx264 -crf 18 -preset veryslow " + audio_file + "/res.mp4")
                   .c_str());
        system(("rm " + audio_file + "/*.png").c_str());
    }
} // namespace app
