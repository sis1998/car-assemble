# CLAUDE.md

## 프로젝트 개요
차량 조립 시스템 — 절차지향 레거시 코드를 객체지향으로 리팩토링하는 실습 프로젝트

## 필수 참고 문서
- 제품 요구사항: `docs/PRD.md`
- 제약 조건: `docs/RESTRICT.md`

코드 작성 및 수정 시 위 두 문서의 요구사항과 제약조건을 반드시 반영해야 한다.

## 리팩토링 목표
- 절차지향 구조를 객체지향으로 전환
- 타입 안전한 문법 사용 (전역 배열, 매직 넘버 제거)
- 확장성 고려: 새로운 차량 타입 및 부품 추가가 용이한 구조
- 유닛테스트 작성 (Google Mock / gtest 사용)

## 기술 스택
- 언어: C++
- 테스트 프레임워크: Google Test / Google Mock (gmock)
- 빌드: Visual Studio (MSVC)

## 코드 작성 규칙
- 제약조건 검증 로직은 한 곳에서만 관리한다 (중복 금지)
- 각 클래스는 단일 책임을 갖는다 (SRP)
- `#ifdef _DEBUG` 블록에서 gmock 테스트가 실행된다

---

## 개발 계획 (Phase 0 → 4)

- Phase 0 — 테스트 환경 구축: `tmp_docs/phase0_test_env.md`
- Phase 1 — 도메인 모델 구현: `tmp_docs/phase1_domain_model.md`
- Phase 2 — 검증 로직 분리: `tmp_docs/phase2_validator.md`
- Phase 3 — UI 계층 분리: `tmp_docs/phase3_ui_separation.md`
- Phase 4 — 유닛테스트 작성: `tmp_docs/phase4_unit_test.md`
