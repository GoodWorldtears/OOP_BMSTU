#include "elevator.h"

LiftSystem::LiftSystem(QObject *parent)
    : QObject(parent)
{
    QObject::connect(this, &LiftSystem::floor_call_requested,
                     &_controller, &Controller::handle_floor_call);
    QObject::connect(this, &LiftSystem::cabin_call_requested,
                     &_controller, &Controller::handle_cabin_call);

    QObject::connect(&_controller, &Controller::floor_button_style_changed,
                     this, &LiftSystem::forward_floor_button_style);
    QObject::connect(&_controller, &Controller::cabin_button_style_changed,
                     this, &LiftSystem::forward_cabin_button_style);
    QObject::connect(&_controller, &Controller::cabin_position_changed,
                     this, &LiftSystem::forward_cabin_position);
}

void LiftSystem::request_floor_call(int floor, direction_t direction)
{
    emit floor_call_requested(floor, direction);
}

void LiftSystem::request_cabin_call(int floor, cabin_id_t cabin_id)
{
    emit cabin_call_requested(floor, cabin_id);
}

void LiftSystem::forward_floor_button_style(int floor, direction_t direction, bool is_active)
{
    emit floor_button_style_changed(floor, direction, is_active);
}

void LiftSystem::forward_cabin_button_style(int floor, cabin_id_t cabin_id, bool is_active)
{
    emit cabin_button_style_changed(floor, cabin_id, is_active);
}

void LiftSystem::forward_cabin_position(cabin_id_t cabin_id, int floor)
{
    emit cabin_position_changed(cabin_id, floor);
}
