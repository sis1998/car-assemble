# Phase 4: gmock 환경 설정 + 유닛테스트 작성

## 목표
vcpkg로 googletest를 프로젝트에 추가하고, `CarValidator`를 중심으로 유닛테스트를 작성한다.

## 환경 설정 절차
1. vcpkg 설치 및 VS 통합
   ```
   git clone https://github.com/microsoft/vcpkg C:\vcpkg
   C:\vcpkg\bootstrap-vcpkg.bat
   C:\vcpkg\vcpkg integrate install
   ```
2. googletest 설치
   ```
   C:\vcpkg\vcpkg install gtest:x64-windows
   ```
3. `.vcxproj`에 헤더/라이브러리 경로 자동 반영됨 (integrate install 이후)

## 테스트 대상
도메인 로직인 `CarValidator`가 핵심 테스트 대상. UI(`ConsoleUI`, `CarAssemblyApp`)는 테스트 제외.

## 작성할 테스트 케이스

### 정상 조합 (PASS 기대)
| CarType | Engine | BrakeSystem | SteeringSystem |
|---------|--------|-------------|----------------|
| Sedan   | GM     | Mando       | Bosch          |
| Sedan   | GM     | Bosch       | Bosch          |
| SUV     | GM     | Continental | Mobis          |
| Truck   | GM     | Continental | Mobis          |

### 제약조건 위반 (FAIL 기대)
| 위반 제약 | CarType | Engine | BrakeSystem | SteeringSystem |
|----------|---------|--------|-------------|----------------|
| Sedan + Continental 불가 | Sedan | GM | Continental | Bosch |
| SUV + Toyota 불가 | SUV | Toyota | Mando | Bosch |
| Truck + WIA 불가 | Truck | WIA | Mando | Bosch |
| Truck + Mando 불가 | Truck | GM | Mando | Bosch |
| Bosch 제동 → Mobis 조향 불가 | Sedan | GM | Bosch | Mobis |

## 테스트 코드 구조 예시
```cpp
TEST(CarValidatorTest, Sedan_Continental_ShouldFail) {
    Car car;
    car.setCarType(CarType::Sedan);
    car.setEngine(Engine::GM);
    car.setBrakeSystem(BrakeSystem::Continental);
    car.setSteeringSystem(SteeringSystem::Bosch);

    CarValidator validator;
    auto result = validator.validate(car);

    EXPECT_FALSE(result.isValid);
}
```

## main.cpp _DEBUG 블록
현재 구조 유지:
```cpp
#ifdef _DEBUG
#include "gmock/gmock.h"
int main() {
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
#endif
```

## 완료 기준
- Debug 빌드 시 모든 테스트 케이스가 실행되고 PASS
- 제약조건 위반 케이스가 FAIL 판정으로 정확히 감지됨
- 새 제약조건 추가 시 테스트 케이스 한 줄 추가로 검증 가능
