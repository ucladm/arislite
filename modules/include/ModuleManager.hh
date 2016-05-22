#ifndef ModuleManager_hh
#define ModuleManager_hh 1

class ModuleManager{

public:

protected:

  static ModuleManager* theModuleManager;

  ModuleManager();






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
