#include "Collection.h"
#include "Stress_ball.h"
#include <string>


Collection::Collection(): array(nullptr), size(0), capacity(0){}
Collection::Collection(int cap):array(new Stress_ball[cap]), size(0), capacity(cap){}
//array needs an array if size cap so dynamically allocate the collection array to be size capacity
Collection::Collection(const Collection& c):array(new Stress_ball[c.capacity]), size(c.size), capacity(c.capacity){
	//copy the collection exactly, size, cap and array; should be initalized up top
	//size = c.size;
	//capacity = c.capacity;
	//array = new Stress_ball[capacity];
	//loop through the collection and copy the collection.
	for(int i = 0; i < size; i++){
		array[i] = c.array[i];
	}
}

Collection& Collection:: operator=(const Collection& c){
	if (this != &c){
		//error for != find a way around or create that opperator
		//delete the array if existant, we want to fully copy collection 
		if (array != nullptr){
			delete []array;
		}
		size = c.size;
		capacity = c.capacity;
		array = new Stress_ball[capacity];
		for(int i = 0; i < size; i++){
			array[i] = c.array[i];
		}
	}
	return *this;
	
}

Collection :: Collection(Collection&& c):array(c.array), size(c.size),capacity(c.capacity){
	c.array = nullptr;
	c.size = 0;
	c.capacity = 0;
}

Collection& Collection::operator=(Collection&& c){
	//same as other
	if (this != &c){
		//error for != find a way around or create that opperator
		//delete the array if existant, we want to fully copy collection 
		if (array != nullptr){
			delete []array;
		}
		size = c.size;
		capacity = c.capacity;
		//jk this shouldnt be new it should just be the same
		array = c.array;
	}
		//set old numbers to nothing
	c.size = 0;
	c.capacity = 0; 
	c.array = nullptr;
	return *this;
}

void Collection:: make_empty(){
	if (array != nullptr){
		delete []array;
		size = 0;
		capacity = 0;
		array = nullptr;
	}
}

Collection:: ~Collection(){
	//if an array exists delete it
	/*if (array != nullptr){
		delete []array;
		size = 0;
		capacity = 0;
		array = nullptr;
	}*/
	//make empty is basically a destructor..... should have started with that
	make_empty();
}

void Collection::resize(){
	//check if cap = 0; if so resize to one
	//not resizing the capacity but rather the size....
	int double_cap;
	
	if (capacity == 0){
	    double_cap = 1;
	}
	else{
		double_cap = capacity * 2;
    }
  //create a new array to hold contents of old array plus doubled 
    Stress_ball* resizedArray = new Stress_ball[double_cap];
  //loop through the array to copy into the new one; make sure to update the tracker
  //if array = nullptr skip step
	if(array != nullptr){
		for (int i = 0; i < size; i++){
			resizedArray[i] = array[i];
		}
	}
  //set size equal to the new one and delete the old array to avoid memory leaks?
  //right now is only doing the one cap from a zero cap
    capacity = double_cap;
    delete array;
    array = resizedArray;
}


void Collection::insert_item(const Stress_ball& sb){
	if (size == capacity){
		resize();
	}
	array[size] = sb;
	size ++;
}

bool Collection::contains(const Stress_ball& sb) const{
	//loop through the collection, to find if there is a matching stress ball
	for(int i = 0; i < size; i++){
		if(array[i] == sb){
			return true;
		}
	}
	return false;
}

bool Collection::is_empty() const{
	if (size == 0){
		return true;
	}
	return false;
}

Stress_ball Collection::remove_any_item(){
	if (size == 0){
		throw "No Collection exists";
	}
	//use rand to pick a random index thus the "no control"
	int random = std::rand()%size;
	Stress_ball sB = array[random];
	//move the other elements over to fill in the hole of this stressball
	for (int i = random + 1; i < size; i++){
		array[i - 1] = array[i];
	}
	size --;
	return sB;
}

void Collection::remove_this_item(const Stress_ball& sb){
	//match remove random but with an actual index
	
	if (size == 0){
		throw "No Collection exists";
	}
	
	int index = -1; // that why if not found we simply dont delete a value.
	for (int i = 0; i < size; i++){
		if (array[i] == sb){
			index = i;
			break;
		}
	}
	//move the other elements over to fill in the hole of this stressball
	if(index != -1){
		for (int j = index + 1; j < size; j++){
			array[j - 1] = array[j];
		}
		size --;
	}
}

