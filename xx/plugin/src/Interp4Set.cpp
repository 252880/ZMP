#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _Name(""), _X(0),_Y(0),_Z(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout <<"   "<< GetCmdName() << "  " << _Name  << "                    " <<_X<<" "<<_Y<<" "<<_Z<< endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Name))
    {
      std::cout << "Blad wczytywania nazwy" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _X))
    {
      std::cout << "Blad wczytywania pozycji x" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _Y))
    {
      std::cout << "Blad wczytywania pozycji y" << std::endl;
      return 1;
    }
  
  if (!(Strm_CmdsList >> _Z))
    {
      std::cout << "Blad wczytywania pozycji z" << std::endl;
          return 1;
    }
  
  return 0;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Polozenie[X Y Z]" << endl;
}
