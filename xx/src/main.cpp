#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"
#include "Reader.hh"
#include "Scene.hh"
#include "Sender.hh"
#include "Set4LibInterfaces.hh"
#include <cassert>
#include <dlfcn.h>
#include <iostream>
#include <thread>

int main()
{
  Configuration Config;
  Reader reader;
  Set4LibInterfaces handler;
  Interp4Command *command;
  std::istringstream stream;
  std::vector<std::thread> threads;
  reader.init("wykonaj.cmd");

  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  handler.init(Config.libraries_vector);
  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);
  std::string key;
  reader.execPreprocesor(stream);
  while (stream >> key)
  {
    command = handler.execute(key);
    
    if (handler.isParallel() && command != nullptr)
    {
      command->ReadParams(stream);
      threads.push_back(std::thread(&Interp4Command::ExecCmd, command, &scene));
    
    }
    else if (!handler.isParallel())
    {
      for (int i = 0; i < threads.size(); ++i)
      {
        if (threads[i].joinable())
          threads[i].join();
      }
      threads.clear();
    }
  }

 

  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  for (int i = 0; i < threads.size(); ++i)
  {
 
    if (threads[i].joinable())
      threads[i].join();
  }
  Thread4Sending.join();

  return 0;
}
