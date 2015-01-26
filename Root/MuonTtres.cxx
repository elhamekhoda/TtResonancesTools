#include "TtResonancesTools/MuonTtres.h"

#include "TopEvent/EventTools.h"

#include <cmath>

namespace top {

MuonTtres::MuonTtres(double ptcut, double sd0cut) :
    m_ptcut(ptcut), m_sd0cut(sd0cut),
    m_muonSelectionTool("MuonSelectionTool") {

    m_muonSelectionTool.msg().setLevel(MSG::WARNING);
    top::check(m_muonSelectionTool.initialize(), "MuonMediumDC14 muon selection tool failed to init");
}

MuonTtres::~MuonTtres() {
}

bool MuonTtres::passSelection(const xAOD::Muon& mu) {
    if (mu.pt() < m_ptcut)
        return false;

    if (!m_muonSelectionTool.accept(mu))
        return false;
    if (std::fabs(mu.eta()) > 2.5)
        return false;

    if (mu.author() != xAOD::Muon::MuidCo)
        return false;

    //if (mu.quality() != xAOD::Muon::Tight)
    //    return false;

    // pass trk cuts
    //if (!mu.passesIDCuts())
    //    return false;
 
    // mini-iso
    if (mu.auxdecor<float>("miniIso")/mu.pt() > 0.05)
      return false;

    //float z0 = mu.primaryTrackParticle()->definingParameters()[1];

    //float d0 = mu.primaryTrackParticle()->definingParameters()[0];
    //float sigma_d0 = mu.primaryTrackParticle()->definingParametersCovMatrixVec()[0];

    //float sd0 = 0;
    //if (sigma_d0 != 0) {
    //  sd0 = d0/sigma_d0;
    //}

    //if (std::fabs(sd0) > m_sd0cut)
    //    return false;

    //if (std::fabs(z0) > 2.0) return false;

    return true;
}

void MuonTtres::print(std::ostream& os) const {
    os << "MuonTtres\n"
       << "    * pT > " << m_ptcut << "\n"
       << "    * Everything else from muon tool - fill this in?\n"
       << "    * |S(d0)| < " << m_sd0cut << "\n";
}

}
