[추가한 클래스]

1.TJProjectile(일반 발사체)
- 다른 발사체들의 Parent class

2. TJChargeProjectile(충전 발사체)
- TJProjectile의 subclass
- 3초간 Q키를 누른 후 떼면 일반 대신 충전 발사체가 발사

3. TJSplitProjectile(분열 발사체)
- TJProjectile의 subclass
- -45, 45 degree 각도로 ArrowComponent 추가 생성
- BeginPlay에서 3초후 분열 및 파괴하는 람다를 델리게이트로 호출

4. TJReflectProjectile(반사 발사체)
- TJProjectile의 subclass
- bShouldBounce를 활성화해 충돌 후에도 simulate를 계속하도록 세팅
- OnHit시 Velocity를 반대 방향으로 바꿔줌
- 노멀벡터를 기준으로 반사하는 방향으로 코드를 짰다가 진행 방향의 반대 방향으로 바꿔주는 것으로 변경

5. TJCharacter (플레이어)
- 기본 템플릿에서 사용하는 SideScrollerCharacter의 Parent class를 이 클래스로 설정
- 입력 바인딩 및 프로젝타일 발사
- 키 입력 상태에 따른 ui 업데이트 델리게이트 호출

6. TJPlayerController (플레이어 컨트롤러)
- 블루 프린트 위젯을 찾아서 UI Widget을 코드에서 생성하고 뷰포트에 추가

7. TJProjectileRecordComponent (프로젝타일 발사 개수 기록)
- 플레이어가 발사한 프로젝타일 개수 기록
- 개수 업데이트 시 멀티캐스트 델리게이트를 호출하여 UI에 업데이트 (멀티캐스트일 이유는 없으나 사용해봄)
- 리셋 버튼이 눌리면 개수를 초기화하고 UI에 업데이트

8. TJUIWidget (UI 위젯)
- 프로젝타일 개수 업데이트시 델리게이트로 호출되어 UI를 업데이트
- 캐릭터의 충전 상태 변경시 델리게이트로 호출되어 충전 UI의 visibility를 세팅
- 캐릭터의 충전 시간 변경시 델리게이트로 호출되어 충전 UI의 progressbar를 업데이트

[추가사항]
- 마지막으로 눌린 키에 우선권을 주었습니다
- Q가 1초 이상 charge된 후에 W를 누를 시 Q의 입력이 취소되고 W의 입력을 계산 (이 상태에서는 Q를 떼도 일반이나, 충전이 발사되지 않음)
- W를 누른 상태에서 떼지않고 Q를 눌렀을 경우 W의 입력이 취소되고 Q의 입력을 계산 (이 상태에서는 W를 떼도 반사 발사체가 발사되지 않음)

- 프로젝타일이 발사된 시점에는 모든 키의 입력이 초기화됩니다.
- 충전이 1초 이하인 상태에서 W를 누를 시 분열 발사체가 발사되고, Q,W의 입력상태가 초기화 (이 상태에서는 Q나 W를 떼도 일반이나, 반사가 발사되지 않음)
