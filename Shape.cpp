#include "Shape.h"


int main()
{
	Shape* pr = new Rectangle();
	/*
	��? pr�� ���� Ÿ���� Shape* �̱� ������, ���� ȣ��Ǵ� ���� �Լ��� ���̴� �⺻ �Ű���
	�� ���� Shape::Red�� ����Ѵ�????? ���� �ڵ带 �ٽ� Ȯ�� ����!!!!!
	pr->draw(); // Rectangle::draw(Shape::Red)�� ȣ���Ѵ� ���Դϴ�!
	��? ������ �׸�37�� 107 ���� Ȯ�� �о��!!!
	*/
	pr->draw();// ��� 0, �ڵ� ��Ʈ���� ShapeColor color = Red �̷��� �����ִ�

	if (pr)
	{
		delete pr;
		pr = NULL;
	}
	return 0;
}