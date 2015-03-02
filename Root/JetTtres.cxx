#include "TtResonancesTools/JetTtres.h"

#include <vector>
#include <cmath>
#include <string>

namespace top {

JetTtres::JetTtres(double ptcut, double etamax, double jvfmin, const std::string &ghostCollectionName) :
    m_ptcut(ptcut),
    m_etamax(etamax),
    m_jvfmin(jvfmin),
    m_ghostCollectionName(ghostCollectionName) {
}

JetTtres::~JetTtres() {}

bool JetTtres::passSelection(const xAOD::Jet& jet) {
    if (jet.pt() < m_ptcut)
        return false;

    if (std::fabs(jet.eta()) > m_etamax)
        return false;

    if (m_jvfmin > 0) { // use 0 for large-R jets, on which we don't want the JVF cut
      //std::vector<float> v_jvf = jet.getAttribute<std::vector<float> >("JVF");
      //fewer than one jvf - then crash to let us know...
      const float jvf = jet.getAttribute<std::vector<float> >("JVF").at(0);
      //if (!v_jvf.empty())
      //    jvf = v_jvf[0];

      if ((jet.pt() < 50e3) && std::fabs(jet.eta()) < 2.4 && std::fabs(jvf) < m_jvfmin)
          return false;

    }
    jet.auxdecor<int>("good") = 1;
    jet.auxdecor<int>("closeToLepton") = 0;

    // TODO
    // some of this only works for MC.

    int nGhostJets = 0;
    int nTrueBGhostJets = 0;
    int nTrueBBGhostJets = 0;
    int nTrueCGhostJets = 0;
    int nTrueCCGhostJets = 0;
    int nTrueLGhostJets = 0;

    // set nonsense values if no ghost collection.
    if (m_ghostCollectionName == "") {
        nGhostJets = -1;
        nTrueBGhostJets = -1;
        nTrueBBGhostJets = -1;
        nTrueCGhostJets = -1;
        nTrueCCGhostJets = -1;
        nTrueLGhostJets = -1;
    } else {
        const std::vector<ElementLink<xAOD::IParticleContainer> >& ghostJets =
            jet.getAttribute<std::vector<ElementLink<xAOD::IParticleContainer> > >(m_ghostCollectionName);

        for (const auto& link : ghostJets) {
            const xAOD::Jet *ghostjet = dynamic_cast<const xAOD::Jet*>(*link);

            // make sure the ghost jets will be taggable
            if (ghostjet->pt() < 7000)
                continue;

            nGhostJets++;

            // labeling preference: BB, B, CC, C, L
            int nBs = ghostjet->getAttribute<int>("GhostBHadronsFinalCount");
            int nCs = ghostjet->getAttribute<int>("GhostCHadronsFinalCount");
            if (nBs > 1)
                nTrueBBGhostJets++;
            else if (nBs == 1)
                nTrueBGhostJets++;
            else if (nCs > 1)
                nTrueCCGhostJets++;
            else if (nCs == 1)
                nTrueCGhostJets++;
            else
                nTrueLGhostJets++;
        }
    }

    jet.auxdecor<int>("nGhostJets") = nGhostJets;
    jet.auxdecor<int>("nTrueBGhostJets") = nTrueBGhostJets;
    jet.auxdecor<int>("nTrueBBGhostJets") = nTrueBBGhostJets;
    jet.auxdecor<int>("nTrueCGhostJets") = nTrueCGhostJets;
    jet.auxdecor<int>("nTrueCCGhostJets") = nTrueCCGhostJets;
    jet.auxdecor<int>("nTrueLGhostJets") = nTrueLGhostJets;


    return true;
}


void JetTtres::print(std::ostream& os) const {
    os << "JetTtres\n"
       << "    * pT > " << m_ptcut << "\n"
       << "    * |eta| < " << m_etamax << "\n"
       << "    * |JVF| > " << m_jvfmin << " for pT < 50 GeV and |eta| < 2.4\n";
}
}
