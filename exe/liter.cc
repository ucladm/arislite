#include <iostream>

#include "TTree.h"
#include "TFile.h"

#include "ModuleManager.hh"
#include "StandardObs.hh"

#include "ReaderManager.hh"
#include "ReadArisFiles.hh"



using namespace std;

int main(){

  cout<<"hello world"<<endl;


  ReaderManager* readerManagerInstance = ReaderManager::getInstance();

  readerManagerInstance->registerReader(new ReadArisFiles("arisana.root"),"fileReader");


  TFile* file_out = new TFile("Out.root","RECREATE");
  TTree* tree = new TTree("litetree","litetree");



  ModuleManager* moduleManagerInstance = ModuleManager::getInstance();
  moduleManagerInstance->SetTree(tree);

  moduleManagerInstance->registerModule(new StandardObs,"StandardObs");


  arisana::EventData* event = NULL;
  while(readerManagerInstance->getNextEvent()){

    
    cout<<readerManagerInstance->getCurentEvent()->info.event_id<<endl;;

  }

  return 0;
}
