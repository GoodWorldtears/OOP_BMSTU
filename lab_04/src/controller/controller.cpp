#include "controller.h"

#include <cmath>
#include <limits>
#include <vector>

namespace
{
constexpr int FLOOR_NOT_FOUND = -1;
}

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < CABINS_COUNT; ++i)
    {
        const auto cabin_id = static_cast<cabin_id_t>(i);

        _cabins[i] = std::make_unique<Cabin>(cabin_id, this);
        _cur_floor[i] = START_FLOOR - 1;
        _cur_directions[i] = DIR_STAND;
        _preferred_directions[i] = DIR_UP;

        QObject::connect(_cabins[i].get(), &Cabin::cabin_finish_boarding,
                         this, &Controller::handle_boarding_finished);

        QObject::connect(&_cabins[i]->move_timer, &QTimer::timeout, this, [this, cabin_id]()
        {
            handle_cabin_floor_passed(cabin_id);
        });
    }

    QObject::connect(this, &Controller::cabin_should_become_free, this, [this](cabin_id_t cabin_id)
    {
        _cabins[cabin_id]->cabin_free_slot();
    });

    QObject::connect(this, &Controller::cabin_should_move, this, [this](cabin_id_t cabin_id, int floor, direction_t direction)
    {
        _cabins[cabin_id]->cabin_moving_slot(floor, direction);
    });

    QObject::connect(this, &Controller::cabin_should_stop, this, [this](cabin_id_t cabin_id, int floor)
    {
        _cabins[cabin_id]->cabin_start_boarding_slot(floor);
    });

    QObject::connect(this, &Controller::cabin_should_continue, // проверка есть ли следующие задачи
                     this, &Controller::dispatch_cabin);

    QObject::connect(this, &Controller::controller_should_become_idle, // контроллер переводится в состояние покоя
                     this, &Controller::set_controller_idle);

    for (int floor_index = 0; floor_index < FLOOR_COUNT; ++floor_index)
    {
        const int floor = floor_index + 1;

        _floor_buttons[BDIR_UP][floor_index] = std::make_shared<FloorButton>(floor, DIR_UP);
        _floor_buttons[BDIR_DOWN][floor_index] = std::make_shared<FloorButton>(floor, DIR_DOWN);
        _lift_buttons[CID_FIRST][floor_index] = std::make_shared<LiftButton>(floor, CID_FIRST);
        _lift_buttons[CID_SECOND][floor_index] = std::make_shared<LiftButton>(floor, CID_SECOND);

        QObject::connect(_floor_buttons[BDIR_UP][floor_index].get(), &FloorButton::activated_signal, this, [this, floor_index]()
        {
            dispatch_cabin(assigned_cabin_for_floor_call(floor_index, DIR_UP));
        });

        QObject::connect(_floor_buttons[BDIR_DOWN][floor_index].get(), &FloorButton::activated_signal, this, [this, floor_index]()
        {
            dispatch_cabin(assigned_cabin_for_floor_call(floor_index, DIR_DOWN));
        });

        QObject::connect(_lift_buttons[CID_FIRST][floor_index].get(), &LiftButton::activated_signal, this, [this]()
        {
            dispatch_cabin(CID_FIRST);
        });

        QObject::connect(_lift_buttons[CID_SECOND][floor_index].get(), &LiftButton::activated_signal, this, [this]()
        {
            dispatch_cabin(CID_SECOND);
        });

        QObject::connect(_floor_buttons[BDIR_UP][floor_index].get(), &FloorButton::activated_signal, this, [this, floor]()
        {
            emit floor_button_style_changed(floor, DIR_UP, true);
        });

        QObject::connect(_floor_buttons[BDIR_DOWN][floor_index].get(), &FloorButton::activated_signal, this, [this, floor]()
        {
            emit floor_button_style_changed(floor, DIR_DOWN, true);
        });

        QObject::connect(_floor_buttons[BDIR_UP][floor_index].get(), &FloorButton::deactivated_signal, this, [this, floor]()
        {
            emit floor_button_style_changed(floor, DIR_UP, false);
        });

        QObject::connect(_floor_buttons[BDIR_DOWN][floor_index].get(), &FloorButton::deactivated_signal, this, [this, floor]()
        {
            emit floor_button_style_changed(floor, DIR_DOWN, false);
        });

        QObject::connect(_lift_buttons[CID_FIRST][floor_index].get(), &LiftButton::activated_signal, this, [this, floor]()
        {
            emit cabin_button_style_changed(floor, CID_FIRST, true);
        });

        QObject::connect(_lift_buttons[CID_SECOND][floor_index].get(), &LiftButton::activated_signal, this, [this, floor]()
        {
            emit cabin_button_style_changed(floor, CID_SECOND, true);
        });

        QObject::connect(_lift_buttons[CID_FIRST][floor_index].get(), &LiftButton::deactivated_signal, this, [this, floor]()
        {
            emit cabin_button_style_changed(floor, CID_FIRST, false);
        });

        QObject::connect(_lift_buttons[CID_SECOND][floor_index].get(), &LiftButton::deactivated_signal, this, [this, floor]()
        {
            emit cabin_button_style_changed(floor, CID_SECOND, false);
        });
    }

    for (int i = 0; i < CABINS_COUNT; ++i)
    {
        emit cabin_position_changed(static_cast<cabin_id_t>(i), START_FLOOR);
    }
}

