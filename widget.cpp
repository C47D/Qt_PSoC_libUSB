#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#if defined Q_OS_LINUX
#include "libusb-1.0/libusb.h"
#elif Q_OS_WINDOWS
#include "libusb.h"
#endif

/* Functions */
static void printSliderState();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /* Setup the contents of the GUI */
    ui->buttonState_cB->setText("Push button state");
    ui->scrollBar_lbl->setText("PrISM Density Value");
    ui->state_lbl->setText("Disconnected");
    ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color : red}");
    ui->density_Slider->setMinimum(0);
    ui->density_Slider->setMaximum(100);
    ui->density_Slider->setTickPosition(QSlider::TicksBelow);
    ui->density_Slider->setTickInterval(5);

    /* Connect signals and slots */

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
