// implementation of the DLList class

#include "DLList.h"

//exceptions need to be thrown like how they are thrown in labs
#include <stdexcept>
//structure of the execptions
struct EmptyDLList: public std::runtime_error{
	explicit EmptyDLList(char const *msg = nullptr):runtime_error(msg){}
};

struct InvaildOperation : public std::runtime_error{
	explicit InvaildOperation(char const *msg = nullptr):runtime_error(msg){}
};

//constructor needs to be defined at the top i believe 
//header and trailer zero?
DLList::DLList(): header(0), trailer(0){
	header.next = &trailer;
	trailer.prev = &header;
	//this should link them together
}

DLListNode* DLList::first_node() const{
	return header.next;
}

const DLListNode* DLList::after_last_node() const{
	// return the pointer to the trailer
	return &trailer;
	
}

bool DLList::is_empty() const{
	//if the header returns empty then return the true, else there is anything then return false
	if(header.next == &trailer){
		return true;
	}
	return false;
}

int DLList::first() const{
	if (is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	return header.next->obj;
}

int DLList::last() const{

	if (is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	return trailer.prev->obj;
}

void DLList::insert_first(int obj){
	//create a new node with the object being object
	//code is straight from the slides
	DLListNode *newNode = new DLListNode(obj, &header, header.next);
	header.next->prev = newNode;
	header.next = newNode;
}

void DLList::insert_last(int obj){
	//straight from slides
	DLListNode *newNode = new DLListNode(obj, trailer.prev,&trailer);
	trailer.prev->next = newNode;
	trailer.prev = newNode;
}

int DLList::remove_first(){
	//copy straight from the slides
	if (is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	DLListNode *node = header.next;
	node->next->prev = &header;
	header.next = node->next;
	int obj = node->obj;
	delete node;
	return obj;
}

int DLList::remove_last(){
	//coppied from slides
	if (is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	DLListNode *node = trailer.prev;
	node->prev->next = &trailer;
	trailer.prev = node->prev;
	int obj = node->obj;
	delete node;
	return obj;
}

DLList:: ~DLList(){
	DLListNode *prev_node, *node = header.next;
	while (node != &trailer) {
		prev_node = node;
		node = node->next;
		delete prev_node;
	}
	header.next = &trailer;
	trailer.prev = &header;
}

void DLList::insert_after(DLListNode &p, int obj){
	//check if the node we insert the new one after is a nullptr
	if(is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	//alocate a new node
	DLListNode *newNode = new DLListNode(obj, &p, p.next);
	//want the next of p to be the next of the new node to not lose the connection
	p.next->prev = newNode; //look into why this is an '->' instead of '.'
	//place new node in the list
	p.next = newNode;
}

void DLList::insert_before(DLListNode &p, int obj){
	//check if the node we insert the new one after is a nullptr
	if(p.prev == nullptr){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	//alocate a new node
	DLListNode *newNode = new DLListNode(obj, p.prev, &p);
	//want the next of p to be the next of the new node to not lose the connection
	 p.prev-> next = newNode;
	//place new node in the list
	p.prev = newNode;
	//should just be a backwards version of the one above
}

int DLList::remove_after(DLListNode &p){
	//create an int to hold the object of p
	if(is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	if( &p == &trailer){
		throw InvaildOperation("Cannot remove after trailer");
	}
	//remove p, get p next to make sure it doesnt just get lost, keep and return the object
	DLListNode* temp = p.next;
	temp->next->prev = &p;
	p.next = temp->next;
	int obj = temp->obj;
	delete temp;
	return obj;
	
}

int DLList::remove_before(DLListNode &p){
	//same as above just backwards and with header
	//create an int to hold the object of p
	if(is_empty()){
		throw EmptyDLList("Empty Doubly Linked List");
	}
	if( &p == &header){
		throw InvaildOperation("Cannot before remove header");
	}
	//remove p, get p next to make sure it doesnt just get lost, keep and return the object
	DLListNode* temp = p.prev;
	temp->prev->next = &p;
	p.prev = temp->prev;
	int objP = temp->obj;
	delete temp;
	return objP;
}

DLList::DLList(const DLList& dll):header(dll.header),trailer(dll.trailer){
	//goal is to match everything to everything in dll
	header.next = &trailer;
	trailer.prev = &header;
	
	//loop through and add each node in
	DLListNode* tempNode = dll.first_node();
	while(tempNode != dll.after_last_node()){
		insert_last(tempNode->obj);
		tempNode = tempNode->next;
	}
}

DLList& DLList::operator=(const DLList& dll){
	//follow the steps of any copy previous opperator
	//check if it is that 
	if(this != &dll){
		if(!this->is_empty()){
			DLListNode* prevNode = header.next;
			DLListNode* temp = header.next;
			//straight copy
			while(temp != &trailer){
				prevNode = temp;
				temp = temp->next;
				delete prevNode;
			}
		}
		header.next = &trailer;
		trailer.prev = &header;
		//new node to copy old one 
		
		DLListNode* tempNode = dll.first_node();
		while(tempNode != dll.after_last_node()){
			insert_last(tempNode->obj);
			tempNode = tempNode->next;
		}
	}
	return *this;
}

DLList::DLList(DLList&& dll){
	//basically a swap function
	header.next = dll.header.next;
	trailer.prev = dll.trailer.prev;
	
	dll.header.next->prev = &header;
	trailer.prev->next = &trailer;
	
	dll.header.next = &dll.trailer;
	dll.trailer.prev = &dll.header;
}

DLList& DLList::operator=(DLList&& dll){
	//reminds me of the copy with a few changes
		if(this != &dll){
		if(!this->is_empty()){
			DLListNode* prevNode = header.next;
			DLListNode* temp = header.next;
			//straight copy
			while(temp != &trailer){
				prevNode = temp;
				temp = temp->next;
				delete prevNode;
			}
		}
		header.next = &trailer;
		trailer.prev = &header;
		//in place of the copy simply do the move opperation
		header.next = dll.header.next;
		trailer.prev = dll.trailer.prev;
	
		dll.header.next->prev = &header;
		trailer.prev->next = &trailer;
	
		dll.header.next = &dll.trailer;
		dll.trailer.prev = &dll.header;
		
	}
	return *this;
}

ostream& operator<<(ostream& out, const DLList& dll){
	//if stack is empty throw
	if (dll.is_empty()){
		throw EmptyDLList("Cannot have an empty Double linked list");
	}
	DLListNode* temp = dll.first_node();
	//loop though
	while(temp != dll.after_last_node()){
		out << temp->obj << ", ";
		temp = temp ->next;
	}
	return out;
}