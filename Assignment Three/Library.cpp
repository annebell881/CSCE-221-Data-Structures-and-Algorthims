#include "Library.h"
#include "TemplatedDLList.h"
#include "Record.h"
#include <fstream>

std::vector<Record> Library::search(std::string title){
	//create a vector to add the records to 
	vector<Record> records;
	//iterate through the linked list
	for(unsigned i = 0; i < book_db.size(); i++){
		DLListNode<Record> *itterator = book_db[i].first_node();
		while(itterator != book_db[i].after_last_node()){
			//if the title matches the title name then add to the base
			if(itterator->obj.get_title() == title){
				records.push_back(itterator->obj);
			}
			itterator = itterator->next;
		}
	}
	//return the records 
	return records;
}

bool Library::add_record(Record book){
	string title = book.get_title();
	//take the first letter of the titles name and create a switch to create an index
	int index = -1;
	char firstLetter = title.at(0);
	switch (firstLetter){
		case 'A' : 
			index = 0;
			break;
		case 'B' : 
			index = 1;
			break;
		case 'C' : 
			index = 2;
			break;
		case 'D' : 
			index = 3;
			break;
		case 'E' : 
			index = 4;
			break;
		case 'F' : 
			index = 5;
			break;
		case 'G' : 
			index = 6;
			break;
		case 'H' : 
			index = 7;
			break;
		case 'I' : 
			index = 8;
			break;
		case 'J' : 
			index = 9;
			break;
		case 'K' : 
			index = 10;
			break;
		case 'L' : 
			index = 11;
			break;
		case 'M' : 
			index = 12;
			break;
		case 'N' : 
			index = 13;
			break;
		case 'O' : 
			index = 14;
			break;
		case 'P' : 
			index = 15;
			break;
		case 'Q' : 
			index = 16;
			break;
		case 'R' : 
			index = 17;
			break;
		case 'S' : 
			index = 18;
			break;
		case 'T' : 
			index = 19;
			break;
		case 'U' : 
			index = 20;
			break;
		case 'V' : 
			index = 21;
			break;
		case 'W' : 
			index = 22;
			break;
		case 'X' : 
			index = 23;
			break;
		case 'Y' : 
			index = 24;
			break;
		case 'Z' : 
			index = 25;
			break;
	}
	//iterate through this section to find if the record matches any other record
	DLListNode<Record> *itterator = book_db[index].first_node();
	while(itterator != book_db[index].after_last_node()){
	//if the book matches another send back
		if(itterator->obj == book){
			return false;
		}
		itterator = itterator->next;
	}
	//if not then we add it to that section and return true
	book_db[index].insert_last(book);
	return true;	
}

void Library::print_database(){
	//iterate through the linked list and print baby
	for(unsigned i = 0; i < book_db.size(); i++){
		DLListNode<Record> *itterator = book_db[i].first_node();
		while(itterator != book_db[i].after_last_node()){
			
			std::cout << itterator->obj.get_title() << std::endl;
			std::cout << itterator->obj.get_author() << std::endl;
			std::cout << itterator->obj.get_ISBN() << std::endl;
			std::cout << itterator->obj.get_edition() << std::endl;
			std::cout << itterator->obj.get_year()<< std::endl;
			itterator = itterator->next;
		}
	}
}

int Library::import_database(std::string filename){
	//int to return that counts the number in the data base
	int count = 0;
	//open the file add records 
	Record rec;
	ifstream ifs(filename);
	string t;
	string a;
	string i;
	string e;
	string y;
	
	while(getline(ifs,t)){
		rec.set_title(t);

	
		getline(ifs, a);
		rec.set_author(a);
	
		getline(ifs, i);
		rec.set_ISBN(i);

		getline(ifs, y);
		rec.set_year(y);
	
		getline(ifs, e);
		rec.set_edition(e);
		//hahahahaha add record is a bool I am dumb
		if(add_record(rec)){
			count ++;
		}
	}
	return count;
}

char Library::prompt_yes_no(){
	char prompt;
	do{
		cout << "Please type Y for yes or N for no." << endl;
		cin >> prompt;
	}while(prompt != 'Y' && prompt != 'N');
	return prompt;
}

std::string Library::prompt_title(){
	std::string userTitle;
	cout << "Please enter a title:" << endl;
	cin >> userTitle;
	
	return userTitle;
}

std::string Library::prompt_string(std::string prompt){
	std::string userInput;
	cout << prompt << endl;
	cin >> userInput;
	
	return userInput;
}

Record Library::prompt_record(){
	Record user;
	user.set_title(prompt_title());
	user.set_author(prompt_string("Please enter the author: "));
	user.set_ISBN(prompt_string("Please enter the ISBN: "));
	user.set_edition(prompt_string("Please enter the edition: "));
	user.set_year(prompt_string("Please enter the year: "));
	return user;
}

int Library::prompt_menu(std::vector<std::string> vector){
	int userInput;
	
	for(unsigned i = 0; i < vector.size(); i++){
		cout << i+1 << ". "<< vector[i] << endl;
	}
	cout << "Please select an option: " << endl;
	cin >> userInput;
	
	return userInput-1;
	
}

void Library::remove_record(Record book){
	//create a pointer and traverse through the list to find a book equal to remove
	for(unsigned i = 0; i < book_db.size(); i++){
		DLListNode<Record> *itterator = book_db[i].first_node();
		while(itterator != book_db[i].after_last_node()){
			//if the object matches the book remove it 
			if(itterator->obj == book){
					remove_node(itterator);
			}
			itterator = itterator->next;
		}
	}
	
}

int Library::export_database(std::string filename){
	int count = 0;
	
	return count;
}