#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Set4LibInterfaces.hh"



using namespace std;

int main()
{

  Set4LibInterfaces Set;
  std::istringstream stream;


  Set.execPreprocesor("wywolanie.cmd",stream);
  Set.init();
  Set.execute(stream);

  return 0;
}
