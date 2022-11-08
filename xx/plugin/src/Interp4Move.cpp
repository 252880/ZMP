#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move():_Name(""), _Speed_mmS(0), _Length(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout <<"   "<< GetCmdName() << "  " <<_Name<<"             "<< _Speed_mmS  << "              " << _Length<< endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{

  if (!(Strm_CmdsList >> _Name))
    {
      std::cout << "Blad wczytywania nazwy" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _Speed_mmS))
    {
      std::cout << "Blad wczytywania predkosci" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _Length))
    {
      std::cout << "Blad wczytywania odleglosci" << std::endl;
      return 1;
    }
  return 0;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
