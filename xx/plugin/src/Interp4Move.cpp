#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _Name(""), _Speed_mmS(0), _Lenght(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name << " " << _Speed_mmS << " " << _Lenght << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(Scene *scene) const
{
  MobileObj *obj = scene->FindMobileObj(_Name.c_str());
  Vector3D position = obj->GetPositoin_m();
  double roll= obj->GetAng_Roll_deg();
  double pitch= obj->GetAng_Pitch_deg();
  double yaw = obj->GetAng_Yaw_deg();

  double time = _Lenght / _Speed_mmS;
  double steps = (int)(time * N);

  double x_ = 0, y_ = 0, z_ = 0;
  Vector3D move;
  double step_distance = _Distance_m / steps; 
  double step = 0.0333333 * 1000000;            


  for (int i = 0; i < steps; ++i)
  {
  scene->LockAccess();
  
    x_ += step_distance * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
    y_ += step_distance * (cos(roll * M_PI / 180) * sin(yaw * M_PI / 180) + cos(yaw * M_PI / 180) * sin(pitch * M_PI / 180) * sin(roll * M_PI / 180));
    z_ += step_distance * (sin(roll * M_PI / 180) * sin(yaw * M_PI / 180) - cos(roll * M_PI / 180) * cos(yaw * M_PI / 180) * sin(pitch * M_PI / 180));
    move[0] = x_+ position[0];
    move[1] = y_ + position[1];
    move[2] = z_ + position[2];
    
    object->SetPosition_m(move);
    scene->MarkChange();
    scene->UnlockAccess();
    usleep(step;
  }
 

  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Speed_mmS))
  {
    std::cout << "Blad wczytywania predkosci obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Lenght))
  {
    std::cout << "Blad wczytywania odleglosci" << std::endl;
    return 1;
  }
  return 0;
}

/*!
 *
 */
Interp4Command *Interp4Move::CreateCmd()
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
