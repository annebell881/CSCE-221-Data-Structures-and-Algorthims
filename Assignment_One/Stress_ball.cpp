#include "Stress_ball.h"
#include <iostream>

using namespace std;

Stress_ball:: Stress_ball(): color(Stress_ball_colors (std::rand()%4)),size(Stress_ball_sizes (std::rand()%3)){}
Stress_ball:: Stress_ball(Stress_ball_colors c, Stress_ball_sizes s): color(c),size(s){}

