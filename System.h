#pragma once
#include<iostream>
#include<string>

class System
{
protected:
	int htime, mtime, idnum; //htime to record the hour digits. mtime ti record the minute digits
	std::string dest; //dest to record destination as string
public:
	virtual ~System() = default;
	virtual std::string getletter() const = 0; //virtual function
	int gettime() const; // function to return the time in 24hr clock //new changes
	std::string getdest() const; // function to return the destination
	int gettimeh() const;
	int gettimem() const;
	int getidnum() const; //funciton to get idnum
	void settime(int timeh, int timem); //function to set time 
	void setdest(std::string destination); //function to set destination
	void setidnum(int newid); //function to set idnum
	System(int idnumber, std::string destination, int timeh, int timem); //System constructor 
	System();

};

