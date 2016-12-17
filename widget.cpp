#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /***** QTimer Setup *****/
    timer = new QTimer(this);

    /********** Setup GUI visual contents **********/

    // buttonState Check Button:
    // this check button let us know the state
    // of the onboard switch button of the
    // development kit.
    ui->buttonState_cB->setCheckable(false);
    ui->buttonState_cB->setText("Push button state");

    // scrollBar Label
    // This is just a label to
    // display a text, nothing fancy here
    ui->scrollBar_lbl->setText("PrISM Density Value");

    // connect Push Button
    // This button will allow us to
    // connect and disconnect the USB device to
    // the application.
    // Acquire and release in libUSB terms, it will
    // also display a text, which will be the state
    // of the device (connected or disconnected) being
    // the last state the default state
    ui->connect_pB->setText("Connect");
    ui->connect_pB->setStyleSheet("QPushButton {font-weight: bold; color : green}");

    ui->state_lbl->setText("PSoC Disconnected");
    ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");

    // density Slider
    // this slider will let us control the
    // brightness of the onboard LED of the kit.
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

    connect(timer,
            &QTimer::timeout,
            this,
            &Widget::getPushButtonValue);

}

Widget::~Widget()
{
    delete ui;
    // Nos debemos asegurar de desconectar de libusb
    closeUSB();
}

void Widget::error(QString s, int err)
{
    qDebug() << s << " Error: " << libusb_error_name(err);
    //exit(err);
}

void Widget::connect2USB()
{    
    if (this->isConnected == true) {
        // Si ya estabamos conectados entonces el clic
        // es para desconectarnos
        ui->density_Slider->setEnabled(false);
        ui->state_lbl->setText("Disconnected");
        ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");
        ui->connect_pB->setText("Connect");
        ui->connect_pB->setStyleSheet("QPushButton {font-weight: bold; color : green}");
        timer->stop();
        qDebug() << "Timer Detenido";
        this->isConnected = false;
        closeUSB();
    } else {
        libusb_init(NULL);
        if (0 > result) {
            ui->state_lbl->setText("Unable to init libUSB");
            ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");
            error("Cannot init libUSB!", err);
        }

        usb_handle = libusb_open_device_with_vid_pid(NULL, usbVID, usbPID);
        if (NULL == usb_handle) {
            ui->state_lbl->setText("Unable to init libUSB");
            ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: red}");
            error("Cannot open the device!", err);
        }

        err = libusb_claim_interface(usb_handle, 0);
        if (err) {
            error("Cannot claim interface", err);
        }

        err = libusb_set_interface_alt_setting(usb_handle, 0, 0);
        if (err) {
            error("Cannot set alt setting!", err);
        }

        ui->density_Slider->setEnabled(true);
        ui->state_lbl->setText("Connected");
        ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color: green}");
        ui->connect_pB->setText("Disconnect");
        ui->connect_pB->setStyleSheet("QPushButton {font-weight: bold; color : red}");

        //timer->start(100); // 100 ms timer

        this->isConnected = true;
    }
}

void Widget::closeUSB()
{
    libusb_release_interface(usb_handle, 0);
    libusb_close(usb_handle);
    libusb_exit(NULL);
}

void Widget::sendSliderValue()
{
    //timer->stop();
    /* send the slider value to control the onboard LED */
    sliderPosition[0] = ui->density_Slider->value();

    err = libusb_interrupt_transfer(usb_handle,
                                    LIBUSB_ENDPOINT_OUT | OUT_ENDPOINT,
                                    &sliderPosition[0],
                                    sizeof(sliderPosition),
                                    &transfer_size,
                                    250);

    qDebug() << "Bytes transferidos: " << transfer_size;

    if (err) {
        error("OUT Interrupt transfer failed!", err);
    }
    //timer->start();
}

void Widget::getPushButtonValue()
{
    //timer->stop();
    /* Request the state of the onboard push button */
    err = libusb_interrupt_transfer(usb_handle,
                                    LIBUSB_ENDPOINT_IN | IN_ENDPOINT,
                                    &buttonState[0],
                                    2,
                                    &transfer_size,
                                    2500);

    qDebug() << "Bytes recibidos: " << transfer_size;
    ui->buttonState_cB->setCheckState(( buttonState[0] != 0 ? Qt::Checked : Qt::Unchecked ));

    if (err) {
        error("IN Interrupt transfer failed!", err);
    }
    //timer->start();
}
