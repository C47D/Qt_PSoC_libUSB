#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    /* Slots */
    void connect2USB();
    void sendSliderValue();
    void getPushButtonValue();

private:
    Ui::Widget *ui;
    QTimer *timer;
    int result;
    bool isConnected;
};

#endif // WIDGET_H
