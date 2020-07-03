//항목35_private가상함수.cpp
#include <iostream>

//항목35
//비가상 인터페이스 관용구를 통한 템플릿 메서드 패턴
class GameCharacter
{
public:
	//healthValue()는 함수는 인라인 함수
	int healthValue() const//파생 클래스는 이제 이 함수를 재정의할 수 없다.
	{
		printf_s("healthValue");
		//"사전" 동작을 수행합니다. 아래를 봐주세요.
		int retVal = doHealthValue();//실제 동작을 수행합니다.
		//"사후" 동작을 수행합니다. 아래를 봐주세요.
		return retVal;
	}
private:
	virtual int doHealthValue() const//파생 클래스는 이 함수를 재정의할 수 있습니다.
	{
		printf_s("doHealthValue");
		//캐릭터의 체력치 계산을 위한 기본 알고리즘 구현
		return 1;
	}
};
//사용자로 하여금 public 비가상 멤버 함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법으로,
//비가상 함수 인터페이스(non-virtual interface:NVI) 관용구라고 많이 알려져 있지요. 사실 이 관용구는
//템플릿 메서드(Template Method)라 불리는 고전 디자인 패턴을 C++ 식으로 구현한 것입니다.
//필자의 경우엔 이 관용구에 쓰이는 비가상 함수(이를테면 healthValue)를 가상 함수의 랩퍼(wrapper)라고 부르지요

class Char1:public GameCharacter
{
private:
	virtual int doHealthValue() const
	{
		printf_s("파생 클래스에서 재정의한 doHealthValue");
		return 10;
	}
};

int main(void)
{
	GameCharacter *p= NULL;
	Char1 char1;
	p = &char1;
	p->healthValue();
	return 0;
}

/*
Output
"파생 클래스에서 재정의한 doHealthValue"
*/