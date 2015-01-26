#include "TtResonancesTools/TtresEventSaverFlatNtuple.h"

#include "TopEvent/Event.h"

#include "TopEventSelectionTools/TreeManager.h"

namespace top {

//Always initialise primitive types in the constructor
TtresEventSaverFlatNtuple::TtresEventSaverFlatNtuple() {
}

TtresEventSaverFlatNtuple::~TtresEventSaverFlatNtuple() {
}

/**
 * Add our extra variable to each systematic TTree
 */
void TtresEventSaverFlatNtuple::initialise(top::TopConfig* config, TFile* file, const std::vector<std::string>& treeNames, const std::vector<std::string>& extraBranches, xAOD::TEvent& xaodEvent) {
    EventSaverFlatNtuple::initialise(config, file, treeNames, extraBranches, xaodEvent);

    for (auto systematicTree : treeManagers()) {
        // save an int that is 0/1 if the large-R jet satisfies all basic cuts
        // including mass, sqrt(d_12), dr, dphi, etc.
        // so that we can save all other large-R jets as well just passing pt and eta cuts
        systematicTree->makeOutputVariable(m_ljet_good, "ljet_good");

        // save an int that is 0/1 if the small-R jet is the one with dR < 1.5 to the lepton
        // and it is the highest p_T one
        systematicTree->makeOutputVariable(m_jet_closeToLepton, "jet_closeToLepton");
    }
}

void TtresEventSaverFlatNtuple::saveEvent(const top::Event& event, unsigned int systematicNumber, xAOD::TEvent& xaodEvent) {
    //calculate our extra variable:

    int i = 0;
    i = 0;
    m_ljet_good.resize(event.m_largeJets.size());
    for (const auto* const jetPtr : event.m_largeJets) {
        m_ljet_good[i] = 0;
        if (jetPtr->isAvailable<int>("good"))
            m_ljet_good[i] = jetPtr->auxdata<int>("good");
        ++i;
    }


    i = 0;
    m_jet_closeToLepton.resize(event.m_jets.size());
    for (const auto* const jetPtr : event.m_jets) {
        m_jet_closeToLepton[i] = 0;
        if (jetPtr->isAvailable<int>("closeToLepton"))
            m_jet_closeToLepton[i] = jetPtr->auxdata<int>("closeToLepton");
        ++i;
    }

    EventSaverFlatNtuple::saveEvent(event, systematicNumber, xaodEvent);
}

}

