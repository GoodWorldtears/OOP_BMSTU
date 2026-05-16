#include "base_button.h"

BaseButton::BaseButton(QWidget *parent)
    : QObject(parent)
{
    _state = BUTTON_INACTIVE;
}
