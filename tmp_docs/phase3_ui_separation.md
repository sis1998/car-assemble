# Phase 3: UI 계층 분리

## 목표
`main()`에 뒤섞인 입력 처리, 화면 출력, 상태 흐름 제어를 분리하여 도메인 로직과 UI 로직을 독립시킨다.

## 현재 문제
- `main()` 약 170줄에 화면 출력 / 입력 파싱 / 상태 흐름 / 유효성 검사 호출이 모두 혼재
- `printf()` + `fgets()` + `strtol()` 파싱이 `main()` 안에 직접 작성됨
- `delay()`가 busy-wait(`volatile int sum`) 으로 구현 → CPU 점유, 이식성 없음

## 변경 방향

### 파일 구조 (신규 생성)
```
ConsoleUI.h / ConsoleUI.cpp   — 화면 출력 및 사용자 입력 담당
CarAssemblyApp.h / CarAssemblyApp.cpp — 조립 흐름(스텝 전환) 담당
```

### 역할 분리
| 클래스 | 책임 |
|--------|------|
| `ConsoleUI` | 메뉴 출력, 입력 읽기, 파싱, 에러 메시지 출력 |
| `CarAssemblyApp` | 단계 흐름 제어 (CarType → Engine → Brake → Steering → Test) |
| `Car` | 선택된 부품 상태 보관 (Phase 1) |
| `CarValidator` | 제약조건 검증 (Phase 2) |

### main() 의 최종 형태
```cpp
int main() {
    CarAssemblyApp app;
    app.run();
    return 0;
}
```

### delay() 개선
- busy-wait 제거
- `#include <thread>` + `std::this_thread::sleep_for()` 로 교체

## 완료 기준
- `main()` 이 10줄 이내로 줄어듦
- 도메인 클래스(Car, CarValidator)가 `printf` / `scanf` 등 UI 코드에 의존하지 않음
- 단계 흐름 제어가 `CarAssemblyApp` 한 곳에서만 관리됨
