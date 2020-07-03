//�׸�35_�Լ������ͷα�������������.cpp

#include <iostream>

//�׸�35
//�Լ� �����ͷ� ������ ���� ����

class GameCharacter;//���� ����

//ü��ġ ��꿡 ���� �⺻ �˰����� ������ �Լ�
int defaultHealthCalc( const GameCharacter& gc );

class GameCharacter
{
public:
	typedef int (*HealthCalcFunc)(const GameCharacter& );
	
	explicit GameCharacter( HealthCalcFunc hcf = defaultHealthCalc ):healthFunc( hcf ){}


	//healthValue()�� �Լ��� �ζ��� �Լ�
	int healthValue() const//�Ļ� Ŭ������ ���� �� �Լ��� �������� �� ����.
	{		
		return healthFunc(*this);
	}
private:
	HealthCalcFunc healthFunc;
};


//���� ĳ���� Ÿ�����κ��� ������� ��ü�鵵 ü��ġ ��� �Լ��� ���� �ٸ��� ���� �� �ֽ��ϴ�. ��, �̷� �� �����ϴٴ� �̾߱���
class EvilBadGuy:public GameCharacter
{
public:
	explicit EvilBadGuy( HealthCalcFunc hcf = defaultHealthCalc ):GameCharacter( hcf ){} 
};

int defaultHealthCalc( const GameCharacter& gc )
{
	printf_s("defaultHealthCalc ���� �Լ�\n");
	return 1;
}

int loseHealthQuickly( const GameCharacter& gc )//�ٸ� ���� ������ ������ ü��ġ ��� �Լ���
{
	printf_s("loseHealthQuickly ���� �Լ�\n");
	return 1;
}
int loseHealthSlowly( const GameCharacter& gc )//�ٸ� ���� ������ ������ ü��ġ ��� �Լ���
{
	printf_s("loseHealthSlowly ���� �Լ�\n");
	return 1;
}

//������ ����Ǵ� ���߿� Ư�� ĳ���Ϳ� ���� ü��ġ ��� �Լ��� �ٲ� �� �ֽ��ϴ�.
//���� ��� GameCharacter Ŭ�������� setHealthCalculator ��� ��� �Լ��� �����ϰ� �ִٸ�
//�̸� ���� ���� ���̴� ü��ġ ��� �Լ��� ��ü�� ���������� ������

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
loseHealthQuickly ���� �Լ�
loseHealthSlowly ���� �Լ�

*/