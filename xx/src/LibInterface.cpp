#include "LibInterface.hh"
#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"
0;10;1c

using namespace std;

bool LibInterface::init(std::string path)
{
  LibHandler = dlopen(path.c_str(),RTLD_LAZY);


  if (!LibHandler) {
    cerr << "!!! Brak biblioteki: " << path << endl;
    
  }

  const char* (*GetCmdName)(void);  
  void* pFun;

  
  pFun = dlsym(LibHandler,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
   
  }

  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  pFun = dlsym(LibHandler,"GetCmdName");
  if(!pFun){
    cerr << "!!! Nie znaleziono funkcji GetCmdName" << endl;
  
  }
  

  GetCmdName = reinterpret_cast<const char* (*)(void)>(pFun);

  CmdName = GetCmdName();
  
  
}


Interp4Command *LibInterface::CreateCmd()
{
  return pCreateCmd();
}

string LibInterface ::GetCmdName(){

  return CmdName;
}
  
LibInterface::~LibInterface()
{
  dlclose(LibHandler);
}


