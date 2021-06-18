#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

using std::string;

class Record {
private:
    //member variables
	string title;
	string author;
	string ISBN;
	string year;
	string edition;
	
public:
    //accessor/mutator functions
	//"getters and setters"
	//setters
	void set_title(string t);
	void set_author(string a);
	void set_ISBN(string Isbn);
	void set_year(string yr);
	void set_edition(string ed);
	//getters
	string get_title() const;
	string get_author() const;
	string get_ISBN() const;
	string get_year() const;
	string get_edition() const;
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif