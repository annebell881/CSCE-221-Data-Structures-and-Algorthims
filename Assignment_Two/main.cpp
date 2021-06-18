#include <iostream>
#include "Collection.h"
#include "Stress_ball.h"
#include <string>

using namespace std;

int main(){
	
	Stress_ball test1;
	std::cout << test1 << std::endl;
	
	Stress_ball test2;
	std::cout << test2 << std::endl;
	
	Stress_ball test3(Stress_ball_colors::red, Stress_ball_sizes::small);
	std::cout << "Testing for a red,small stressball." << std::endl;
	std::cout << test3 << std::endl;
	
	Stress_ball test4(Stress_ball_colors::yellow, Stress_ball_sizes::large);
	std::cout << "Testing for a yellow,large stressball." << std::endl;
	std::cout << test4 << std::endl;
	
	Stress_ball arr[2] = {test1, test2};
	Stress_ball a[2]={test3,test4};
	
	Collection c();
	Collection c2(2);
	
	cout << c << endl;
	cout<< c2 << endl;
	cout << "Now swapping" << endl;
	swap(c,c2);
	cout << c << endl;
	cout<< c2 << endl;
	
	return 0;
}