#include "TtResonancesTools/ElectronTtres.h"
#include "TopEvent/EventTools.h"
#include "TopObjectSelectionTools/ElectronCutBasedDC14.h"

namespace top {

ElectronTtres::ElectronTtres(double ptcut, bool vetoCrack, const std::string& quality, const std::string& qualityLoose, IsolationBase* isolation) :
    ElectronCutBasedDC14(ptcut, vetoCrack, quality, qualityLoose, isolation) {
}

bool ElectronTtres::passSelection(const xAOD::Electron& el) const {
    bool basic = ElectronCutBasedDC14::passSelection(el);
    if (!basic) return false;

    if (el.caloCluster()) {
      if( std::fabs(el.caloCluster()->eta()) > 2.47 ){
        return false;
      }
    }

    return true;
}

bool ElectronTtres::passSelectionLoose(const xAOD::Electron& el) const {
    bool basic = ElectronCutBasedDC14::passSelectionLoose(el);
    if (!basic) return false;

    if (el.caloCluster()) {
      if( std::fabs(el.caloCluster()->eta()) > 2.47 ){
        return false;
      }
    }

    return true;
}

void ElectronTtres::print(std::ostream& os) const {
    ElectronCutBasedDC14::print(os);
}

}
