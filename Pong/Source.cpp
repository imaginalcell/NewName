#include <ctime>
#include "sfwdraw.h"
#include <iostream>
#include <cstdlib>

const int scrnWidth = 800;
const int scrnHeight = 600;

float plrOneP = 0;
float plrTwoP = 520;
float plrHeight = 85;
float plrSpeed = 600;

float radius = 8;
float xpos = 400, ypos = 300;
float xvel = 0, yvel = 0;
float speed = 200;

int delay = 3300;
int plrOneLife = 3;
int plrTwoLife = 3;

void Collision()
{
	if (ypos < radius) yvel *= -1;
	if (ypos > scrnHeight - radius) yvel *= -1;

	if (ypos >= plrTwoP &&	// ball is below the top of the right paddle
		ypos <= plrTwoP + plrHeight && // ball is above the bottom of the right paddle
		xpos + radius >= 795) //if the balls x position is past the paddles x position
	{
		xvel *= -1;
	}

	if (ypos >= plrOneP && //check if ball is below top of the left paddle
		ypos <= plrOneP + plrHeight &&//ball is above the bottom of the left paddle
		xpos - radius <= 5) //if the balls x position is past the paddles x position
	{
		xvel *= -1;
	}
}

void Life()
{

	if (xpos < 2)
	{
		plrOneLife--;
		xpos = 400;
		ypos = 300;
	}
	if (xpos > scrnWidth - 3)
	{
		plrTwoLife--;
		xpos = 400;
		ypos = 300;
	}
	if (plrOneLife == 0)
	{
		std::cout << "player two wins" << std::endl;
		system("pause");
	}
	if (plrTwoLife == 0)
	{
		std::cout << "player one wins" << std::endl;
		system("pause");
	}
}

int main()
{
	//Sets window
	sfw::initContext(scrnWidth, scrnHeight, "Pong");

	while (sfw::stepContext())
	{
		Collision();
		Life();

		//player one
		sfw::drawLine(5, plrOneP, 5, plrOneP + plrHeight);
		if (sfw::getKey('q')) plrOneP -= plrSpeed * sfw::getDeltaTime();
		if (sfw::getKey('a')) plrOneP += plrSpeed * sfw::getDeltaTime();

		if (plrOneP < 0) plrOneP = 0;
		if (plrOneP > scrnHeight - plrHeight) plrOneP = scrnHeight - plrHeight;
		//player two
		sfw::drawLine(795, plrTwoP, 795, plrTwoP + plrHeight);
		if (sfw::getKey('p')) plrTwoP -= plrSpeed * sfw::getDeltaTime();
		if (sfw::getKey(';')) plrTwoP += plrSpeed * sfw::getDeltaTime();

		if (plrTwoP < 0) plrTwoP = 0;
		if (plrTwoP > scrnHeight - plrHeight) plrTwoP = scrnHeight - plrHeight;
		//ball
		xpos += xvel * sfw::getDeltaTime();
		ypos += yvel * sfw::getDeltaTime();

		sfw::drawCircle(xpos, ypos, radius);

		delay--;
		if (delay == 0)
		{
			xvel = speed;
			yvel = speed + 50;
		}
	}
	sfw::termContext();
}