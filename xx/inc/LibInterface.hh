#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH
#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"
#include "dlfcn.h"

class LibInterface {

  void* LibHandler;
  Interp4Command *(*pCreateCmd)(void);
  std::string pCmdName;
  
  
public:

  
  ~LibInterface();

  Interp4Command* CreateCmd();
  std::string GetCmdName();
  bool init(std::string path);
  

};


#endif
