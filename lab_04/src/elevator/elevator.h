#pragma once

#include "controller.h"
#include "../defines.h"

#include <QObject>

class LiftSystem : public QObject
{
    Q_OBJECT

public:
    explicit LiftSystem(QObject *parent = nullptr);

signals:
    void floor_button_style_changed(int floor, direction_t direction, bool is_active);
    void cabin_button_style_changed(int floor, cabin_id_t cabin_id, bool is_active);
    void cabin_position_changed(cabin_id_t cabin_id, int floor);

    void floor_call_requested(int floor, direction_t direction);
    void cabin_call_requested(int floor, cabin_id_t cabin_id);

public slots:
    void request_floor_call(int floor, direction_t direction);
    void request_cabin_call(int floor, cabin_id_t cabin_id);

    void forward_floor_button_style(int floor, direction_t direction, bool is_active);
    void forward_cabin_button_style(int floor, cabin_id_t cabin_id, bool is_active);
    void forward_cabin_position(cabin_id_t cabin_id, int floor);

private:
    Controller _controller;
};
