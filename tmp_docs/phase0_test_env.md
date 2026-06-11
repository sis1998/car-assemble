# Phase 0: 테스트 환경 구축 (리팩토링 안전망 확보)

## 목표
Phase 1 리팩토링 이전에 테스트를 실행 가능한 상태로 만든다.
현재 코드의 동작을 테스트로 고정(characterization test)하여,
이후 리팩토링 시 동작이 깨지지 않았음을 검증하는 안전망을 확보한다.

## 핵심 전략: 테스트를 먼저, 리팩토링은 나중에
```
[현재 레거시 코드] → [테스트로 동작 고정] → [Phase 1~3 리팩토링] → [테스트 통과 확인]
```
리팩토링 중 테스트가 FAIL 나면 동작이 바뀐 것이므로 즉시 인지 가능하다.

---

## Step 1: googletest 환경 설정

### vcpkg 설치 및 통합
```
git clone https://github.com/microsoft/vcpkg C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg integrate install
C:\vcpkg\vcpkg install gtest:x64-windows
```

### .vcxproj 확인 사항
- `integrate install` 이후 헤더/라이브러리 경로 자동 반영
- Debug 빌드 시 `_DEBUG` 매크로가 정의되어 main.cpp의 테스트 진입점이 활성화됨

---

## Step 2: 테스트 가능한 최소 구조 분리

### 현재 문제
현재 검증 로직이 `main.cpp` 안의 전역 배열 `int stack[10]`에 직접 의존한다.

```cpp
// isValidCheck()가 전역 stack[]을 직접 참조
int isValidCheck() {
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
        return false;
    ...
}
```

테스트에서 `isValidCheck()`를 호출하려면 전역 상태를 직접 조작해야 한다.
이는 코드 수정을 최소화하면서도 테스트를 가능하게 하는 유일한 방법이다.

### 분리 방법: validation 로직만 별도 파일로 추출

**신규 파일 2개 생성 (코드 이동만, 로직 변경 없음)**

```
CarAssemblyLegacy.h   — 전역 변수/enum/함수 선언 (extern)
CarAssemblyLegacy.cpp — isValidCheck(), testProducedCar() 구현 이동
```

**CarAssemblyLegacy.h**
```cpp
#pragma once

extern int stack[10];

enum QuestionType { CarType_Q, Engine_Q, brakeSystem_Q, SteeringSystem_Q, Run_Test };
enum CarType      { SEDAN = 1, SUV, TRUCK };
enum Engine       { GM = 1, TOYOTA, WIA };
enum brakeSystem  { MANDO = 1, CONTINENTAL, BOSCH_B };
enum SteeringSystem { BOSCH_S = 1, MOBIS };

int  isValidCheck();
void testProducedCar();
```

**main.cpp 변경 최소화**
```cpp
// #else 블록 상단에 추가
#include "CarAssemblyLegacy.h"
// 기존 enum/함수 선언 제거 (헤더로 이동했으므로)
```

**테스트 파일에서 사용**
```cpp
#include "CarAssemblyLegacy.h"

TEST(LegacyValidationTest, Sedan_Continental_ShouldFail) {
    stack[CarType_Q]     = SEDAN;
    stack[Engine_Q]      = GM;
    stack[brakeSystem_Q] = CONTINENTAL;
    stack[SteeringSystem_Q] = BOSCH_S;

    EXPECT_FALSE(isValidCheck());
}
```

---

## Step 3: 작성할 Characterization Test 목록

현재 `isValidCheck()` 동작을 그대로 고정하는 테스트.
리팩토링 전후 동작이 동일함을 보장하는 안전망이다.

### PASS 케이스 (isValidCheck == true 기대)
| 설명 | CarType | Engine | BrakeSystem | SteeringSystem |
|------|---------|--------|-------------|----------------|
| 정상 세단 | SEDAN | GM | MANDO | BOSCH_S |
| Bosch 제동 + Bosch 조향 | SEDAN | GM | BOSCH_B | BOSCH_S |
| 정상 SUV | SUV | GM | CONTINENTAL | MOBIS |
| 정상 트럭 | TRUCK | GM | CONTINENTAL | MOBIS |

### FAIL 케이스 (isValidCheck == false 기대)
| 위반 제약 | CarType | Engine | BrakeSystem | SteeringSystem |
|----------|---------|--------|-------------|----------------|
| Sedan + Continental | SEDAN | GM | CONTINENTAL | BOSCH_S |
| SUV + TOYOTA | SUV | TOYOTA | MANDO | BOSCH_S |
| Truck + WIA | TRUCK | WIA | MANDO | BOSCH_S |
| Truck + MANDO | TRUCK | GM | MANDO | BOSCH_S |
| Bosch 제동 + Mobis 조향 | SEDAN | GM | BOSCH_B | MOBIS |

---

## Step 4: 파일 구조 (이 단계 완료 시)

```
car_assemble/
├── main.cpp                  — #ifdef _DEBUG 테스트 진입점 유지
├── CarAssemblyLegacy.h       — (신규) 전역 선언 / enum / 함수 선언
├── CarAssemblyLegacy.cpp     — (신규) isValidCheck(), testProducedCar() 이동
└── CarAssemblyLegacyTest.cpp — (신규) characterization test
```

---

## 완료 기준
- Debug 빌드 시 `RUN_ALL_TESTS()` 가 실행됨
- PASS/FAIL 케이스 전체가 기대한 결과로 통과
- main.cpp 의 실제 동작 로직은 변경 없음
- 이 테스트들이 Phase 1~3 진행 중 안전망으로 동작함

## Phase 1 이후 이 파일의 운명
Phase 1~3 완료 후 `CarAssemblyLegacy.*` 파일과 이 테스트는
`CarValidator` 기반의 새 테스트(phase4)로 대체되어 삭제된다.
