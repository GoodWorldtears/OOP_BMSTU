#pragma once

#include "../cabin/cabin.h"
#include "../defines.h"
#include "../button/floor_button.h"
#include "../button/lift_button.h"
#include "../task/task_manager.h"

#include <QObject>
#include <memory>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

signals:
    void floor_button_style_changed(int floor, direction_t direction, bool is_active);
    void cabin_button_style_changed(int floor, cabin_id_t cabin_id, bool is_active);
    void cabin_position_changed(cabin_id_t cabin_id, int floor);

    void cabin_should_continue(cabin_id_t cabin_id);
    void cabin_should_become_free(cabin_id_t cabin_id);
    void cabin_should_move(cabin_id_t cabin_id, int current_floor, direction_t direction);
    void cabin_should_stop(cabin_id_t cabin_id, int current_floor);
    void controller_should_become_idle();

public slots:
    void handle_floor_call(int floor, direction_t direction);
    void handle_cabin_call(int floor, cabin_id_t cabin_id);

    void handle_cabin_floor_passed(cabin_id_t cabin_id);
    void dispatch_cabin(cabin_id_t cabin_id);
    void handle_boarding_finished(cabin_id_t cabin_id);
    void set_controller_idle();

private:
    direction_t direction_from_delta(int difference) const;
    direction_t choose_next_direction(cabin_id_t cabin_id);
    cabin_id_t assigned_cabin_for_floor_call(int floor_index, direction_t direction) const;

    double calculate_cabin_score(cabin_id_t cabin_id, int target_floor, direction_t direction) const;

    int choose_next_target_floor(cabin_id_t cabin_id);
    int find_target_in_direction(cabin_id_t cabin_id, direction_t direction, int current_floor) const;
    bool has_no_pending_tasks() const;

    enum controller_state_t
    {
        CON_FREE, // контроллер свободен и может принимать новые вызовы
        CON_REQUEST_CABIN, // обрабатывается запрос из кабины
        CON_REQUEST_FLOOR, // обрабатывается вызов с этажа
        CON_MANAGING_CABIN, // контроллер управляет кабиной: выбирает цель, запускает движение или остановку
        CON_MANAGING_MOVE, // контроллер обрабатывает факт движения: кабина проехала этаж
        CON_REACH_DST_FLOOR, // кабина достигла нужного этажа, контроллер обрабатывает остановку
    };

    controller_state_t _state = CON_FREE;

    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] = {};
    int _cur_floor[CABINS_COUNT] = {};
    direction_t _cur_directions[CABINS_COUNT] = {};
    direction_t _preferred_directions[CABINS_COUNT] = {};

    std::shared_ptr<FloorButton> _floor_buttons[DIRECTIONS_COUNT][FLOOR_COUNT];
    std::shared_ptr<LiftButton> _lift_buttons[CABINS_COUNT][FLOOR_COUNT];

    TaskManager _task_manager;
};