Controller::~Controller() = default;

void Controller::handle_floor_call(int floor, direction_t direction)
{
    if (_state != CON_FREE && _state != CON_MANAGING_CABIN && _state != CON_MANAGING_MOVE)
        return;

    for (int id = 0; id < CABINS_COUNT; ++id)
    {
        const auto cabin_id = static_cast<cabin_id_t>(id);
        const bool already_requested =
            (direction == DIR_UP && _task_manager.has_floor_call_up(cabin_id, floor)) ||
            (direction == DIR_DOWN && _task_manager.has_floor_call_down(cabin_id, floor));

        if (already_requested)
            return;
    }

    for (int id = 0; id < CABINS_COUNT; ++id)
    {
        if (_cur_floor[id] == floor - 1 && _cur_directions[id] == DIR_STAND)
        {
            emit cabin_should_stop(static_cast<cabin_id_t>(id), _cur_floor[id]);
            return;
        }
    }

    _state = CON_REQUEST_FLOOR;

    cabin_id_t selected_cabin_id = CID_FIRST;
    double best_score = std::numeric_limits<double>::max();

    for (int i = 0; i < CABINS_COUNT; ++i)
    {
        const auto cabin_id = static_cast<cabin_id_t>(i);
        const double score = calculate_cabin_score(cabin_id, floor, direction);

        qInfo("Лифт %d: оценка = %.2f (этаж %d, направление %d)",
              i + 1, score, _cur_floor[i] + 1, _cur_directions[i]);

        if (score < best_score)
        {
            best_score = score;
            selected_cabin_id = cabin_id;
        }
    }

    qInfo("Выбран лифт %d для вызова на этаж %d (%s), оценка %.2f",
          selected_cabin_id + 1,
          floor,
          direction == DIR_UP ? "вверх" : "вниз",
          best_score);

    const Task task(floor, direction, selected_cabin_id, TASK_FLOOR_CALL);
    _task_manager.add_task(task);

    if (direction == DIR_UP)
        emit _floor_buttons[BDIR_UP][floor - 1]->activate_signal();
    else
        emit _floor_buttons[BDIR_DOWN][floor - 1]->activate_signal();
}

void Controller::handle_cabin_call(int floor, cabin_id_t cabin_id)
{
    if (_state != CON_FREE && _state != CON_MANAGING_CABIN && _state != CON_MANAGING_MOVE)
        return;

    if (_task_manager.has_cabin_call(cabin_id, floor))
        return;

    _state = CON_REQUEST_CABIN;

    const Task task(floor, DIR_STAND, cabin_id, TASK_CABIN_CALL);
    _task_manager.add_task(task);

    qInfo("Добавлена задача кабины: %s", task.to_string().c_str());

    emit _lift_buttons[cabin_id][floor - 1]->activate_signal();
}

void Controller::handle_cabin_floor_passed(cabin_id_t cabin_id)
{
    if (_state != CON_MANAGING_CABIN)
        return;

    _state = CON_MANAGING_MOVE;
    _cur_floor[cabin_id] += _cur_directions[cabin_id];

    emit cabin_position_changed(cabin_id, _cur_floor[cabin_id] + 1);
    dispatch_cabin(cabin_id);
}

void Controller::dispatch_cabin(cabin_id_t cabin_id)
{
    if (_state == CON_MANAGING_CABIN)
        return;

    _state = CON_MANAGING_CABIN;

    const int target_floor = choose_next_target_floor(cabin_id);

    if (target_floor == FLOOR_NOT_FOUND)
    {
        _cur_directions[cabin_id] = DIR_STAND;
        emit cabin_should_become_free(cabin_id);
    }
    else if (target_floor > _cur_floor[cabin_id])
    {
        _cur_directions[cabin_id] = DIR_UP;
        emit cabin_should_move(cabin_id, _cur_floor[cabin_id], DIR_UP);
    }
    else if (target_floor < _cur_floor[cabin_id])
    {
        _cur_directions[cabin_id] = DIR_DOWN;
        emit cabin_should_move(cabin_id, _cur_floor[cabin_id], DIR_DOWN);
    }
    else
    {
        _cur_directions[cabin_id] = choose_next_direction(cabin_id);
        emit cabin_should_stop(cabin_id, _cur_floor[cabin_id]);
    }

    if (has_no_pending_tasks())
        emit controller_should_become_idle();
}

