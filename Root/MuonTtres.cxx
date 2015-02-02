#include "TtResonancesTools/MuonTtres.h"
#include "TopEvent/EventTools.h"
#include <cmath>
#include "TopObjectSelectionTools/MuonDC14.h"

namespace top {

MuonTtres::MuonTtres(double ptcut, double etamax, double sd0, IsolationBase *isolation) :
    MuonDC14(ptcut, etamax, isolation), m_sd0(sd0) {
}

MuonTtres::~MuonTtres() {
}

bool MuonTtres::passSelection(const xAOD::Muon& mu) {
    bool basic = MuonDC14::passSelection(mu);
    if (!basic) return false;

    if (mu.author() != xAOD::Muon::MuidCo)
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
    MuonDC14::print(os);
}

}

