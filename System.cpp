#include "System.h"
#include<iostream>
#include<string>
using namespace std;

int System::gettime() const {
	return (htime * 100) + mtime;
}	

string System::getdest() const {
	return dest;
}

int System::getidnum() const {
	return idnum;
}

void System::settime(int timeh, int timem) {
	htime = timeh;
	mtime = timem;
}

void System::setdest(string destination) {
	dest = destination;
}

void System::setidnum(int id)
{
	idnum = id;
}

System::System(int idnumber, string destination, int timeh, int timem) {

	idnum = idnumber;
	dest = destination;
	htime = timeh;
	mtime = timem;
}

System::System() {
	idnum = 0;
	dest = "default";
	htime = 0;
	mtime = 0;
}

int System::gettimeh() const
{
	return htime;
}

int System::gettimem() const
{
	return mtime;
}
