#include "Empty.h"
#include <iostream>

int main()
{
	Empty ept;
	BytePadding bp;
	//����ü ��� ������ 4����Ʈ�� �����ص� 1����Ʈ��� ����� ����... ��� ������ ��� �׷��ɱ�?
	std::cout << sizeof(ept) << std::endl;

	//����ü ��� ������ 4����Ʈ�� �����ϸ� ��°�� 8
	std::cout << sizeof(bp) << std::endl;
	return 0;
}
//��°�� 1