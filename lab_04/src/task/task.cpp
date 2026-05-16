#include "task.h"
#include <sstream>

Task::Task(int floor, direction_t direction, cabin_id_t cabin_id, task_type_t type)
    : _floor(floor), _direction(direction), _cabin_id(cabin_id), _type(type)
{
}

bool Task::operator==(const Task& other) const
{
    return _floor == other._floor &&
           _direction == other._direction &&
           _cabin_id == other._cabin_id &&
           _type == other._type;
}

bool Task::operator!=(const Task& other) const
{
    return !(*this == other);
}

std::string Task::to_string() const
{
    std::ostringstream oss;
    oss << "Task{floor=" << _floor 
        << ", dir=" << (_direction == DIR_UP ? "UP" : _direction == DIR_DOWN ? "DOWN" : "STAND")
        << ", cabin=" << _cabin_id 
        << ", type=" << (_type == TASK_FLOOR_CALL ? "FLOOR_CALL" : "CABIN_CALL")
        << "}";
    return oss.str();
} 