#include "task_manager.h"
#include <algorithm>
#include <iostream>
#include <QDebug>

TaskManager::TaskManager()
{
}

void TaskManager::add_task(const Task& task)
{
    auto it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it == _tasks.end())
    {
        _tasks.push_back(task);
    }
}

bool TaskManager::remove_task(const Task& task)
{
    auto it = std::find(_tasks.begin(), _tasks.end(), task);
    if (it != _tasks.end())
    {
        _tasks.erase(it);
        return true;
    }
    return false;
}

void TaskManager::clear_all_tasks()
{
    _tasks.clear();
}

void TaskManager::clear_tasks_for_cabin(cabin_id_t cabin_id)
{
    _tasks.erase(
        std::remove_if(_tasks.begin(), _tasks.end(),
            [cabin_id](const Task& task) { return task.get_cabin_id() == cabin_id; }),
        _tasks.end()
    );
}

std::vector<Task> TaskManager::get_tasks_for_cabin(cabin_id_t cabin_id) const
{
    return filter_tasks([cabin_id](const Task& task) {
        return task.get_cabin_id() == cabin_id;
    });
}

std::vector<Task> TaskManager::get_tasks_for_floor(int floor) const
{
    return filter_tasks([floor](const Task& task) {
        return task.get_floor() == floor;
    });
}

std::vector<Task> TaskManager::get_tasks_for_cabin_and_floor(cabin_id_t cabin_id, int floor) const
{
    return filter_tasks([cabin_id, floor](const Task& task) {
        return task.get_cabin_id() == cabin_id && task.get_floor() == floor;
    });
}

std::vector<Task> TaskManager::get_tasks_by_direction(cabin_id_t cabin_id, direction_t direction) const
{
    return filter_tasks([cabin_id, direction](const Task& task) {
        return task.get_cabin_id() == cabin_id && task.get_direction() == direction;
    });
}

std::vector<Task> TaskManager::get_tasks_by_type(cabin_id_t cabin_id, task_type_t type) const
{
    return filter_tasks([cabin_id, type](const Task& task) {
        return task.get_cabin_id() == cabin_id && task.get_type() == type;
    });
}

bool TaskManager::has_task_for_cabin_and_floor(cabin_id_t cabin_id, int floor) const
{
    return !get_tasks_for_cabin_and_floor(cabin_id, floor).empty();
}

bool TaskManager::has_task_for_cabin_floor_direction(cabin_id_t cabin_id, int floor, direction_t direction) const
{
    return std::any_of(_tasks.begin(), _tasks.end(),
        [cabin_id, floor, direction](const Task& task) {
            return task.get_cabin_id() == cabin_id && 
                   task.get_floor() == floor && 
                   task.get_direction() == direction;
        });
}

bool TaskManager::has_tasks_for_cabin(cabin_id_t cabin_id) const
{
    return std::any_of(_tasks.begin(), _tasks.end(),
        [cabin_id](const Task& task) {
            return task.get_cabin_id() == cabin_id;
        });
}

bool TaskManager::has_any_tasks() const
{
    return !_tasks.empty();
}

bool TaskManager::has_floor_call_up(cabin_id_t cabin_id, int floor) const
{
    return std::any_of(_tasks.begin(), _tasks.end(),
        [cabin_id, floor](const Task& task) {
            return task.get_cabin_id() == cabin_id && 
                   task.get_floor() == floor && 
                   task.get_direction() == DIR_UP &&
                   task.get_type() == TASK_FLOOR_CALL;
        });
}

bool TaskManager::has_floor_call_down(cabin_id_t cabin_id, int floor) const
{
    return std::any_of(_tasks.begin(), _tasks.end(),
        [cabin_id, floor](const Task& task) {
            return task.get_cabin_id() == cabin_id && 
                   task.get_floor() == floor && 
                   task.get_direction() == DIR_DOWN &&
                   task.get_type() == TASK_FLOOR_CALL;
        });
}

bool TaskManager::has_cabin_call(cabin_id_t cabin_id, int floor) const
{
    return std::any_of(_tasks.begin(), _tasks.end(),
        [cabin_id, floor](const Task& task) {
            return task.get_cabin_id() == cabin_id && 
                   task.get_floor() == floor && 
                   task.get_type() == TASK_CABIN_CALL;
        });
}

int TaskManager::get_task_count_for_cabin(cabin_id_t cabin_id) const
{
    return std::count_if(_tasks.begin(), _tasks.end(),
        [cabin_id](const Task& task) {
            return task.get_cabin_id() == cabin_id;
        });
}

void TaskManager::print_all_tasks() const
{
    qInfo("=== Все задачи (%zu) ===", _tasks.size());
    for (const auto& task : _tasks)
    {
        qInfo("%s", task.to_string().c_str());
    }
    qInfo("==============================");
}

std::vector<Task> TaskManager::filter_tasks(std::function<bool(const Task&)> predicate) const
{
    std::vector<Task> result;
    std::copy_if(_tasks.begin(), _tasks.end(), std::back_inserter(result), predicate);
    return result;
} 