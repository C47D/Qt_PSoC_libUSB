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

private:
    Ui::Widget *ui;

    int result;

};

#endif // WIDGET_H
