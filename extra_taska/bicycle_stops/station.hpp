#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>

class Station {
    std::string name;
    int capacity;
    int bikes;
    int target;
public:
    Station(std::string name_, int capacity_, int bikes_, int target_) {
        name = name_;
        capacity = capacity_;
        bikes = bikes_;
        target = target_;

        if (bikes < 0 || bikes > capacity || target < 0 || target > capacity) {
            throw std::invalid_argument("ERROR: Запас и цель должны быть в пределах вместимости");
        }
    }

    const std::string& get_name() const { return name; }
    int get_capacity() const { return capacity; }
    int get_bikes() const { return bikes; }
    int get_target() const { return target; }
    int get_diff() const { return target - bikes; }

    int transfer_to(Station& destination) {
        int extra = bikes - target;
        int needed = destination.target - destination.bikes;
        if (extra <= 0 || needed <= 0) {
            return 0;
        }

        // Перевозим столько, сколько можем отдать и сколько нужно другой станции.
        int count = std::min(extra, needed);
        bikes -= count;
        destination.bikes += count;
        return count;
    }
};
