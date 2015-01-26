#include "TtResonancesTools/ElectronTtres.h"
#include "ElectronIsolationSelection/ElectronIsolationSelectionTool.h"
#include "TopEvent/EventTools.h"

namespace top {

ElectronTtres::ElectronTtres(const float ptcut, const bool vetoLArCrack, const std::string& idType,const std::string& idTypeBkg) :
        top::ElectronSelectionBase(ptcut, vetoLArCrack, idType, idTypeBkg) {
}

bool ElectronTtres::passSelection(const xAOD::Electron& el) const {
    if (!passSelectionBasic(el))
        return false;

    if (!passSelectionID(el))
        return false;

    if (el.caloCluster()) {
      if( std::fabs(el.caloCluster()->eta()) > 2.47 ){
        return false;
      }
      if( std::fabs(el.caloCluster()->eta()) > 1.37 && std::fabs(el.caloCluster()->eta()) < 1.52 ){
        return false;
      }
    }

    // mini-iso
    if (el.auxdecor<float>("miniIso") / el.pt() > 0.05)
        return false;

    return true;
}

bool ElectronTtres::passSelectionBkg(const xAOD::Electron& el) const {
    if (!passSelectionBasic(el))
        return false;

    if (!passSelectionIDBkg(el))
        return false;

    if (el.caloCluster()) {
      if( std::fabs(el.caloCluster()->eta()) > 2.47 ){
        return false;
      }
      if( std::fabs(el.caloCluster()->eta()) > 1.37 && std::fabs(el.caloCluster()->eta()) < 1.52 ){
        return false;
      }
    }

    // mini-iso
    if (el.auxdecor<float>("miniIso") / el.pt() > 0.05)
        return false;

    return true;
}

void ElectronTtres::print(std::ostream& os) const {
    os << "ElectronTtres\n"
            << "    * pT > " << m_ptcut << "\n"
            << "    * |eta| < 2.5\n"
            << "    * Tight\n"
            << "    * Approx mini-isolation / pT  < 0.05\n"
            ;
}

}
