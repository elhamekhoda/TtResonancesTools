#ifndef ELECTRONTTRES_H_
#define ELECTRONTTRES_H_

#include "TopObjectSelectionTools/ElectronSelectionBase.h"

#include "ElectronIsolationSelection/ElectronIsolationSelectionTool.h"


  /**
  * @brief An example class implementing a fairly tight electron selection with
  * isolation.
  *
  * @brief A little class that initialises any tools (for isolation etc) that
  * it needs at the start of the job.  So that if that doesn't work it'll
  * crash asap for you to figure out.  After that it looks at each electron
  * and decides to keep it (or not).
  *
  * @param ptcut The lower pT threshold to apply to the electron.
  */

namespace top {

  class ElectronTtres : public top::ElectronSelectionBase {
    public:
      ElectronTtres(const float ptcut, const bool vetoLArCrack, const std::string& idType,const std::string& idTypeBkg = "NULL");

      /**
      * @brief Doesn't do anything itself.
      */
      virtual ~ElectronTtres(){}

      /**
      * @brief The cuts (per object) are implemented in here.
      *
      * Not that I've marked this as final, to stop people going crazy with
      * inheritance.  Why not just inherit from ElectronSelectionBase instead?
      *
      * @param el The electron to cut on.
      * @return True if you want to keep this electron, false otherwise.
      */
      bool passSelection(const xAOD::Electron& el) const override final;
      bool passSelectionBkg(const xAOD::Electron& el) const override final;

      ///Print the cuts to the ostream.
      void print(std::ostream& os) const override final;
  };

}

#endif
