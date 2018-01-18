#include<iostream>

#include"include\grapics\Window.h"
#include"include/math/Vector2.h"

int main()
{
	nano::graphics::Window window(nano::math::Vector2(500, 500), "Save it");

	while (window.IsOpen()) 
	{
		window.Clear();

		window.Display();
	}

	return 0;
}