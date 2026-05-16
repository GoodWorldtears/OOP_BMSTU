#pragma once

#include "task.h"
#include <vector>
#include <functional>

class TaskManager
{
public:
    TaskManager();
    
    // Управление задачами
    void add_task(const Task& task);
    bool remove_task(const Task& task);
    void clear_all_tasks();
    void clear_tasks_for_cabin(cabin_id_t cabin_id);
    
    // Поиск задач с фильтрами
    std::vector<Task> get_tasks_for_cabin(cabin_id_t cabin_id) const;
    std::vector<Task> get_tasks_for_floor(int floor) const;
    std::vector<Task> get_tasks_for_cabin_and_floor(cabin_id_t cabin_id, int floor) const;
    std::vector<Task> get_tasks_by_direction(cabin_id_t cabin_id, direction_t direction) const;
    std::vector<Task> get_tasks_by_type(cabin_id_t cabin_id, task_type_t type) const;
    
    // Проверки существования
    bool has_task_for_cabin_and_floor(cabin_id_t cabin_id, int floor) const;
    bool has_task_for_cabin_floor_direction(cabin_id_t cabin_id, int floor, direction_t direction) const;
    bool has_tasks_for_cabin(cabin_id_t cabin_id) const;
    bool has_any_tasks() const;
    
    // Специальные методы для логики лифта
    bool has_floor_call_up(cabin_id_t cabin_id, int floor) const;
    bool has_floor_call_down(cabin_id_t cabin_id, int floor) const;
    bool has_cabin_call(cabin_id_t cabin_id, int floor) const;
    
    // Утилиты
    int get_task_count_for_cabin(cabin_id_t cabin_id) const;
    std::vector<Task> get_all_tasks() const { return _tasks; }
    
    // Для отладки
    void print_all_tasks() const;

private:
    std::vector<Task> _tasks;
    
    // Вспомогательные методы
    std::vector<Task> filter_tasks(std::function<bool(const Task&)> predicate) const;
}; 