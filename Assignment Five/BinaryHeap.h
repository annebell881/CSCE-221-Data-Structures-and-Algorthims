#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>

struct EmptyBH: public std::runtime_error{
	explicit EmptyBH(char const *msg = nullptr):runtime_error(msg){}
};

/*
 * Binary Heap class
 */
template <typename T>
class BinaryHeap {
    public:
        //Implement the below 4 methods. Please note these methods are not from MPQ.h
        //BinaryHeap class does not inherit MPQ class 
        //Implement BinaryHeap insert operation
        //Also implement upheap and downheap operations (functions provided below) and call them from wherever necessary
        void insert(const T& data);
        // Return true if BinaryHeap is empty otherwise false
        bool is_empty();
        // Return minimum element in the BinaryHeap
        T min();
        // Remove minimum element in the BinaryHeap and return it
        T remove_min();
    private:
        //
        std::vector<T> elements;
        int size = 0;
        //Implement down heap operation
        void down_heap(int i);
        //Implement up heap operation
        void up_heap(int i);

        //Pre-implemented helper functions
        //swaps two elements at positions a and b
        void swap(int a, int b) { T c(elements[a]); elements[a] = elements[b]; elements[b] = c;}
        //Binary tree (Complete Binary tree) can be represented in vector form and hence, stored in a vector. 
        //Returns the right child index of current index
        int right_child(int i) {return 2*i + 2;}
        //Returns the left child index of current index
        int left_child(int i) {return 2*i + 1;}
        //Returns the parent index of current index
        int parent(int i) {return floor((i-1)/2);}
        //Checks if current index is an internal node
        bool is_internal(int i) {return left_child(i) < size || right_child(i) < size;}
        //Checks if current index is a leaf
        bool is_leaf(int i) {return left_child(i) >= size && right_child(i) >= size;}
};

/*
 * Restores the binary heap property starting from a node that is smaller than its parent
 */
template <typename T>
void BinaryHeap<T>::up_heap(int i){
    int parent_index = parent(i);
    /*
     * Can be computed iteratively or recursively
     */
	while (elements[i] < elements[parent(i)] && 0 < i){
		swap(i, parent(i));
		i = parent(i);
	}
}

/*
 * Restores the binary heap property starting from an node that is larger than its children
 */
template <typename T>
void BinaryHeap<T>::down_heap(int i){
    int right_index = right_child(i);
    int left_index = left_child(i);
    /*
     * Can be computed iteratively or recursively
     */
	int index = i;
	if(right_index < size && elements[right_index] < elements[index]){
		index = right_index;
	}
	if(left_index < size && elements[left_index] < elements[index]){
		index = left_index;
	}
	if (i != index){
		swap(index, i);
		down_heap(index);
	}
}

template <typename T>
void BinaryHeap<T>::insert(const T& data){
	size++;
	int newSize = size -1;
	elements.push_back(data);
	up_heap(newSize);
}

template <typename T>
bool BinaryHeap<T>::is_empty(){
	if(size == 0){
		return true;
	}
	return false;
}

template <typename T>
T BinaryHeap<T>::min(){
	if(is_empty()){
		throw EmptyBH("Empty binary heap.");
	}
	else{
		T val = elements[0];
		return val;
	}
}

template <typename T>
T BinaryHeap<T>::remove_min(){
	if(is_empty()){
		throw EmptyBH("Empty binary heap.");
	}
	else{
		T val = elements[0];
		int newSize = --size;
		elements[0] = elements[newSize];
		elements.erase(--elements.end());
		down_heap(0);
		return val;
	}
}
#endif