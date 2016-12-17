#ifndef WIDGET_H
#define WIDGET_H

#ifdef Q_OS_LINUX
#include "libusb-1.0/libusb.h"
#else // Q_OS_WINDOWS
#include "libusb.h"
#endif

#include <QString>
#include <QTimer>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    Ui::Widget *ui;
    QTimer *timer;
    int result;
    bool isConnected = false;
    bool success = false;

    const uint16_t usbVID = 0x04B4; // PSoC VID
    const uint16_t usbPID = 0XE177; // PSoC PID
    const int IN_ENDPOINT = 0x01;
    const int OUT_ENDPOINT = 0x02;

    uint8_t sliderPosition[2];
    uint8_t buttonState[2];
    int err;
    int transfer_size;

    /* libUSB devices and handles */
    libusb_context* ctx = nullptr;
    libusb_device_handle* usb_handle = nullptr;
    libusb_device** devs;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void error(QString s, int err);
    void connect2USB();
    void closeUSB();
    void sendSliderValue();
    void getPushButtonValue();

};

#endif // WIDGET_H
