#pragma once

#include <optional>
#include "CarType.h"
#include "Engine.h"
#include "BrakeSystem.h"
#include "SteeringSystem.h"

class Car
{
public:
    void setCarType(CarType type);
    void setEngine(Engine engine);
    void setBrakeSystem(BrakeSystem brake);
    void setSteeringSystem(SteeringSystem steering);

    std::optional<CarType>       getCarType()       const;
    std::optional<Engine>        getEngine()        const;
    std::optional<BrakeSystem>   getBrakeSystem()   const;
    std::optional<SteeringSystem> getSteeringSystem() const;

    bool isFullyAssembled() const;

private:
    std::optional<CarType>        carType_;
    std::optional<Engine>         engine_;
    std::optional<BrakeSystem>    brakeSystem_;
    std::optional<SteeringSystem> steeringSystem_;
};
