#include "gmock/gmock.h"
#include "CarAssemblyLegacy.h"

class LegacyValidationTest : public testing::Test
{
protected:
    void SetUp() override
    {
        memset(stack, 0, sizeof(stack));
    }
};

// PASS cases
TEST_F(LegacyValidationTest, NormalSedan_ShouldPass)
{
    stack[CarType_Q]      = SEDAN;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = MANDO;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_TRUE(isValidCheck());
}

TEST_F(LegacyValidationTest, BoschBrake_BoschSteering_ShouldPass)
{
    stack[CarType_Q]      = SEDAN;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = BOSCH_B;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_TRUE(isValidCheck());
}

TEST_F(LegacyValidationTest, NormalSUV_ShouldPass)
{
    stack[CarType_Q]      = SUV;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = CONTINENTAL;
    stack[SteeringSystem_Q] = MOBIS;
    EXPECT_TRUE(isValidCheck());
}

TEST_F(LegacyValidationTest, NormalTruck_ShouldPass)
{
    stack[CarType_Q]      = TRUCK;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = CONTINENTAL;
    stack[SteeringSystem_Q] = MOBIS;
    EXPECT_TRUE(isValidCheck());
}

// FAIL cases
TEST_F(LegacyValidationTest, Sedan_Continental_ShouldFail)
{
    stack[CarType_Q]      = SEDAN;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = CONTINENTAL;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_FALSE(isValidCheck());
}

TEST_F(LegacyValidationTest, SUV_Toyota_ShouldFail)
{
    stack[CarType_Q]      = SUV;
    stack[Engine_Q]       = TOYOTA;
    stack[brakeSystem_Q]  = MANDO;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_FALSE(isValidCheck());
}

TEST_F(LegacyValidationTest, Truck_WIA_ShouldFail)
{
    stack[CarType_Q]      = TRUCK;
    stack[Engine_Q]       = WIA;
    stack[brakeSystem_Q]  = MANDO;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_FALSE(isValidCheck());
}

TEST_F(LegacyValidationTest, Truck_Mando_ShouldFail)
{
    stack[CarType_Q]      = TRUCK;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = MANDO;
    stack[SteeringSystem_Q] = BOSCH_S;
    EXPECT_FALSE(isValidCheck());
}

TEST_F(LegacyValidationTest, BoschBrake_MobisSteering_ShouldFail)
{
    stack[CarType_Q]      = SEDAN;
    stack[Engine_Q]       = GM;
    stack[brakeSystem_Q]  = BOSCH_B;
    stack[SteeringSystem_Q] = MOBIS;
    EXPECT_FALSE(isValidCheck());
}
