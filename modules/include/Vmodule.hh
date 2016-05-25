#ifndef VMODULE_h
#define VMODULE_h 1

#include <iostream>

#include "TTree.h"

class Vmodule{

public:
  Vmodule(){};

  virtual ~Vmodule(){};
  virtual void initialization(TTree* tree){};
  virtual void process(/*Event* event*/){};


};



#endif
