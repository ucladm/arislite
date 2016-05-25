#ifndef ModuleManager_hh
#define ModuleManager_hh 1

#include <map>

#include "TStopwatch.h"
#include "TTree.h"


#include "Vmodule.hh"


using namespace std;


class ModuleManager{

public:

protected:

  static ModuleManager* theModuleManager;

  ModuleManager();

  ~ModuleManager();

private:
  map<string, Vmodule*> moduleCollection;
  TTree* ftree ;


  map<string, double> timerCollection_real;
  map<string, double> timerCollection_cpu;
  TStopwatch* timer;
  int Nevent_treatmentTime, fnEventTreated;



public:

  void registerModule(Vmodule*, string);

  void processEvent(/*Event* event*/);

  inline void SetTree(TTree* tree){
    ftree = tree;
  };

  inline static ModuleManager* getInstance(){
    if (theModuleManager == NULL)
    theModuleManager = new ModuleManager;
    return (ModuleManager *)theModuleManager;
  };

  inline static void freeInstance(){
    if (theModuleManager != NULL)
    delete theModuleManager;
  };
};



#endif
