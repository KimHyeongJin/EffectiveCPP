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
	// ��� ���� draw ���� �Լ��� �Ű������� ������ �ߴ�???
	virtual void draw(ShapeColor color = Green) const;
};

void Rectangle::draw(ShapeColor color) const 
{
	std::cout << color << std::endl;
}

// ���� �ذ� ��� 1
class Shape1
{
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color = Red) const	// ���� �񰡻� �Լ��Դϴ�.
	{
		doDraw(color);	// ���� �Լ��� ȣ���մϴ�.
	}
private:
	// ��¥ �۾��� �� �Լ����� �̷������.
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle1 : public Shape1
{
public:
	// �ߺ�����! �⺻ �Ű����� ���� �����ϴ�.
	virtual void doDraw(ShapeColor color) const;
};

void Rectangle1::doDraw(ShapeColor color) const
{
	std::cout << color << std::endl;
}