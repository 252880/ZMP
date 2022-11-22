#pragma once


#include <cstdio>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include <vector>
#include <memory>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Configuration.hh"
#include "xmlinterp.hh"


#define LINE_SIZE 500


class Set4LibInterfaces
{
private:
  std::map<std::string, std::shared_ptr<LibInterface>> libraries;
  
public:
 
  bool init(std::vector<std::string> libraries_vector); 
  bool execPreprocesor(const char * NazwaPliku,std::istringstream &IStrm4Cmds);
  bool ReadFile(const char* sFileName, Configuration &rConfig);
  bool execute(std::istringstream &stream);
};
