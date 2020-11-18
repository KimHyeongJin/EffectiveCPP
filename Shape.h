#pragma once
#include <iostream>

class Shape
{
public:
	enum ShapeColor { Red, Green, Blue };
	virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape
{
public:
	// 상속 받은 draw 가상 함수의 매개변수를 재정의 했다???
	virtual void draw(ShapeColor color = Green) const;
};

void Rectangle::draw(ShapeColor color) const 
{
	std::cout << color << std::endl;
}

// 문제 해결 방법 1
class Shape1
{
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color = Red) const	// 이제 비가상 함수입니다.
	{
		doDraw(color);	// 가상 함수를 호출합니다.
	}
private:
	// 진짜 작업은 이 함수에서 이루어진다.
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle1 : public Shape1
{
public:
	// 잘보세요! 기본 매개변수 값이 없습니다.
	virtual void doDraw(ShapeColor color) const;
};

void Rectangle1::doDraw(ShapeColor color) const
{
	std::cout << color << std::endl;
}