#ifndef MUONTTRES_H_
#define MUONTTRES_H_

#include "TopObjectSelectionTools/MuonSelectionBase.h"

#include "MuonSelectorTools/MuonSelectionTool.h"

namespace top {

/**
 * @brief Select muons based on some early DC14 suggestions.
 *
 * @todo Rename this to MuonMiniIso - or something like that?
 */
class MuonTtres : public MuonSelectionBase {
public:
    /**
     * @brief Construct the tool to select good muons.
     *
     * @param ptcut The minimum pT cut for good muons.
     */
    MuonTtres(double ptcut, double sd0cut = 3);

    ~MuonTtres();

    /**
     * @brief Implements the logic to select good muons.
     *
     * @param mu The muon that we want to check.
     * @return True if the muon is good, false otherwise.
     */
    bool passSelection(const xAOD::Muon& mu) override final;

    ///Print the cuts to the ostream.
    void print(std::ostream& os) const override final;

private:
    ///Lower pT threshold to apply to object selection.
    double m_ptcut;

    /// upper significance of d0 threshold
    double m_sd0cut;

    ///Proper tool to select muons.
    CP::MuonSelectionTool m_muonSelectionTool;
};

}

#endif
