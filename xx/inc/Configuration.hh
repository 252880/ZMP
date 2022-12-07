#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "MobileObjConfig.hh"
#include "Vector3D.hh"
#include <string>
#include <vector>

class Configuration {
  
public:
  std::vector<std::string> lib_vector;
 
  std::vector<MobileObjConfig> obj_vector;

 
};

#endif
