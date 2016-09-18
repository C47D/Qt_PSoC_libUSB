#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QTimer>

#ifdef Q_OS_LINUX
#include "libusb-1.0/libusb.h"
#else // Q_OS_WINDOWS
#include "libusb.h"
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /********** Setup GUI visual contents **********/

    /*
     * buttonState Check Button:
     * this check button let us know the state
     * of the onboard switch button of the
     * development kit.
    */
    ui->buttonState_cB->setText("Push button state");

    /*
     * scrollBar Label
     * This is just a label to
     * display a text, nothing fancy here
    */
    ui->scrollBar_lbl->setText("PrISM Density Value");

    /*
     * connect Push Button
     * This button will allow us to
     * connect and disconnect the USB device to
     * the application.
     * Acquire and release in libUSB terms, it will
     * also display a text, which will be the state
     * of the device (connected or disconnected) being
     * the last state the default state
    */
    ui->connect_pB->setText("Connect");
    ui->connect_pB->setStyleSheet("QPushButton {font-weight: bold; color : green}");

    /*
     *
     *
    */
    ui->state_lbl->setText("PSoC Disconnected");
    ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");

    /*
     * density Slider
     * this slider will let us control the
     * brightness of the onboard LED of the kit.
    */
    ui->density_Slider->setMinimum(0);
    ui->density_Slider->setMaximum(255);
    ui->density_Slider->setTickPosition(QSlider::TicksBelow);
    ui->density_Slider->setTickInterval(5);
    ui->density_Slider->setEnabled(false);

    /********** Connect signals and slots **********/

    connect(ui->connect_pB,
            &QPushButton::clicked,
            this,
            &Widget::connect2USB);

    connect(ui->density_Slider,
            &QSlider::valueChanged,
            this,
            &Widget::sendSliderValue);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::connect2USB()
{
    result = libusb_init(NULL);

    if(0 != result){
        ui->state_lbl->setText("Unable to init libUSB");
        ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");
    }

    ui->density_Slider->setEnabled(true);
    ui->state_lbl->setText("Connected");
    ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: green}");

}

void Widget::sendSliderValue()
{
    qDebug() << "Slot del cambio de valor del slider" ;
}

bool Widget::getPushButtonValue()
{
    return true;
}
