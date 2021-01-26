#pragma once

#include <chrono>
#include <mutex>
#include <optional>
#include <set>

#include "caretaker/PlantCaretaker.hpp"

namespace sensors {
class SunlightSensor {
    using TimePoint = decltype(std::chrono::system_clock::now());

    const std::chrono::seconds sleepTime;
    std::mutex& mtx;
    std::set<caretaker::PlantCaretaker*> caretakers;

    std::optional<TimePoint> sunlightOnFrom;
    std::optional<TimePoint> sunlightOffFrom;

    const int threshold = 2;
    bool sensorOn = true;

public:
    SunlightSensor(const std::chrono::seconds, std::mutex&);
    void subscribe(caretaker::PlantCaretaker&);
    void operator()();

private:
    void updateState(const bool);
    bool isTooMuchSunlight(const bool);
    bool isTooLittleSunlight(const bool);
    bool isSunlight() const;
};
} // namespace sensors