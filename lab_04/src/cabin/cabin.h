#pragma once

#include "../defines.h"
#include "../doors/doors.h"

#include <QObject>
#include <QTimer>

class Cabin : public QObject
{
    Q_OBJECT

public:
    Cabin(cabin_id_t id, QObject *parent = nullptr);
    ~Cabin() = default;

    QTimer move_timer;

signals:
    void cabin_finish_boarding(cabin_id_t id);

    void cabin_stop();
    void passing_floor();
    void open_doors();

public slots:
    void cabin_free_slot();
    void cabin_moving_slot(int floor, direction_t direction);
    void cabin_stop_boarding_slot();
    void cabin_start_boarding_slot(int floor);

private:
    cabin_id_t _id;

    enum cabin_state_t
    {
        CAB_FREE,
        CAB_MOVE,
        CAB_BOARDING_STARTED,
        CAB_BOARDING_FINISHED,
    };

    cabin_state_t _state;
    Doors _doors;
}; 
