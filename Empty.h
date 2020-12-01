#pragma once

// 항목 39 예제

/*
데이터가 없는 클래스란 비정적 데이터 멤버가 없는 클래스를 일겉습니다.
C++에는 "독립 구조(freestanding)의 객체는 반드시 크기가 0을 넘어야 한다"라는 
금기사항이 있다. 크기가 0인 독립 구조의 객체가 생기는 것을 금지하는 C++의 제약을 
지키기 위해, 컴파일러는 이런 "공백" 객체에 char 한 개를 슬그머니 끼워넣는 식으로 
처리하기 때문입니다.

기본 클래스를 두 개 이상 갖는 파생 클래스에는 EBO가 적용될 수 없다고 하네요.

그런데 눈치가 빠른 독자라면, 아까부터 필자가 객체 크기가 0이면 안 된다는 이야기를
하면서 '독립구조'라는 말을 신경 써서 했던게 수상쩍었을 겁니다. 맞습니다.
C++의 제약은 파생 클래스 객체의 기본 클래스 부분에는 적용되지 않습니다. 이때의
기본 클래스 부분은 독립구조 객체, 다시 말해 홀로서기를 한 객체가 아니기 때문입니다.
*/
class Empty
{
	int Func()// 멤버 함수는 인스턴스 객체의 크기에 포함되지 않는다.
	{
		return 1;
	}
};

//바이트 패딩 테스트 클래스
class BytePadding
{
	char x;
	int y;
};

//sizeof(HoldsAnInt) > sizeof(int)
class HoldsAnInt	// int를 저장할 공간만 필요해야 합니다.
{
private:
	int x;
	Empty e;	// 메모리 요구가 없어야 합니다.
};

//sizeof(HoldsAnInt) == sizeof(int), 여기서 Empty는 독립 구조 객체가 아님
class HoldsAnInt2 : private Empty
{
private:
	int x;
};
/*
sizeof(HoldsAnInt2) == sizeof(int)를 확인할 수 있습니다. 이 공간 절약
기법은 공백 기본 클래스 최적화(Empty Base Opimization:EBO)라고 알려져 있으며,
필자가 테스트한 모든 컴파일러에서 구현하고 있답니다. 메모리 공간에 많이 신경쓰는
사용자를 상대하는 라이브러리 개발자라면 EBO를 알아두는 게 좋을 것입니다. 이와
더불어 알아두면 쓸 만한 사실이 하나 더 있는데, EBO는 일반적으로 단일 상속에서만
적용된다는 점입니다. C++ 객체의 레이아웃을 결정하는 규칙이 일반적으로 이러저러한
관계로, 기본 클래스를 두 개 이상 갖는 파생 클래스에는 EBO가 적용될 수 없다고
하네요.
*/