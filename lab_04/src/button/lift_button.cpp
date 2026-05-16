#include "lift_button.h"
#include "../defines.h"

#include <QDebug>

LiftButton::LiftButton(int floor, cabin_id_t id, QWidget *parent) : BaseButton(parent), _floor(floor), _id(id)
{
    QObject::connect(this, &LiftButton::activate_signal, this, &LiftButton::activate_slot);
    QObject::connect(this, &LiftButton::deactivate_signal, this, &LiftButton::deactivate_slot);
}

void LiftButton::activate_slot()
{
    if (this->_state == BUTTON_ACTIVE)
        return;

    this->_state = BUTTON_ACTIVE;

    qInfo(TEXT_CYAN "[!] В кабине лифта №%d была нажата кнопка этажа №%d" TEXT_DEFAULT, _id + 1, _floor);
    emit activated_signal();
}

void LiftButton::deactivate_slot()
{
    if (this->_state == BUTTON_INACTIVE)
        return;

    this->_state = BUTTON_INACTIVE;
    qInfo(TEXT_CYAN "[!] В кабине лифта №%d кнопка этажа №%d деактивирована" TEXT_DEFAULT, _id + 1, _floor);
    emit deactivated_signal();
} 