#ifndef ELECTRONTTRES_H_
#define ELECTRONTTRES_H_

#include "TopObjectSelectionTools/ElectronCutBasedDC14.h"
#include "TopObjectSelectionTools/IsolationTools.h"
#include "TopObjectSelectionTools/ElectronSelectionBase.h"

#include <memory>

namespace top {

/**
 * @brief Electron selection based on the cut-based thingy.
 */
class ElectronTtres : public top::ElectronCutBasedDC14 {
public:
    /**
     * @brief Class to help select cut-based good electrons.
     *
     * @param ptcut The minimum pT cut to apply to the electrons.
     * @param vetoCrack Do you want to veto 1.37 < |cluster_eta| < 1.52?
     * @param quality The definition for good electrons, e.g. "Tight"
     * @param qualityLoose The loose defeinition, for fake-lepton estimates with
     * the matrix method?
     * @param isolation nullptr for un-isolated, or a new "isolation object" to
     * apply isolation cuts
     */
    ElectronTtres(double ptcut, bool vetoCrack, const std::string& quality, const std::string& qualityLoose, IsolationBase* isolation);

    /**
     * @brief The cuts to select good electrons for your analysis should be
     * implemented in here.
     *
     * @param el The electron to cut on (all electrons in the event are passed
     * to the tool)
     * @return True if this is a good electron, false otherwise.
     */
    bool passSelection(const xAOD::Electron& el) const override;

    /**
     * @brief The loose selection needed by some background estimates.
     *
     * @param el
     * @return
     */
    bool passSelectionLoose(const xAOD::Electron& el) const override;

    /**
     * @brief Print some useful information about the electron selection.
     *
     * Usually this goes to the log file, so you know what you ran with.
     *
     * @param Where the print-out should go, e.g. cout.
     */
    void print(std::ostream&) const override;

};

}

#endif

