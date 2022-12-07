#include "Scene.hh"

Scene::Scene(Configuration &config)
{

  for (int i = 0; i < config.objects_vector.size(); i++)
  {
    MobileObj tmp;
    tmp.SetName(config.objects_vector[i].name.c_str());
    tmp.SetAng_Roll_deg(config.objects_vector[i].rot[0]);
    tmp.SetAng_Pitch_deg(config.objects_vector[i].rot[1]);
    tmp.SetAng_Yaw_deg(config.objects_vector[i].rot[2]);
    tmp.SetPosition_m(config.objects_vector[i].shift);
    tmp.setRgb(config.objects_vector[i].rgb);
    tmp.setScale(config.objects_vector[i].scale);
    tmp.setTranslation(config.objects_vector[i].trans);

    AddMobileObj(&tmp);
    std::cout << "dodano obiekt " << tmp.GetName() << std::endl;
  }
}

 }

void Scene::AddMobileObj(MobileObj *pMobObj)
{
  _Container4Objects.insert(std::make_pair(pMobObj->GetName(), *pMobObj));
}
