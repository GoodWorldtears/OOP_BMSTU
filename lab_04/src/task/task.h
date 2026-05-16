#pragma once

#include "../defines.h"

enum task_type_t
{
    TASK_FLOOR_CALL,
    TASK_CABIN_CALL
};

class Task
{
public:
    Task(int floor, direction_t direction, cabin_id_t cabin_id, task_type_t type);
    
    int get_floor() const { return _floor; }
    direction_t get_direction() const { return _direction; }
    cabin_id_t get_cabin_id() const { return _cabin_id; }
    task_type_t get_type() const { return _type; }
    
    bool operator==(const Task& other) const;
    bool operator!=(const Task& other) const;
    
    std::string to_string() const;

private:
    int _floor;
    direction_t _direction;
    cabin_id_t _cabin_id;
    task_type_t _type;
}; 