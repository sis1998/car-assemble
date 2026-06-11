#pragma once

extern int stack[10];

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

int  isValidCheck();
void testProducedCar();
