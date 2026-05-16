#pragma once

#include "../defines.h"

#include <QObject>
#include <QTimer>

class Doors : public QObject
{
    Q_OBJECT

public:
    explicit Doors(cabin_id_t id, QObject *parent = nullptr);

signals:
    void door_is_closed();

public slots:
    void start_opening_slot();
    void start_closing_slot();

private slots:
    void open_slot();
    void close_slot();

private:
    cabin_id_t _id;

    enum door_state_t
    {
        DOOR_OPENED,
        DOOR_OPENING,
        DOOR_CLOSED,
        DOOR_CLOSING,
    };

    door_state_t _state;

    QTimer open_door_timer;
    QTimer close_door_timer;
    QTimer open_state_door_timer;
}; 
