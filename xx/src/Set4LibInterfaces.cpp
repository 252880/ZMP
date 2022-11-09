#include "Set4LibInterfaces.hh"

using namespace std;

bool Set4LibInterfaces::init()
{
  rt->init("libs/libInterp4Rotate.so");
  ps->init("libs/libInterp4Pause.so");
  st->init("libs/libInterp4Set.so");
  mv->init("libs/libInterp4Move.so");

  Lib.insert(make_pair("Rotate", rt));
  Lib.insert(make_pair("Pause", ps));
  Lib.insert(make_pair("Set", st));
  Lib.insert(make_pair("Move", mv));

  return 0;
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
