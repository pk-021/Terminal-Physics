#include <conio.h>
#include <iostream>
#include "gameLoop.h"
#include "Window.h"
#include "shape.h"
#include <thread>
const float PI = 3.1415;

int main()
{
  GameLoop game;
  game.run(30);
}


