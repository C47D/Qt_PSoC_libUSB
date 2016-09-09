#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#ifdef Q_OS_LINUX
#include "libusb-1.0/libusb.h"
#else // Q_OS_WINDOWS
#include "libusb.h"
#endif

/* Functions */
static void printSliderState();

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
    ui->density_Slider->setMaximum(100);
    ui->density_Slider->setTickPosition(QSlider::TicksBelow);
    ui->density_Slider->setTickInterval(5);


    /********** Connect signals and slots **********/

    // Sender : Slider
    // Signal : Value changed
    // Receiver : NA
    // Slot (simple function): printSliderState
    // New way to connect signals and slot, in this case
    // connecting to a simple function
    QObject::connect(ui->density_Slider,
                     &QSlider::valueChanged,
                     printSliderState);
}

Widget::~Widget()
{
    delete ui;
}

static void printSliderState()
{
    qDebug() << "El slider cambio de posicion";
}
