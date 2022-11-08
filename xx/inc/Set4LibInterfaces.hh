#pragma once

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include <vector>
#include <memory>


class Set4LibInterfaces
{
private:
  std::map<std::string, LibInterface *> libraries;
  
public:
  bool init();  
  bool execute(std::istringstream &stream);
};
