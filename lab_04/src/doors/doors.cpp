#include "doors.h"
#include "../defines.h"
#include <QDebug>

Doors::Doors(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _state(DOOR_CLOSED)
{
    open_door_timer.setSingleShot(true);
    open_state_door_timer.setSingleShot(true);
    close_door_timer.setSingleShot(true);

    QObject::connect(&open_door_timer, &QTimer::timeout, this, &Doors::open_slot);
    QObject::connect(&open_state_door_timer, &QTimer::timeout, this, &Doors::start_closing_slot);
    QObject::connect(&close_door_timer, &QTimer::timeout, this, &Doors::close_slot);
}

void Doors::start_opening_slot()
{
    if (_state != DOOR_CLOSED && _state != DOOR_CLOSING)
        return;

    if (_state == DOOR_CLOSED)
    {
        _state = DOOR_OPENING;
        qInfo(TEXT_GREEN "[*] Двери лифта №%d открываются..." TEXT_DEFAULT, _id + 1);
        open_door_timer.start(WAIT_TIME);
    }
    else if (_state == DOOR_CLOSING)
    {
        int remaining_time = close_door_timer.remainingTime();
        int opening_time = (remaining_time > 0) ? (WAIT_TIME * remaining_time / WAIT_TIME) : WAIT_TIME;

        close_door_timer.stop();
        _state = DOOR_OPENING;
        qInfo(TEXT_GREEN "[*] Двери лифта №%d открываются..." TEXT_DEFAULT, _id + 1);
        open_door_timer.start(opening_time);
    }
}

void Doors::start_closing_slot()
{
    if (_state != DOOR_OPENED)
        return;

    _state = DOOR_CLOSING;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d закрываются..." TEXT_DEFAULT, _id + 1);
    close_door_timer.start(WAIT_TIME);
}

void Doors::open_slot()
{
    if (_state != DOOR_OPENING)
        return;

    _state = DOOR_OPENED;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d открылись." TEXT_DEFAULT, _id + 1);
    open_state_door_timer.start(WAIT_TIME);
}

void Doors::close_slot()
{
    if (_state != DOOR_CLOSING)
        return;

    _state = DOOR_CLOSED;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d закрылись." TEXT_DEFAULT, _id + 1);
    emit door_is_closed();
}
