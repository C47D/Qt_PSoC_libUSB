#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->buttonState_cB->setText("Push button state");
    ui->scrollBar_lbl->setText("PrISM Density Value");
    ui->state_lbl->setText("Disconnected");
    ui->state_lbl->setStyleSheet("QLabel {font-weight: bold; color : red}");
    ui->density_Slider->setMinimum(0);
    ui->density_Slider->setMaximum(100);
    ui->density_Slider->setTickPosition(QSlider::TicksBelow);
    ui->density_Slider->setTickInterval(5);
}

Widget::~Widget()
{
    delete ui;
}
