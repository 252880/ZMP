#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>

#define LINE_SIZE 500

class Read
{
private:
 

public:
  Read(){};
  bool execPreprocesor(const char * NazwaPliku,std::istringstream &IStrm4Cmds);
};
