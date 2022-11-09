#include "LibInterface.hh"
#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"


using namespace std;

bool LibInterface::init(string path)
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
  pCmdName = GetCmdName();
  
  
}


Interp4Command *LibInterface::CreateCmd()
{
  return pCreateCmd();
}

string LibInterface ::_GetCmdName(){

  return pCmdName;
}
  
LibInterface::~LibInterface()
{
  dlclose(LibHandler);
}


