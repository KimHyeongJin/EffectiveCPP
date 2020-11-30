#include "Empty.h"
#include <iostream>

int main()
{
	Empty ept;
	BytePadding bp;
	//구조체 멤버 맞춤을 4바이트로 변경해도 1바이트라는 결과가 나옴... 멤버 변수가 없어서 그런걸까?
	std::cout << sizeof(ept) << std::endl;

	//구조체 멤버 맞춤을 4바이트로 변경하면 출력결롸 8
	std::cout << sizeof(bp) << std::endl;
	return 0;
}
//출력결과 1