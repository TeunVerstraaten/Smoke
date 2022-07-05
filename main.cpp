#include "app/disp/MainWindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("smoke");

    const QString audio_file = "minimal.wav";

    app::disp::MainWindow widget(audio_file);
    //        app::disp::MainWindow widget;
    widget.show();
    return app.exec();
}