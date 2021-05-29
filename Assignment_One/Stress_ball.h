#ifndef STRESS_BALL_H
#define STRESS_BALL_H

#include <iostream>
#include <ostream>

//creates an enum stress ball that holds the colors and the possible sizes
enum class Stress_ball_colors { red, blue, yellow, green};
enum class Stress_ball_sizes {small, medium, large};

//creating a class for the stress ball itself 
class Stress_ball{
	private:
	//these are set to private so they can only be accessed within the class there will be functions
	//that can retrieve them outside of the class that will be public
		Stress_ball_colors color;
		Stress_ball_sizes size;
		
	public:
		//constructor one intializes it with random variables, two takes in variables
		Stress_ball();
		Stress_ball(Stress_ball_colors c, Stress_ball_sizes s);
		
		//create access to the color and size from outside of this class
		//They should remain constant 
		Stress_ball_colors get_color() const{
			return color;
		}
		Stress_ball_sizes get_size() const{
			return size;
		}
		
		//creating a bool function that checks the stress ball to see if it is the same as 
		//the one being presented.
		//creating a bool function that checks the stress ball to see if it is the same as 
		//the one being presented.
		bool operator ==(const Stress_ball& sb){
			if(this->get_color() == sb.get_color()){
				if(this->get_size() == sb.get_size()){
					return true;
				}
			}
			return false;	
		}
};

std::ostream& operator << (std::ostream& o, const Stress_ball& sb){
	o << '(';
	//an enum "prints out a desginated number as a representive of the "color" or size
	// a switch or if-else statments can be used to create them as a word
	//switches just make the code look cleaner 
	switch (sb.get_color()){
		case Stress_ball_colors::red :
			o << "red, ";
			break;
		case Stress_ball_colors::blue :
			o << "blue, ";
			break;
		case Stress_ball_colors::yellow :
			o << "yellow, ";
			break;
		case Stress_ball_colors::green :
			o << "green, ";
			break;
	}
	//Stress_ball_sizes {small, medium, large};
	switch (sb.get_size()){
		case Stress_ball_sizes::small :
			o << "small)" << std::endl;
			break;
		case Stress_ball_sizes::medium :
			o << "medium)" << std::endl;
			break;
		case Stress_ball_sizes::large :
			o << "large)" << std::endl;
			break;
	}
	
	return o;	
}



#endif