#pragma once

#include "base_button.h"
#include "../defines.h"

class LiftButton : public BaseButton
{
    Q_OBJECT
public:
    LiftButton(int floor, cabin_id_t id, QWidget *parent = nullptr);
    ~LiftButton() override = default;

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
    cabin_id_t _id;
}; 