void Controller::handle_boarding_finished(cabin_id_t cabin_id)
{
    if (_state != CON_MANAGING_CABIN)
        return;

    _state = CON_REACH_DST_FLOOR;

    const int current_floor = _cur_floor[cabin_id] + 1;
    qInfo("Обработка остановки лифта %d на этаже %d", cabin_id + 1, current_floor);

    if (_task_manager.has_cabin_call(cabin_id, current_floor))
    {
        const Task task(current_floor, DIR_STAND, cabin_id, TASK_CABIN_CALL);
        _task_manager.remove_task(task);
        emit _lift_buttons[cabin_id][_cur_floor[cabin_id]]->deactivate_signal();
    }

    if (_task_manager.has_floor_call_up(cabin_id, current_floor))
    {
        const Task task(current_floor, DIR_UP, cabin_id, TASK_FLOOR_CALL);
        if (_task_manager.remove_task(task))
            emit _floor_buttons[BDIR_UP][_cur_floor[cabin_id]]->deactivate_signal();
    }

    if (_task_manager.has_floor_call_down(cabin_id, current_floor))
    {
        const Task task(current_floor, DIR_DOWN, cabin_id, TASK_FLOOR_CALL);
        if (_task_manager.remove_task(task))
            emit _floor_buttons[BDIR_DOWN][_cur_floor[cabin_id]]->deactivate_signal();
    }

    _cur_directions[cabin_id] = DIR_STAND;
    emit cabin_should_continue(cabin_id);
}

void Controller::set_controller_idle()
{
    if (_state == CON_FREE)
        return;

    _state = CON_FREE;
    qInfo("[!] Контроллер находится в состоянии покоя.");
}

direction_t Controller::direction_from_delta(int difference) const
{
    if (difference == 0)
        return DIR_STAND;

    return difference > 0 ? DIR_UP : DIR_DOWN;
}

cabin_id_t Controller::assigned_cabin_for_floor_call(int floor_index, direction_t direction) const
{
    const int floor = floor_index + 1;

    for (int i = 0; i < CABINS_COUNT; ++i)
    {
        const auto cabin_id = static_cast<cabin_id_t>(i);
        const bool has_assigned_call =
            (direction == DIR_UP && _task_manager.has_floor_call_up(cabin_id, floor)) ||
            (direction == DIR_DOWN && _task_manager.has_floor_call_down(cabin_id, floor));

        if (has_assigned_call)
            return cabin_id;
    }

    return CID_FIRST;
}

int Controller::choose_next_target_floor(cabin_id_t cabin_id)
{
    const std::vector<Task> tasks = _task_manager.get_tasks_for_cabin(cabin_id);

    if (tasks.empty())
    {
        qInfo("Лифт %d: нет задач", cabin_id + 1);
        return FLOOR_NOT_FOUND;
    }

    const int current_floor = _cur_floor[cabin_id] + 1;

    for (const auto& task : tasks)
    {
        if (task.get_floor() == current_floor)
        {
            qInfo("Лифт %d: задача на текущем этаже %d", cabin_id + 1, current_floor);
            return _cur_floor[cabin_id];
        }
    }

    if (_cur_directions[cabin_id] == DIR_STAND)
    {
        bool has_tasks_in_preferred_direction = false;
        bool has_tasks_in_opposite_direction = false;

        for (const auto& task : tasks)
        {
            if (_preferred_directions[cabin_id] == DIR_UP && task.get_floor() > current_floor)
                has_tasks_in_preferred_direction = true;
            else if (_preferred_directions[cabin_id] == DIR_DOWN && task.get_floor() < current_floor)
                has_tasks_in_preferred_direction = true;
            else if (_preferred_directions[cabin_id] == DIR_UP && task.get_floor() < current_floor)
                has_tasks_in_opposite_direction = true;
            else if (_preferred_directions[cabin_id] == DIR_DOWN && task.get_floor() > current_floor)
                has_tasks_in_opposite_direction = true;
        }

        if (has_tasks_in_preferred_direction)
        {
            const int target_floor = find_target_in_direction(cabin_id, _preferred_directions[cabin_id], current_floor);
            if (target_floor != FLOOR_NOT_FOUND)
                return target_floor;
        }
        else if (has_tasks_in_opposite_direction)
        {
            _preferred_directions[cabin_id] = (_preferred_directions[cabin_id] == DIR_UP) ? DIR_DOWN : DIR_UP;
            qInfo("Лифт %d: разворот, новое направление %d", cabin_id + 1, _preferred_directions[cabin_id]);

            const int target_floor = find_target_in_direction(cabin_id, _preferred_directions[cabin_id], current_floor);
            if (target_floor != FLOOR_NOT_FOUND)
                return target_floor;
        }

        return FLOOR_NOT_FOUND;
    }

    return find_target_in_direction(cabin_id, _cur_directions[cabin_id], current_floor);
}

