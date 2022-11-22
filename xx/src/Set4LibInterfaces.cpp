#include "Set4LibInterfaces.hh"

using namespace std;


bool Set4LibInterfaces::init(std::vector<std::string> libraries_vector)
{
    for (int i = 0; i < libraries_vector.size(); i++)
    {
        std::shared_ptr<LibInterface> tmp_library = std::make_shared<LibInterface>();
        tmp_library->init("libs/" + libraries_vector[i]);
        std::string command_name = libraries_vector[i].substr(10, libraries_vector[i].length() - 13);
        std::cout << command_name << std::endl;

        libraries.insert(std::make_pair(command_name, tmp_library));
    }

bool Set4LibInterfaces::execPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds)
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += NazwaPliku;
  FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc) return false;

  while (fgets(Line, LINE_SIZE, pProc))  OTmpStrm << Line;
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

bool Set4LibInterfaces::ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            xercesc::XMLPlatformUtils::Initialize();
   }
   catch (const xercesc::XMLException& toCatch) {
            char* message = xercesc::XMLString::transcode(toCatch.getMessage());
            std::cerr << "Error during initialization! :\n";
            std::cerr << "Exception message is: \n"
                 << message << "\n";
            xercesc::XMLString::release(&message);
            return 1;
   }

   xercesc::SAX2XMLReader* pParser = xercesc::XMLReaderFactory::createXMLReader();

   pParser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(xercesc::XMLUni::fgXercesDynamic, false);
   pParser->setFeature(xercesc::XMLUni::fgXercesSchema, true);
   pParser->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);

   xercesc::DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << std::endl;
       return false;
     }
     pParser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const xercesc::XMLException& Exception) {
            char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
            std::cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            xercesc::XMLString::release(&sMessage);
            return false;
   }
   catch (const xercesc::SAXParseException& Exception) {
            char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            std::cerr << "Blad! " << std::endl
                 << "    Plik:  " << sSystemId << std::endl
                 << "   Linia: " << Exception.getLineNumber() << std::endl
                 << " Kolumna: " << Exception.getColumnNumber() << std::endl
                 << " Informacja: " << sMessage 
                 << std::endl;

            xercesc::XMLString::release(&sMessage);
            xercesc::XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

bool Set4LibInterfaces::execute(istringstream &stream)
{
  string str;
  LibInterface *Lib_;
  Interp4Command *cmd;

  while (stream >> str)
    {
      map<string, LibInterface *>::iterator it = Lib.find(str);
      if (it == Lib.end())
	{
	  cout << "Nie znaleziono wtyczki o nazwie: " << str << endl;
	  return 1;
	}

      Lib_ = it->second;
      cmd = Lib_->CreateCmd();
      cmd->ReadParams(stream);
      cout << "Wykonaj:" << endl;
      cmd->PrintCmd();
      delete cmd;
    }

  return 0;
}
