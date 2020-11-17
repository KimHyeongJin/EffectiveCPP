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
	virtual void draw(ShapeColor color = Green) const;
};

void Rectangle::draw(ShapeColor color) const 
{
	std::cout << color << std::endl;
}