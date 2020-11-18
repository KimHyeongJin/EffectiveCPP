#include "Shape.h"


int main()
{
	Shape* pr = new Rectangle();
	/*
	뭐? pr의 정적 타입은 Shape* 이기 때문에, 지금 호출되는 가상 함수에 쓰이는 기본 매개변
	수 값은 Shape::Red를 사용한다????? 다음 코드를 다시 확인 하자!!!!!
	pr->draw(); // Rectangle::draw(Shape::Red)를 호출한단 말입니다!
	왜? 이유는 항목37의 107 줄을 확인 읽어보자!!!
	*/
	pr->draw();// 출력 0, 코드 힌트에도 ShapeColor color = Red 이렇게 쓰여있다

	if (pr)
	{
		delete pr;
		pr = NULL;
	}
	return 0;
}