/*//�׸�35_tr1::function���� ������ ���� ����.cpp
#include <functional>
#include <algorithm> 
#include <iostream>
//#include "boost/bind/bind.hpp"
//#include "boost/function/function_base.hpp"


using namespace std;
using namespace std::tr1::placeholders;

class GameCharacter;

int defaultHealthCalc( const GameCharacter& gc );
short calcHealth(const GameCharacter& );//ü��ġ ��� �Լ��Դϴ�. ��ȯ Ÿ���� int�� �ƴ� �κп� �ָ�!

class GameCharacter
{
public:
	//HealthCalcFunc�� �Լ�ȣ�⼺ ��ü�μ�, GameCharacter�� ȣȯ�Ǵ� � ���̵�
	//�Ѱܹ޾Ƽ� ȣ��� �� ������ int�� ȣȯ�Ǵ� ��� Ÿ���� ��ü�� ��ȯ�մϴ�.
	//�ڼ��� ������ �Ʒ��� ���ø� ���ɴϴ�.
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

//ü��ġ ���� �Լ� ��ü�� ����� ���� Ŭ����
struct HealthCalculator
{
	int operator()(const GameCharacter&)const
	{
		printf_s("HealthCalculator ����ü�� �Լ�");
		return 1;
	}
	//����ȯ �����ڴ�
	//operator int(){return num}...�̷����� �� ��ȯ �����ڴ� ��ȯ���� ������� �ʴ´�.
};

class GameLevel
{
public:
	float health( const GameCharacter& )const
	{
		printf_s("health ���� �Լ�");
		return 0.01f;
	}//ü��ġ ��꿡 ���� ��� �Լ��Դϴ�. ��ȯ Ÿ���� int�� �ƴ� �κп� �ָ��ϼ���.
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
	printf_s("defaultHealthCalc ���� �Լ�\n");
	return 1;
}

short calcHealth( const GameCharacter& gc )
{
	printf_s("calcHealth ���� �Լ�\n");
	return 1;
}

int main(void)
{
	//��ȯ���� short�� �Ϲ� �Լ� calcHealth()
	EvilBadGuy ebg1(calcHealth);//ü��ġ ����� ���� �Լ� ��ü�� ����ϴ� ĳ����
	ebg1.healthValue();

	//EyeCandyCharacter ecc1( HealthCalculator() );//���� ���Ұ�?//ü��ġ ����� ���� �Լ� ��ü�� ����ϴ� ĳ����
	HealthCalculator h;
	EvilBadGuy ebg3(h);
	ebg3.healthValue();

	GameLevel currentLevel;
	EvilBadGuy ebg2( std::tr1::bind(&GameLevel::health, currentLevel,_1));//ü��ġ ����� ���� ��� �Լ��� ����ϴ� ĳ�����Դϴ�.
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

	std::for_each(&arg[0], &arg[3], std::tr1::bind(product, _1, 2));//2��° ���ڸ� 2�� ���� 
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