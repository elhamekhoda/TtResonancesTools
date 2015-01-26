#include "TtResonancesTools/FirstOverlapRemovalIndicesTtres.h"

namespace top {

FirstOverlapRemovalIndicesTtres::FirstOverlapRemovalIndicesTtres() {
}

void FirstOverlapRemovalIndicesTtres::overlapremoval(xAOD::ElectronContainer* el,
        xAOD::MuonContainer* /*mu*/,
        xAOD::JetContainer* jet,
        xAOD::JetContainer* /*ljet*/,
        std::shared_ptr<std::vector<unsigned int>>  /*OUT_el*/,
        std::shared_ptr<std::vector<unsigned int>>  /*OUT_mu*/,
        std::shared_ptr<std::vector<unsigned int>>  /*OUT_jet*/,
        std::shared_ptr<std::vector<unsigned int>>  /*OUT_ljet*/) {
    m_o.Load(jet, el);
    m_o.AnalyzeEvent();
}

void FirstOverlapRemovalIndicesTtres::print(std::ostream& os) const {
    os << "fill in\n";
}

}
