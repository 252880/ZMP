#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Read.hh"
#include "Set4LibInterfaces.hh"

#define LINE_SIZE 500

using namespace std;

int main()
{

  Read preprocRead;
  Set4LibInterfaces handle;
  std::istringstream stream;
  preprocRead.execPreprocesor("opis_dzialan.cmd",stream);

  handle.init();
  handle.execute(stream);

  return 0;
}
