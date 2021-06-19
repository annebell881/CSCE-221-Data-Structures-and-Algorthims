#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include "MPQ.h"
//we need the standard dictionary and a vector for sorting
#include <iostream>
#include <vector>

struct EmptyMPQ: public std::runtime_error{
	explicit EmptyMPQ(char const *msg = nullptr):runtime_error(msg){}
};
/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ: MPQ<T> {
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::list
   // For remove_min() and min() throw exception if the SortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
   //Use the standard sorted list to create a list for the Minimum Priority Queue
   // Create a private member which would be the created list
   private:
	std::list<T> newList;
   
   public:
	T remove_min();
	T min();
	bool is_empty();
	void insert(const T& value);
};

template <typename T>
bool SortedMPQ<T>::is_empty(){
	if (newList.size() == 0){
		return true;
	}
	return false;
}

template <typename T>
T SortedMPQ<T>::remove_min(){
	if(is_empty()){
		//throw an expection
		throw EmptyMPQ("MPQ is empty");
	}
	//The list should be sorted so that you can just pop off the front
	T minimum = newList.front();
	newList.pop_front();
	return minimum;
}

template <typename T>
T SortedMPQ<T>::min(){
	if(is_empty()){
		//throw an expection
		throw EmptyMPQ("MPQ is empty");
	}
	// return the first value as it is the min
	return newList.front();
}

template <typename T>
void SortedMPQ<T>::insert(const T& value){
	//if this is empty then the value is the first one
	if(newList.size() == 0){
		newList.push_front(value);
		//end the function
		return;
	}
	//create a transversal list if otherwise
	typename std::list<T>::iterator it;
	for (it = newList.begin(); it != newList.end(); it++){
		if (value < *it){
			newList.insert(it, value);
			//needs the return value to end the loop after the value is inserted and not add again
			return;
		}
	}
	newList.push_back(value);
	return;

}

#endif