#include "BSTree.h"

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement 


// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node)
{
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree)
{
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) {
    //Don't copy if the node is nullptr
    if(sourceNode == nullptr)
        return;

    //Change the new node to a copy of sourceNode
    newNode = new Node(sourceNode->value);
    //Copy over the search cost
    newNode->search_time = sourceNode->search_time;

    //Copy left subtree
    if (sourceNode->left != nullptr)
        copy_helper(newNode->left, sourceNode->left);
    //Copy right subtree
    if(sourceNode->right != nullptr)
        copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node* node)
{
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

//helper function is going to make empty to help with the deconstructor
void BSTree::makeEmpty (Node* t){
	if(t != nullptr){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

Node* BSTree::insert_helper(Node* p, int obj, int time){
	//check if p is equal to the right node
	if(p == nullptr){
		p = new Node(obj);
		p->search_time = time;
		if(size == 0){
			root = p;
		}
		size++;
	}
	else if (obj < p->value){
		time++;
		p->left = insert_helper(p->left, obj, time);
	}
	else if (obj > p->value){
		time++;
		p->right = insert_helper(p->right, obj, time);
	}
	return p;
	
}
// copy constructor
BSTree::BSTree(const BSTree& other)
{
	if(other.root == nullptr){
		root = nullptr;
		this->size = 0;
	}
	else{
		copy_helper(this->root, other.root);
		this->size = other.size;
	}
}

// move constructor
BSTree::BSTree(BSTree&& other)
{
	if (this == &other){
		return;
	}
	else if(other.root == nullptr){
			root = nullptr;
			this->size = 0;
	}
	else{
		this->root = other.root;
		this->size = other.size;
		
	}
	other.root = nullptr;
	other.size = 0;
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
	/*For the copy assignment operator, you must also check if you are trying to copy the tree into itself,
	in which case you do nothing,or if there is a tree in the destination and if so, delete it.*/
	//so dont copy if same tree
	if(this != &other){
		makeEmpty(this->root);
		if(other.root == nullptr){
			root = nullptr;
			this->size = 0;
		}
		else{
			copy_helper(this->root, other.root);
			this->size = other.size;
		}
	}
	return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
	//check if the other is the same
	if (this == &other){
		return *this;
	}
	else if(this != &other){
		if(other.root == nullptr){
			root = nullptr;
			this->size = 0;
		}
		else{
			if(this->root != nullptr){
				delete root;
			}
			this->root = other.root;
			this->size = other.size;
		}
	}
	other.root = nullptr;
	other.size =0;
	return *this;
}

// destructor
BSTree::~BSTree()
{
    // Make sure to call delete on every node of the tree
    // You can use a recursive helper function to do this
	makeEmpty(root);
	root = nullptr;
}

Node* BSTree::insert(int obj)
{
    /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
	root = insert_helper(root, obj, 1);
	return search(obj);
}

Node* BSTree::search(int obj)
{
    /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
	Node* temp = root;
	
	while(temp != nullptr){
		if (obj < temp->value){
			temp = temp->left;
		}
		else if(obj > temp->value){
			temp = temp->right;
		}
		else{
			return temp;
		}
	}
	return nullptr;
}

void BSTree::search_time_helper (Node* p, int time){
	if(p != nullptr){
		p->search_time = time;
	}
	if(p->left != nullptr){
		search_time_helper(p->left, time+1);
	}
	if(p->right != nullptr){
		search_time_helper(p->right, time+1);
	}
}

void BSTree::update_search_times()
{
    /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */
	  int time = 1;
	  Node* itterator = root;
	  
	  
	  if(itterator != nullptr){
		  itterator->search_time = time;
	  }
	  if(itterator->left){
		  search_time_helper(itterator->left, time+1);
	  }
	  if(itterator->right){
		  search_time_helper(itterator->right,time+1);
	  }
}
void BSTree::inorder_helper (std::ostream& out, Node* temp){
	if(temp == nullptr){
		//do nothing;
		return;
	}
	inorder_helper(out, temp->left);
	out << temp->value << '[' << temp->search_time << "] ";
	inorder_helper(out, temp->right);
}

void BSTree::inorder(ostream& out)
{
    /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */
	inorder_helper(out, root);
}

void BSTree::print_level_by_level(ostream& out)
{
    /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */
	if (this->root == nullptr){
		return;
	}
	//create a queue for the nodes
	queue<Node*> nodeQueue;
	
	int cur = 1;
	int next = 0;
	//start with the root in the queue
	nodeQueue.push(this->root);
	//new node with a random value that a value wouldnt be so negitive
	Node* print = new Node(-1);
	
	bool check = true;
	
	//create vectors to hold the time and value
	vector<int> pval;
	vector<int> ptime;
	//focus on printing the values
	while(!nodeQueue.empty()){
		Node* temp = nodeQueue.front();
		nodeQueue.pop();
		cur--;
		
		if(temp){
			pval.push_back(temp->value);
			ptime.push_back(temp->search_time);
			
			if(temp->left == nullptr){
				//ends the queue
				nodeQueue.push(print);
			}
			else{
				check = false;
				nodeQueue.push(temp->left);
			}
			//do the same to the right side as the left 
			if(temp->right == nullptr){
				//ends the queue
				nodeQueue.push(print);
			}
			else{
				check = false;
				nodeQueue.push(temp->right);
			}
			next += 2;
		}
		if(cur == 0){
			for(unsigned i = 0; i <pval.size(); i++){
				if(pval.at(i) == -1){
					out << "X ";
				}
				else{
					out << pval.at(i) << '[' << ptime.at(i) << ']';
				}
			}
			out << std::endl;
			
			if(check){
				return;
			}
			
			pval.clear();
			ptime.clear();
			check = true;
			
			cur = next;
			next = 0;
		}
	}
	delete print;
}