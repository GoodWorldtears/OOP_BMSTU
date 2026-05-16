#include "button.h"
#include <QDebug>

Button::Button(QWidget *parent) : QPushButton(parent)
{
    _state = NOTCLICKED;
    _type = FLOOR_BUTTON;
    _currentButtonFloor = 1;

    connect(this, &Button::clicked, this, &Button::pressSlot);
    connect(this, &Button::unpressSignal, this, &Button::unpressSlot);
}

void Button::setFloor(int floor)
{
    _currentButtonFloor = floor;
}

void Button::setButtonType(ButtonType type)
{
    _type = type;
}

void Button::pressSlot()
{
    if (_state == CLICKED) 
    {
        return;
    }

    setStyleSheet(QString(STYLE_PRESS));
    update();

    if (_type == FLOOR_BUTTON)
    {
        qDebug() << "[ЭТАЖ] Вызов на" << _currentButtonFloor << "этаж";
    }
    else
    {
        qDebug() << "[КАБИНА] Вызов на" << _currentButtonFloor << "этаж";
    }

    _state = CLICKED;
    setDisabled(true);

    emit pressSignal(_currentButtonFloor);
}

void Button::unpressSlot()
{
    if (_state == NOTCLICKED)
    {
        return;
    }

    setStyleSheet(QString(STYLE));
    update();
    _state = NOTCLICKED;
    setDisabled(false);
}
