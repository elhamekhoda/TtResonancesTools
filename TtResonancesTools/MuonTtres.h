#ifndef MUONTTRES_H_
#define MUONTTRES_H_

#include "TopObjectSelectionTools/MuonSelectionBase.h"
#include "TopObjectSelectionTools/MuonDC14.h"
#include "TopObjectSelectionTools/IsolationTools.h"

#include "MuonSelectorTools/MuonSelectionTool.h"

namespace top {

/**
 * @brief Select muons based on some early DC14 suggestions and extra tt resonances cuts.
 */
class MuonTtres : public MuonDC14 {
public:
    /**
     * @brief Construct the tool to select good muons.
     *
     * @param ptcut The minimum pT cut for good muons.
     * @param etamax The |eta| cut to apply.  Is this done by the muon selector
     * tool?
     * @param isolation The isolation the user wants to apply.  Don't want any
     * isolation to be applied?  Then leave this as a nullptr.
     */
    MuonTtres(double ptcut, double etamax, double sd0, IsolationBase *isolation);

    ///Does nothing.
    ~MuonTtres();

    /**
     * @brief Implements the logic to select good muons.
     *
     * @param mu The muon that we want to check.
     * @return True if the muon is good, false otherwise.
     */
    bool passSelection(const xAOD::Muon& mu) override;

    ///Print the cuts to the ostream.
    void print(std::ostream& os) const override;

private:
    // Sd0 cut
    double m_sd0;

};

}

#endif
