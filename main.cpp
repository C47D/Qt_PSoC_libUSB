#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Widget w;
    w.setWindowTitle("PSoC 5LP USB (VID = 0x4B4, PID = 0xE177)");
    w.show();
    return a.exec();
}
