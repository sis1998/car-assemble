#include "Car.h"

void Car::setCarType(CarType type)             { carType_       = type;     }
void Car::setEngine(Engine engine)             { engine_        = engine;   }
void Car::setBrakeSystem(BrakeSystem brake)    { brakeSystem_   = brake;    }
void Car::setSteeringSystem(SteeringSystem s)  { steeringSystem_ = s;       }

std::optional<CarType>        Car::getCarType()        const { return carType_;        }
std::optional<Engine>         Car::getEngine()         const { return engine_;         }
std::optional<BrakeSystem>    Car::getBrakeSystem()    const { return brakeSystem_;    }
std::optional<SteeringSystem> Car::getSteeringSystem() const { return steeringSystem_; }

bool Car::isFullyAssembled() const
{
    return carType_.has_value()       &&
           engine_.has_value()        &&
           brakeSystem_.has_value()   &&
           steeringSystem_.has_value();
}
