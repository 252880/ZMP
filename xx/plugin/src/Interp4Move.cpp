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
  cout <<"   "<< GetCmdName() << "  " <<_Name<<" "<< _Speed_mmS  << " " << _Length<< endl;
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
bool Interp4Move::ExecCmd(std::shared_ptr<MobileObject> & obj,  std::shared_ptr<Scene> & pAccCtrl) const
{
  

  Vector3D position_init = obj->GetPositoin_m();
  double roll = obj->GetAng_Roll_deg();
  double pitch = obj->GetAng_Pitch_deg();
  double yaw = obj->GetAng_Yaw_deg();


  double x_ = y_ = z_ = 0;
  
   double dist_= (double)_Length/X;
    double time_ = (((double)this->_Length/this->_Speed_mmS)*1000000)/X;
         

 
  for (int i = 0; i < X; ++i)
  {
  
   pAccCtrl->LockAccess(); 
   
    x_ += dist_step_m*cos(pitch*M_PI/180)*cos(yaw*M_PI/180);
        y_+= dist_step_m*(cos(startRoll*M_PI/180)*sin(yaw*M_PI/180) + cos(yaw*M_PI/180)*sin(startPitch*M_PI/180)*sin(startRoll*M_PI/180));
        z_+= dist_step_m*(sin(startRoll*M_PI/180)*sin(yaw*M_PI/180) - cos(roll*M_PI/180)*cos(startYaw*M_PI/180)*sin(startPitch*M_PI/180));
        obj->SetPosition_m(Vector3D(x_+startPos.x(), y_+startPos.y(), z_+startPos.z()));

        pAccCtrl->MarkChange();
        pAccCtrl->UnlockAccess();
        usleep(time_step_us);
  }
  
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
