#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QPushButton>
#include "../defines.h"

class Button : public QPushButton
{
    Q_OBJECT

public:
    enum ButtonState 
    {
        CLICKED,
        NOTCLICKED
    };

    enum ButtonType
    {
        FLOOR_BUTTON,
        CABIN_BUTTON
    };

    Button(QWidget *parent = nullptr);

    void setFloor(int floor);
    void setButtonType(ButtonType type);

signals:
    void pressSignal(int);
    void unpressSignal();

public slots:
    void pressSlot();
    void unpressSlot();

private:
    ButtonState _state;
    ButtonType _type;
    int _currentButtonFloor;
};

#endif
