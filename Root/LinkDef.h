#include "TtResonancesTools/ObjectLoaderTtres.h"
#include "TtResonancesTools/TtresEventSaverFlatNtuple.h"
#include "TtResonancesTools/TtResonancesToolsLoader.h"
#include "TtResonancesTools/TtbarPartonHistorySaver.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;

//for loading the object selection at run time
#pragma link C++ class top::ObjectLoaderTtres+;
#pragma link C++ class top::TtResonancesToolsLoader+;
#pragma link C++ class top::TtresEventSaverFlatNtuple+;
#pragma link C++ class top::TtbarPartonHistorySaver+;

#endif
