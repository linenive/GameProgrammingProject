# RPG 마을 타이쿤(Beginner Village)

## Description
2021.09. - 2021.12.

PC 게임 (건설 경영 시뮬레이션 / 샌드박스 장르)

4인 개발

## 프로젝트 정보
#### 프로젝트 파일 열기
Godot v3.3.2 이상, 프로젝트 파일: project.godot
#### 컴파일 방법
CPP 폴더 내에서 Scons를 이용해 컴파일합니다.
```
scons platform=windows
```

## About Project
#### 설계
내부 시스템은 C++를, 그래픽은 GDScript를 이용하여 구현

<img width="899" alt="기본 구조" src="https://user-images.githubusercontent.com/12760801/153190799-b42cee79-013d-47fe-9564-53fb537a9331.PNG">

게임 시스템은 Manager, Service, Repository의 세 가지 계층 구조로 디자인

<img width="898" alt="기본 구조2" src="https://user-images.githubusercontent.com/12760801/153191202-f4e7ea09-eb09-4030-b264-90dc2c559e90.PNG">

#### 건설
건축 미리보기
+ 미리보기용 객체 생성
+ 타일 시스템에 꼭 맞게(cling) 표시
+ 건설 가능 여부 색깔로 표시

건축
+ 건물/가구 Service에서 Factory를 사용해 생성 및 관리
+ godot로 새 건물 signal->draw

![건축-small](https://user-images.githubusercontent.com/12760801/153189443-72231a96-3445-4c01-9e3c-875de4514242.gif)

#### AI 시스템
+ Priority를 이용해 Task를 결정하는 시스템
+ 각 Task들은 Rule System 기반으로 행동
+ 이동: Pathfinding algorithm(A*) + Steering behavior

![AI-small](https://user-images.githubusercontent.com/12760801/153189951-b8f30fbd-b488-4e18-bf10-ef6663333d5d.gif)

#### 방문객 시스템
+ 중복 이름이 없도록 이름 풀 관리
+ 랜덤 스킬: 캐릭터의 행동에 영향을 미침. 이동속도가 빨라지거나 작업 속도가 빨라짐.
+ 마을 방문 목적 랜덤 생성: 그냥 지나가기, 특정 물건 구매, 잠깐 쉬기 등

![관리-small](https://user-images.githubusercontent.com/12760801/153189625-32dfab9e-3c0b-4b89-921f-603afe565e43.gif)

