#ifndef ModuleManager_hh
#define ModuleManager_hh 1

#include <map>

class ModuleManager{

public:

protected:

  static ModuleManager* theModuleManager;

  ModuleManager();

  ~ModuleManager(){};

private:
  map<string, Vmodule*> moduleCollection;


public:

  inline static ModuleManager* getInstance(){
    if (theModuleManager == NULL)
    theModuleManager = new ModuleManager;
    return (ModuleManager *)theModuleManager;
  };

  inline static void freeInstance(){
    if (thePostgresqlConnection != NULL)
    delete thePostgresqlConnection;
  };
};



#endif
