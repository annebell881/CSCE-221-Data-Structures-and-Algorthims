// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time  

#include <iostream>
#include <vector>

using namespace std;

int comparisons = 0;

ostream& operator<<(ostream& out, vector<int>& v)
{
  // overload the output operator to display elements of v
  // to do so display the elements of the vector
  for (unsigned int i = 0; i < v.size(); i++){
	  out << v[i] << " ,";
  }
  return out;
}

void sort_heaviest(vector<int>& v){
  //reset compasrisions every time or it wont if function continutes to go
  comparisons = 0;
  int heaviest;
  
  // implement the sorting algorithm based on video
  for (unsigned int i = 0; i < (v.size()-1); i++){
	  heaviest = v[i];
	  for (unsigned int j = i + 1; j < v.size(); j++){
		  //check if j is heavier than i, if so swap them
		  if (v[heaviest] < v[j]){
			  heaviest = v[j];
			  comparisons += 1;
	  
			}		
		}
		int temp = v[heaviest];
		v[heaviest] = v[i];
		v[i] = temp;
	}
 
}

int main()
{
 
  cout << "//////Test 2 for vector v ///////////////////////////////"<< endl;
  vector<int> v{10,9,8,7,6,5,4,3,2,1};

  cout << "initial vector v:\n";
  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << endl;
  // call the sorting function for vector v 
  cout << "# of comparisons to sort v: " << comparisons << endl << endl;
  cout << "vector v after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << endl;
  
  cout << "//////Test 2 for vector v1 ///////////////////////////////"<< endl;

  vector<int> v1{1,2,3,4,5,6,7,8,9,10};
  cout << "initial vector v1:\n";
  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << endl;
   // call the sorting function for vector v2 
  cout << "# of comparisons to sort v1: " << comparisons << endl << endl;
  cout << "vector v1 after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << endl;
    
}
