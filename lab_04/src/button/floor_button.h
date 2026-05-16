#pragma once

#include "base_button.h"
#include "../defines.h"

class FloorButton : public BaseButton
{
    Q_OBJECT
public:
    FloorButton(int floor, direction_t direction, QWidget *parent = nullptr);
    ~FloorButton() override = default;

signals:
    void activate_signal();
    void deactivate_signal();

    void activated_signal();
    void deactivated_signal();

public slots:
    void activate_slot();
    void deactivate_slot();

private:
    int _floor;
    direction_t _direction;
}; 