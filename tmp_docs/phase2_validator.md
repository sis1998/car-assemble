# Phase 2: 검증 로직 분리 (CarValidator)

## 목표
`isValidCheck()`와 `testProducedCar()`에 중복된 동일한 조건 로직을 단일 `CarValidator` 클래스로 통합한다.

## 현재 문제
`isValidCheck()`와 `testProducedCar()` 두 함수가 동일한 5가지 조건을 각각 독립적으로 구현.
제약조건이 추가되면 두 곳을 동시에 수정해야 하는 구조.

```cpp
// isValidCheck() 와 testProducedCar() 에 동일한 조건이 중복
if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL) ...
if (stack[CarType_Q] == SUV   && stack[Engine_Q] == TOYOTA) ...
// ... 동일 패턴 반복
```

## 변경 방향

### 파일 구조 (신규 생성)
```
CarValidator.h / CarValidator.cpp
```

### CarValidator 클래스 책임
- `Car` 객체를 받아 제약조건 위반 여부를 판정
- `validate(const Car&)` → `ValidationResult` 반환
  - 성공 여부 (`bool isValid`)
  - 실패 사유 문자열 (`std::string reason`)
- 내부적으로 각 제약조건을 별도 private 메서드로 분리

### 구조 예시
```cpp
class CarValidator {
public:
    ValidationResult validate(const Car& car) const;
private:
    bool checkBrakeSteeringCompatibility(const Car&) const; // 제약조건 1
    bool checkCarTypePartCompatibility(const Car&) const;   // 제약조건 2
};
```

### docs/RESTRICT.md 와의 대응
| 제약조건 | 담당 메서드 |
|---------|------------|
| Bosch 제동 → Bosch 조향 필수 | `checkBrakeSteeringCompatibility` |
| Sedan + Continental 불가 | `checkCarTypePartCompatibility` |
| SUV + Toyota 불가 | `checkCarTypePartCompatibility` |
| Truck + WIA 불가 | `checkCarTypePartCompatibility` |
| Truck + Mando 불가 | `checkCarTypePartCompatibility` |

## 완료 기준
- 제약조건 로직이 `CarValidator` 한 곳에만 존재
- `runProducedCar()`, `testProducedCar()` 모두 `CarValidator::validate()` 결과를 사용
- 새 제약조건 추가 시 `CarValidator` 만 수정하면 됨
