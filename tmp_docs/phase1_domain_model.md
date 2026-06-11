# Phase 1: 도메인 모델 구현

## 목표
전역 배열 `int stack[10]`과 매직 넘버를 제거하고, 각 부품과 차량을 타입 안전한 클래스/구조체로 표현한다.

## 현재 문제
- `int stack[10]` 전역 배열로 모든 선택 상태를 관리 → 인덱스가 의미를 잃음
- enum 값이 1부터 시작하여 배열 인덱스와 혼용되어 혼란
- Engine 선택지 4번 ("없는 엔진")이 enum에 없고 `if (stack[Engine_Q] == 4)` 매직 넘버로 처리

## 변경 방향

### 파일 구조 (신규 생성)
```
CarType.h          — CarType enum class
Engine.h           — Engine enum class
BrakeSystem.h      — BrakeSystem enum class
SteeringSystem.h   — SteeringSystem enum class
Car.h / Car.cpp    — 조립 중인 차량 상태를 보관하는 클래스
```

### Car 클래스 책임
- 선택된 CarType, Engine, BrakeSystem, SteeringSystem을 멤버로 보관
- 각 부품을 설정하는 setter 제공
- `isFullyAssembled()` — 모든 부품이 선택됐는지 여부 반환

### enum class 예시
```cpp
enum class CarType { Sedan, SUV, Truck };
enum class Engine  { GM, Toyota, WIA };
enum class BrakeSystem  { Mando, Continental, Bosch };
enum class SteeringSystem { Bosch, Mobis };
```
- `enum` → `enum class` 로 변경하여 이름 충돌 방지
- `BOSCH_B` / `BOSCH_S` 처럼 구분용 접미사 불필요

## 완료 기준
- `int stack[10]` 전역 배열이 코드에서 완전히 제거됨
- 매직 넘버 없이 enum class 값으로만 비교
- Car 객체 하나로 현재 조립 상태를 표현 가능