direction_t Controller::choose_next_direction(cabin_id_t cabin_id)
{
    const std::vector<Task> tasks = _task_manager.get_tasks_for_cabin(cabin_id);

    if (tasks.empty())
        return DIR_STAND;

    if (_cur_directions[cabin_id] == DIR_STAND)
    {
        int nearest_floor = FLOOR_NOT_FOUND;
        int nearest_distance = FLOOR_COUNT + 1;
        const int current_floor = _cur_floor[cabin_id] + 1;

        for (const auto& task : tasks)
        {
            const int distance = std::abs(current_floor - task.get_floor());
            if (distance > 0 && distance < nearest_distance)
            {
                nearest_distance = distance;
                nearest_floor = task.get_floor();
            }
        }

        if (nearest_floor == FLOOR_NOT_FOUND)
            return DIR_STAND;

        return nearest_floor > current_floor ? DIR_UP : DIR_DOWN;
    }

    const int target_floor_index = choose_next_target_floor(cabin_id);
    if (target_floor_index == FLOOR_NOT_FOUND)
        return DIR_STAND;

    return direction_from_delta((target_floor_index + 1) - (_cur_floor[cabin_id] + 1));
}

bool Controller::has_no_pending_tasks() const
{
    return !_task_manager.has_any_tasks();
}

double Controller::calculate_cabin_score(cabin_id_t cabin_id, int target_floor, direction_t direction) const
{
    double score = 0.0;

    const int current_floor = _cur_floor[cabin_id] + 1;
    const int distance = std::abs(target_floor - current_floor);
    score += distance * 10.0;

    const int task_count = _task_manager.get_task_count_for_cabin(cabin_id);
    score += task_count * 20.0;

    if (_cur_directions[cabin_id] == DIR_STAND)
    {
        score -= 15.0;
    }
    else
    {
        const direction_t direction_to_call = direction_from_delta(target_floor - current_floor);

        if (_cur_directions[cabin_id] == direction_to_call && _cur_directions[cabin_id] == direction)
            score -= 25.0;
        else if (_cur_directions[cabin_id] != direction_to_call)
            score += 30.0;

        if (_cur_directions[cabin_id] != direction_to_call && direction_to_call != DIR_STAND)
            score += 15.0;
    }

    return score;
}

int Controller::find_target_in_direction(cabin_id_t cabin_id, direction_t direction, int current_floor) const
{
    if (direction == DIR_UP)
    {
        int upper_turning_floor = FLOOR_NOT_FOUND;
        for (int floor = FLOOR_COUNT; floor >= current_floor + 1; --floor)
        {
            if (_task_manager.has_floor_call_down(cabin_id, floor))
                upper_turning_floor = floor;
        }

        for (int floor = current_floor + 1; floor <= FLOOR_COUNT; ++floor)
        {
            const bool has_task_on_the_way =
                _task_manager.has_cabin_call(cabin_id, floor) ||
                _task_manager.has_floor_call_up(cabin_id, floor);

            if (!has_task_on_the_way)
                continue;

            if (upper_turning_floor == FLOOR_NOT_FOUND || floor < upper_turning_floor)
                return floor - 1;
        }

        if (upper_turning_floor != FLOOR_NOT_FOUND)
            return upper_turning_floor - 1;
    }
    else if (direction == DIR_DOWN)
    {
        int lower_turning_floor = FLOOR_NOT_FOUND;
        for (int floor = 1; floor <= current_floor - 1; ++floor)
        {
            if (_task_manager.has_floor_call_up(cabin_id, floor))
            {
                lower_turning_floor = floor;
                break;
            }
        }

        for (int floor = current_floor - 1; floor >= 1; --floor)
        {
            const bool has_task_on_the_way =
                _task_manager.has_cabin_call(cabin_id, floor) ||
                _task_manager.has_floor_call_down(cabin_id, floor);

            if (!has_task_on_the_way)
                continue;

            if (lower_turning_floor == FLOOR_NOT_FOUND || floor > lower_turning_floor)
                return floor - 1;
        }

        if (lower_turning_floor != FLOOR_NOT_FOUND)
            return lower_turning_floor - 1;
    }

    return FLOOR_NOT_FOUND;
}
