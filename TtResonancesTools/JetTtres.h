#ifndef JETTTRES_H_
#define JETTTRES_H_

#include "TopObjectSelectionTools/JetSelectionBase.h"

namespace top {

/**
 * @brief A class that performs object cuts on Jets (of any size!).  At the
 * moment it includes a cut on pT, eta and JVF.
 */
class JetTtres : public JetSelectionBase {
public:
    /**
     * @brief A tool to select some jets for DC14 based on the pT and eta cuts.
     *
     * @param ptcut The minimum pT to accept good jets.
     * @param etamax The maximum eta cut.
     * @param jvfmin The minimum cut on the jet vertex fraction
     */
    JetTtres(double ptcut, double etamax, double jvfmin);

    ///Does nothing.
    ~JetTtres();

    /**
     * @brief Implements the logic to select jets based on pT and eta.
     *
     * It cuts on pt, eta, jvf.
     *
     * @param jet The jet to check.
     * @return True if the jet passes the cuts, false otherwise.
     */
    bool passSelection(const xAOD::Jet& jet) override final;

    ///Print the cuts to the ostream.
    void print(std::ostream& os) const override final;

private:
    ///The lower pT cut threshold to apply to the object.
    double m_ptcut;

    ///The upper eta cut.
    double m_etamax;

    ///The minimum JVF cut for jets with pT < 50 GeV and |eta| < 2.4.
    double m_jvfmin;
};

}

#endif
