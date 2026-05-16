#include "cabin.h"
#include "../defines.h"

#include <QString>

#include <QDebug>

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _state(CAB_FREE), _doors(id)
{
    move_timer.setSingleShot(true);
    QObject::connect(this, &Cabin::open_doors, &_doors, &Doors::start_opening_slot);
    QObject::connect(&_doors, &Doors::door_is_closed, this, &Cabin::cabin_stop_boarding_slot);
}

void Cabin::cabin_free_slot()
{
    if (_state != CAB_BOARDING_FINISHED)
        return;

    _state = CAB_FREE;
}

void Cabin::cabin_moving_slot(int floor, direction_t direction)
{
    if (_state == CAB_BOARDING_STARTED)
        return;

    floor++;
    _state = CAB_MOVE;

    if (direction == DIR_UP)
    {
        qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, floor, floor + 1);
        move_timer.start(MOVE_TIME);
    }
    else if (direction == DIR_DOWN)
    {
        qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, floor, floor - 1);
        move_timer.start(MOVE_TIME);
    }
}

void Cabin::cabin_start_boarding_slot(int floor)
{
    if (_state == CAB_BOARDING_STARTED || _state == CAB_BOARDING_FINISHED)
        return;

    _state = CAB_BOARDING_STARTED;
    qInfo("Лифт №%d остановился на этаже №%d.", _id + 1, floor + 1);
    emit open_doors();
}

void Cabin::cabin_stop_boarding_slot()
{
    if (_state == CAB_BOARDING_FINISHED)
        return;

    _state = CAB_BOARDING_FINISHED;
    qInfo("Посадка/высадка пассажиров в лифте №%d завершена.", _id + 1);
    emit cabin_finish_boarding(_id);
}
