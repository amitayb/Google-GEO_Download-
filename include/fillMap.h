#ifndef FILLMAP_H
#define FILLMAP_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace std;
class fillMap
{
    public:
        //Answer Format
struct structAnswer{

    string country;
    string regionState;
    string city;
    string postalCode;
    string answerCode;
    string answerName;


};
struct location {
    string name;
    string fullName;
    string parents;
    string code;
    string parentCode;
    string type;
    structAnswer answer;

};
        fillMap();
        virtual ~fillMap();
        unordered_map<string,location> parseCSV(ifstream& file);
        structAnswer getDataAlgorith (string& id,unordered_map<string,location>& funcMap);
    protected:
    private:
        //Row Format

};

#endif // FILLMAP_H
