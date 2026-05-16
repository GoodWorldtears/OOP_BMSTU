#pragma once

#include <QPushButton>

enum button_state_t
{
    BUTTON_ACTIVE,
    BUTTON_INACTIVE,
};

class BaseButton : public QObject

{
    Q_OBJECT
public:
    explicit BaseButton(QWidget *parent = nullptr);
    ~BaseButton() override = default;

protected:
    button_state_t _state;
}; 