int Collection::total_items() const{
	//return the size cause size is total in the collection.
	return size;
}
	
int Collection::total_items(Stress_ball_sizes s) const{
//loop through and find the same size ball to return that count
	int count = 0;
	for (int i = 0; i < size; i++){
		if (array[i].get_size() == s){
			count += 1;
		}
	}
	return count;
}	

int Collection::total_items(Stress_ball_colors c) const{
	//same as count size but for colors;
	int count = 0;
	for (int i = 0; i < size; i++){
		if (array[i].get_color() == c){
			count += 1;
		}
	}
	return count;
}

void Collection::print_items() const{
	for (int i = 0; i < size; i++){
		std::cout << array[i] << std::endl;
	}
}

Stress_ball& Collection::operator[](int i){
	return array[i];
}

const Stress_ball& Collection::operator[](int i) const{
	return array[i];
}

std::ostream& operator<<(std::ostream& os, const Collection& c){
	
	//an enum "prints out a desginated number as a representive of the "color" or size
	// a switch or if-else statments can be used to create them as a word
	//switches just make the code look cleaner
	//in a loop to print the whole collection;
	for(int i = 0; i < c.total_items(); i++){
		switch (c[i].get_color()){
			case Stress_ball_colors::red :
				os << "(red, ";
				break;
			case Stress_ball_colors::blue :
				os << "(blue, ";
				break;
			case Stress_ball_colors::yellow :
				os << "(yellow, ";
				break;
			case Stress_ball_colors::green :
				os << "(green, ";
				break;
		}
		//Stress_ball_sizes {small, medium, large};
		switch (c[i].get_size()){
			case Stress_ball_sizes::small :
				os << "small)" << std::endl;
				break;
			case Stress_ball_sizes::medium :
				os << "medium)" << std::endl;
				break;
			case Stress_ball_sizes::large :
				os << "large)" << std::endl;
				break;
		}

	}
	return os;
}
std:: istream& operator>>(istream& is, Collection& c){
	std::string color;
	std::string size;
	
}

Collection make_union(const Collection& c1, const Collection& c2){
	int unionSize = c1.total_items() + c2.total_items();	
	//copy c1 into c3 which will be the new collection
	Collection c3 = Collection(unionSize);
	
	for(int i = 0; i < unionSize; i++){
		if(i < c1.total_items()){
			c3[i] = c1[i];
		}
		else{
			
			int tempsize = i - c1.total_items();
			c3[i] = c2[tempsize];
		}
	}
	return c3;
}
void swap(Collection& c1, Collection& c2){
	int temp_size = c1.total_items();
	Collection temp = Collection(temp_size);
	temp = c1;
	c1= c2;
	c2 = temp;
}

void sort_by_size(Collection& c, Sort_choice sort){
	//Then elements will be sorted with respect to their size in array (we do not sort them with respect to color)
	switch (sort){
		case Sort_choice::bubble_sort:
			for (int i = 0; i < c.total_items(); i++){
				for (int j = 0; j < (c.total_items() - i - 1); j++){
					if(c[j].get_size() < c[j + 1].get_size()){
						Stress_ball temp = c[j + 1];
						c[j + 1] = c[j];
						c[j] = temp;
					}
				}
			}
			break;
			
		case Sort_choice::insertion_sort:
			for (int i = 1; i < c.total_items(); i++){
				Stress_ball follow = c[i];
				int j = i - 1;
				
				while(c[j].get_size() > follow.get_size() && j >= 0){
					c[j+1] = c[j];
					j = j -1;
				}
				c[j+1] = follow;
			}	
			break;
		case Sort_choice::selection_sort:
			int min = 0;
			for (int i = 0; i < (c.total_items() - 1); i++){
				min = i;
				for(int j = i+1; j < c.total_items(); j++){
					if (c[j].get_size() < c[min].get_size()){
						min = j;
					}
					Stress_ball temp = c[min];
					c[min] = c[j];
					c[j] = temp;
				}

			}
			break;
	}
}

	