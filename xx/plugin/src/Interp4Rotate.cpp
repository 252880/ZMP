#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate():_Name(""), _Speed_mmS(0), _Angle(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout <<"   "<< GetCmdName() << "  " <<_Name<<" "<< _Speed_mmS  << " " <<_Angle<< endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( std::shared_ptr<MobileObject> & obj,  std::shared_ptr<Scene> & pAccCtrl) const
{
    double yaw = obj->GetAng_Yaw_deg();
    double delta_= 0;
    double dist_step_deg = (double)_Angle/X;
    double time_ = (((double)this->_Angle/this->_Speed_mmS)*1000000)/X;

    for(int i = 0; i<X; ++i)
    {
        pAccCtrl->LockAccess(); // Lock access to the scene to modify something :)
        delta_+= dist_step_deg;
        obj->SetAng_Yaw_deg(delta_ + yaw);
        pAccCtrl->MarkChange();
        pAccCtrl->UnlockAccess();
        usleep(time_);
    }

  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Name))
    {
      std::cout << "Blad wczytywania nazwy" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _Speed_mmS))
    {
      std::cout << "Blad wczytywania predkosci obrotowej" << std::endl;
      return 1;
    }

  if (!(Strm_CmdsList >> _Angle))
    {
      std::cout << "Blad wczytywania kata " << std::endl;
      return 1;
    }

 
  return 0;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Szybkosc[m/s]  Kat" << endl;
}
