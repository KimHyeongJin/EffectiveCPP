/*//항목35_tr1::function으로 구현한 전략 패턴.cpp
#include <functional>
#include <algorithm> 
#include <iostream>
//#include "boost/bind/bind.hpp"
//#include "boost/function/function_base.hpp"


using namespace std;
using namespace std::tr1::placeholders;

class GameCharacter;

int defaultHealthCalc( const GameCharacter& gc );
short calcHealth(const GameCharacter& );//체력치 계산 함수입니다. 반환 타입이 int가 아닌 부분에 주목!

class GameCharacter
{
public:
	//HealthCalcFunc는 함수호출성 개체로서, GameCharacter와 호환되는 어떤 것이든
	//넘겨받아서 호출될 수 있으며 int와 호환되는 모든 타입의 객체를 반환합니다.
	//자세한 내용은 아래를 보시면 나옵니다.
	typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;
	
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc ):healthFunc( hcf ){}

	int healthValue() const
	{
		return healthFunc(*this);
	}
protected:
private:
	HealthCalcFunc healthFunc;
};

//체력치 계산용 함수 객체를 만들기 위한 클래스
struct HealthCalculator
{
	int operator()(const GameCharacter&)const
	{
		printf_s("HealthCalculator 구조체의 함수");
		return 1;
	}
	//형변환 연산자는
	//operator int(){return num}...이런식임 형 변환 연산자는 반환형을 명시하지 않는다.
};

class GameLevel
{
public:
	float health( const GameCharacter& )const
	{
		printf_s("health 구현 함수");
		return 0.01f;
	}//체력치 계산에 쓰일 멤버 함수입니다. 반환 타입이 int가 아닌 부분에 주목하세요.
};

class EvilBadGuy:public GameCharacter
{
public:
	explicit EvilBadGuy( HealthCalcFunc hcf = defaultHealthCalc ):GameCharacter( hcf ){} 
};

class EyeCandyCharacter:public GameCharacter
{
public:
	explicit EyeCandyCharacter( HealthCalcFunc hcf = defaultHealthCalc ):GameCharacter( hcf ){} 
};

int defaultHealthCalc( const GameCharacter& gc )
{
	printf_s("defaultHealthCalc 구현 함수\n");
	return 1;
}

short calcHealth( const GameCharacter& gc )
{
	printf_s("calcHealth 구현 함수\n");
	return 1;
}

int main(void)
{
	//반환형이 short인 일반 함수 calcHealth()
	EvilBadGuy ebg1(calcHealth);//체력치 계산을 위한 함수 객체를 사용하는 캐릭터
	ebg1.healthValue();

	//EyeCandyCharacter ecc1( HealthCalculator() );//직접 사용불가?//체력치 계산을 위한 함수 객체를 사용하는 캐릭터
	HealthCalculator h;
	EvilBadGuy ebg3(h);
	ebg3.healthValue();

	GameLevel currentLevel;
	EvilBadGuy ebg2( std::tr1::bind(&GameLevel::health, currentLevel,_1));//체력치 계산을 위한 멤버 함수를 사용하는 캐릭터입니다.
	currentLevel.health(ebg2);
	return 0;
}//*/


//*/
// std_tr1__functional__placeholder.cpp 
// compile with: /EHsc 
#include <functional> 
#include <algorithm> 
#include <iostream> 

using namespace std::tr1::placeholders; 

void square(double x) 
{ 
	std::cout << x << "^2 == " << x * x << std::endl; 
} 

void product(double x, double y) 
{ 
	std::cout << x << "*" << y << " == " << x * y << std::endl; 
} 

int x_minus_y(int x, int y)
{
	return x-y;
}

int main() 
{ 
	double arg[] = {1, 2, 3}; 

	int _99 = 9;
	printf_s("_gg %d\n",_99);

	std::for_each(&arg[0], &arg[3], square); 
	std::cout << std::endl; 

	std::for_each(&arg[0], &arg[3], std::tr1::bind(product, _1, 2));//2번째 인자를 2로 고정 
	std::cout << std::endl; 

	std::for_each(&arg[0], &arg[3], std::tr1::bind(square, _1)); 

	return (0);
} 
//Output
//1^2 == 1
//2^2 == 4
//3^2 == 9
//
//1*2 == 2
//2*2 == 4
//3*2 == 6
//
//1^2 == 1
//2^2 == 4
//3^2 == 9

//*/