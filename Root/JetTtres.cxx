#include "TtResonancesTools/JetTtres.h"

#include <vector>
#include <cmath>

namespace top {

JetTtres::JetTtres(double ptcut, double etamax, double jvfmin) :
    m_ptcut(ptcut),
    m_etamax(etamax),
    m_jvfmin(jvfmin) {
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

    return true;
}


void JetTtres::print(std::ostream& os) const {
    os << "JetTtres\n"
       << "    * pT > " << m_ptcut << "\n"
       << "    * |eta| < " << m_etamax << "\n"
       << "    * |JVF| > " << m_jvfmin << " for pT < 50 GeV and |eta| < 2.4\n";
}
}
