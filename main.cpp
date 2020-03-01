#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.loadImage("/home/disda/Desktop/深度截图_选择区域_20191108002117.png", true);
    return a.exec();
}
