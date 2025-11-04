#pragma once
#include"Cargo.h"
#include"Freight.h"
#include<vector>
#include<string>
#include<ostream>

class Schedule 
{
private: 
    int schid;
    const Cargo* cargosch;
    const Freight* freightsch;

public:
    const Cargo* getcargosch() const; //elements are idnum(1) , dest(2), timeh(3), timem(4)
    const Freight* getfreightsch() const ;    //elements are idnum(1) , dest(2), timeh(3), timem(4)
    bool match() const; //match current cargosch and freightsch
    Schedule(int sid , const Freight& f,const Cargo& c);
    Schedule();
    int getid() const;
    friend std::ostream& operator<<(std::ostream& out, const Schedule& list);

    //serialise
    static Schedule fromString(const std::string& line);
    static std::string toString(const Schedule& s);
};

