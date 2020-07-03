//항목35_함수포인터로구현한전략패턴.cpp

#include <iostream>

//항목35
//함수 포인터로 구현한 전략 패턴

class GameCharacter;//전방 선언

//체력치 계산에 대한 기본 알고리즘을 구현한 함수
int defaultHealthCalc( const GameCharacter& gc );

class GameCharacter
{
public:
	typedef int (*HealthCalcFunc)(const GameCharacter& );
	
	explicit GameCharacter( HealthCalcFunc hcf = defaultHealthCalc ):healthFunc( hcf ){}


	//healthValue()는 함수는 인라인 함수
	int healthValue() const//파생 클래스는 이제 이 함수를 재정의할 수 없다.
	{		
		return healthFunc(*this);
	}
private:
	HealthCalcFunc healthFunc;
};


//같은 캐릭터 타입으로부터 만들어진 객체들도 체력치 계산 함수를 각각 다르게 가질 수 있습니다. 즉, 이런 게 가능하다는 이야기죠
class EvilBadGuy:public GameCharacter
{
public:
	explicit EvilBadGuy( HealthCalcFunc hcf = defaultHealthCalc ):GameCharacter( hcf ){} 
};

int defaultHealthCalc( const GameCharacter& gc )
{
	printf_s("defaultHealthCalc 구현 함수\n");
	return 1;
}

int loseHealthQuickly( const GameCharacter& gc )//다른 동작 원리로 구현된 체력치 계산 함수들
{
	printf_s("loseHealthQuickly 구현 함수\n");
	return 1;
}
int loseHealthSlowly( const GameCharacter& gc )//다른 동작 원리로 구현된 체력치 계산 함수들
{
	printf_s("loseHealthSlowly 구현 함수\n");
	return 1;
}

//게임이 실행되는 도중에 특정 캐릭터에 대한 체력치 계산 함수를 바꿀 수 있습니다.
//예를 들어 GameCharacter 클래스에서 setHealthCalculator 라는 멤버 함수를 제공하고 있다면
//이를 통해 현재 쓰이는 체력치 계산 함수의 교체가 가능해지는 것이죠

int main(void)
{
	EvilBadGuy ebg1( loseHealthQuickly );
	EvilBadGuy ebg2( loseHealthSlowly );

	ebg1.healthValue();
	ebg2.healthValue();
	return 0;
}
/*
OutPut
loseHealthQuickly 구현 함수
loseHealthSlowly 구현 함수

*/