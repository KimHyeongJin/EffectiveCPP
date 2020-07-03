//�׸�35_private�����Լ�.cpp
#include <iostream>

//�׸�35
//�񰡻� �������̽� ���뱸�� ���� ���ø� �޼��� ����
class GameCharacter
{
public:
	//healthValue()�� �Լ��� �ζ��� �Լ�
	int healthValue() const//�Ļ� Ŭ������ ���� �� �Լ��� �������� �� ����.
	{
		printf_s("healthValue");
		//"����" ������ �����մϴ�. �Ʒ��� ���ּ���.
		int retVal = doHealthValue();//���� ������ �����մϴ�.
		//"����" ������ �����մϴ�. �Ʒ��� ���ּ���.
		return retVal;
	}
private:
	virtual int doHealthValue() const//�Ļ� Ŭ������ �� �Լ��� �������� �� �ֽ��ϴ�.
	{
		printf_s("doHealthValue");
		//ĳ������ ü��ġ ����� ���� �⺻ �˰��� ����
		return 1;
	}
};
//����ڷ� �Ͽ��� public �񰡻� ��� �Լ��� ���� private ���� �Լ��� ���������� ȣ���ϰ� ����� �������,
//�񰡻� �Լ� �������̽�(non-virtual interface:NVI) ���뱸��� ���� �˷��� ������. ��� �� ���뱸��
//���ø� �޼���(Template Method)�� �Ҹ��� ���� ������ ������ C++ ������ ������ ���Դϴ�.
//������ ��쿣 �� ���뱸�� ���̴� �񰡻� �Լ�(�̸��׸� healthValue)�� ���� �Լ��� ����(wrapper)��� �θ�����

class Char1:public GameCharacter
{
private:
	virtual int doHealthValue() const
	{
		printf_s("�Ļ� Ŭ�������� �������� doHealthValue");
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
"�Ļ� Ŭ�������� �������� doHealthValue"
*/