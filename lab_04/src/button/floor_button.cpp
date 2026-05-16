#include "floor_button.h"
#include "../defines.h"
#include <QDebug>

FloorButton::FloorButton(int floor, direction_t direction, QWidget *parent)
    : BaseButton(parent), _floor(floor), _direction(direction)
{
    QObject::connect(this, &FloorButton::activate_signal, this, &FloorButton::activate_slot);
    QObject::connect(this, &FloorButton::deactivate_signal, this, &FloorButton::deactivate_slot);
}

void FloorButton::activate_slot()
{
    if (this->_state == BUTTON_ACTIVE)
        return;

    this->_state = BUTTON_ACTIVE;
    if (_direction == DIR_UP)
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d была нажата кнопка вызова НАВЕРХ" TEXT_DEFAULT, _floor);
    }
    else
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d была нажата кнопка вызова ВНИЗ" TEXT_DEFAULT, _floor);
    }

    emit activated_signal();
}

void FloorButton::deactivate_slot()
{
    if (this->_state == BUTTON_INACTIVE)
        return;

    this->_state = BUTTON_INACTIVE;
    if (_direction == DIR_UP)
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d кнопка НАВЕРХ была деактивирована" TEXT_DEFAULT, _floor);
    }
    else
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d кнопка ВНИЗ была декактивирована" TEXT_DEFAULT, _floor);
    }

    emit deactivated_signal();
} 