#include "TtResonancesTools/TtresEventSaverFlatNtuple.h"

#include "TopEvent/Event.h"

#include "TopEventSelectionTools/TreeManager.h"

#include "xAODRootAccess/TEvent.h"
#include "TopEvent/EventTools.h"

#include <vector>
#include <iostream>

namespace top {

//Always initialise primitive types in the constructor
TtresEventSaverFlatNtuple::TtresEventSaverFlatNtuple() {
  m_ghostjetcollection = "GhostAntiKt3TrackJet";
  m_trackjetcollection = "AntiKt3PV0TrackJets";
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

        // book large-R calo jet trackjet b-tagging information
        systematicTree->makeOutputVariable(m_ljet_ghosttrackjet_idx, "ljet_ghosttrackjet_idx");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjet, "ljet_nghosttrackjet");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjetb, "ljet_nghosttrackjetb");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjetbb, "ljet_nghosttrackjetbb");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjetc, "ljet_nghosttrackjetc");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjetcc, "ljet_nghosttrackjetcc");
        systematicTree->makeOutputVariable(m_ljet_nghosttrackjetl, "ljet_nghosttrackjetl");


        // save an int that is 0/1 if the small-R jet is the one with dR < 1.5 to the lepton
        // and it is the highest p_T one
        systematicTree->makeOutputVariable(m_jet_closeToLepton, "jet_closeToLepton");

        // book small-R calo jet trackjet b-tagging information
        systematicTree->makeOutputVariable(m_jet_ghosttrackjet_idx, "jet_ghosttrackjet_idx");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjet, "jet_nghosttrackjet");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjetb, "jet_nghosttrackjetb");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjetbb, "jet_nghosttrackjetbb");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjetc, "jet_nghosttrackjetc");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjetcc, "jet_nghosttrackjetcc");
        systematicTree->makeOutputVariable(m_jet_nghosttrackjetl, "jet_nghosttrackjetl");

        // book track jet info
        systematicTree->makeOutputVariable(m_trackjet_pt, "trackjet_pt");
        systematicTree->makeOutputVariable(m_trackjet_eta, "trackjet_eta");
        systematicTree->makeOutputVariable(m_trackjet_phi, "trackjet_phi");
        systematicTree->makeOutputVariable(m_trackjet_e, "trackjet_e");

        // TODO
        // these aren't available yet =(
        /*
        systematicTree->makeOutputVariable(m_trackjet_mv1, "trackjet_mv1");
        systematicTree->makeOutputVariable(m_trackjet_mvb, "trackjet_mvb");
        systematicTree->makeOutputVariable(m_trackjet_mv1c, "trackjet_mv1c");
        systematicTree->makeOutputVariable(m_trackjet_mv2c00, "trackjet_mv2c00");
        systematicTree->makeOutputVariable(m_trackjet_mv2c10, "trackjet_mv2c10");
        systematicTree->makeOutputVariable(m_trackjet_mv2c20, "trackjet_mv2c20");
        systematicTree->makeOutputVariable(m_trackjet_ip3dsv1, "trackjet_ip3dsv1");
        */

        systematicTree->makeOutputVariable(m_trackjet_nghostb, "trackjet_nghostb");
        systematicTree->makeOutputVariable(m_trackjet_nghostc, "trackjet_nghostc");


    }
}

void TtresEventSaverFlatNtuple::saveEvent(const top::Event& event, unsigned int systematicNumber, xAOD::TEvent& xaodEvent) {
    //calculate our extra variable:

    int i = 0;
    i = 0;

    m_ljet_ghosttrackjet_idx.resize(event.m_largeJets.size(), std::vector<int>());
    m_ljet_nghosttrackjet.resize(event.m_largeJets.size());
    m_ljet_nghosttrackjetb.resize(event.m_largeJets.size());
    m_ljet_nghosttrackjetbb.resize(event.m_largeJets.size());
    m_ljet_nghosttrackjetc.resize(event.m_largeJets.size());
    m_ljet_nghosttrackjetcc.resize(event.m_largeJets.size());
    m_ljet_nghosttrackjetl.resize(event.m_largeJets.size());


    m_ljet_good.resize(event.m_largeJets.size());
    for (const auto* const jetPtr : event.m_largeJets) {
        m_ljet_good[i] = 0;
        m_ljet_ghosttrackjet_idx[i].clear();
        if (jetPtr->isAvailable<int>("good"))
            m_ljet_good[i] = jetPtr->auxdata<int>("good");

        // I want this to crash if they're not available!
        m_ljet_nghosttrackjet[i] = jetPtr->getAttribute<int>("nGhostJets");
        m_ljet_nghosttrackjetb[i] = jetPtr->getAttribute<int>("nTrueBGhostJets");
        m_ljet_nghosttrackjetbb[i] = jetPtr->getAttribute<int>("nTrueBBGhostJets");
        m_ljet_nghosttrackjetc[i] = jetPtr->getAttribute<int>("nTrueCGhostJets");
        m_ljet_nghosttrackjetcc[i] = jetPtr->getAttribute<int>("nTrueCCGhostJets");
        m_ljet_nghosttrackjetl[i] = jetPtr->getAttribute<int>("nTrueLGhostJets");

        // store the ghost-associated trackjet indices
        const std::vector<ElementLink<xAOD::IParticleContainer> >& ghostJets =
            jetPtr->getAttribute<std::vector<ElementLink<xAOD::IParticleContainer> > >(m_ghostjetcollection);

        for (const auto& link : ghostJets)
            m_ljet_ghosttrackjet_idx[i].push_back(link.index());

        ++i;
    }


    i = 0;
    m_jet_closeToLepton.resize(event.m_jets.size());
    m_jet_ghosttrackjet_idx.resize(event.m_jets.size(), std::vector<int>());
    m_jet_nghosttrackjet.resize(event.m_jets.size());
    m_jet_nghosttrackjetb.resize(event.m_jets.size());
    m_jet_nghosttrackjetbb.resize(event.m_jets.size());
    m_jet_nghosttrackjetc.resize(event.m_jets.size());
    m_jet_nghosttrackjetcc.resize(event.m_jets.size());
    m_jet_nghosttrackjetl.resize(event.m_jets.size());
    for (const auto* const jetPtr : event.m_jets) {
        m_jet_closeToLepton[i] = 0;
        m_jet_ghosttrackjet_idx[i].clear();

        if (jetPtr->isAvailable<int>("closeToLepton"))
            m_jet_closeToLepton[i] = jetPtr->auxdata<int>("closeToLepton");

        // I want this to crash if they're not available!
        m_jet_nghosttrackjet[i] = jetPtr->getAttribute<int>("nGhostJets");
        m_jet_nghosttrackjetb[i] = jetPtr->getAttribute<int>("nTrueBGhostJets");
        m_jet_nghosttrackjetbb[i] = jetPtr->getAttribute<int>("nTrueBBGhostJets");
        m_jet_nghosttrackjetc[i] = jetPtr->getAttribute<int>("nTrueCGhostJets");
        m_jet_nghosttrackjetcc[i] = jetPtr->getAttribute<int>("nTrueCCGhostJets");
        m_jet_nghosttrackjetl[i] = jetPtr->getAttribute<int>("nTrueLGhostJets");

        // store the ghost-associated trackjet indices
        const std::vector<ElementLink<xAOD::IParticleContainer> >& ghostJets =
            jetPtr->getAttribute<std::vector<ElementLink<xAOD::IParticleContainer> > >(m_ghostjetcollection);

        for (const auto& link : ghostJets)
            m_jet_ghosttrackjet_idx[i].push_back(link.index());

        ++i;
    }

    // store track jet info
    const xAOD::JetContainer* trackjets = 0;
    if (m_trackjetcollection != "") {
        top::check(xaodEvent.retrieve(trackjets, m_trackjetcollection), "FAILURE");

        m_trackjet_pt.resize(trackjets->size());
        m_trackjet_eta.resize(trackjets->size());
        m_trackjet_phi.resize(trackjets->size());
        m_trackjet_e.resize(trackjets->size());

        // TODO
        // trackjet b-tagging variables
        /*
        m_trackjet_mv1.resize(trackjets->size());
        m_trackjet_mvb.resize(trackjets->size());
        m_trackjet_mv1c.resize(trackjets->size());
        m_trackjet_mv2c00.resize(trackjets->size());
        m_trackjet_mv2c10.resize(trackjets->size());
        m_trackjet_mv2c20.resize(trackjets->size());
        m_trackjet_ip3dsv1.resize(trackjets->size());
        */

        m_trackjet_nghostb.resize(trackjets->size());
        m_trackjet_nghostc.resize(trackjets->size());
    
        i = 0;
        for (xAOD::JetContainer::const_iterator jet_itr = trackjets->begin(); jet_itr != trackjets->end(); ++jet_itr) {
            const xAOD::Jet* trackjetPtr = *jet_itr;
    
            m_trackjet_pt[i] = trackjetPtr->pt();
            m_trackjet_eta[i] = trackjetPtr->eta();
            m_trackjet_phi[i] = trackjetPtr->phi();
            m_trackjet_e[i] = trackjetPtr->e();
    
            // TODO
            // trackjet b-tagging
            /*
            m_trackjet_mv1[i] = trackjetPtr->btagging()->MV1_discriminant();
            m_trackjet_ip3dsv1[i] = trackjetPtr->btagging()->SV1plusIP3D_discriminant();
    
            // for studies on high performance b-tagging
            // the following are in DC14
            double mvx = -999;
            trackjetPtr->btagging()->MVx_discriminant("MV1c", mvx);
            m_trackjet_mv1c[i] = mvx;
            mvx = -999;
            trackjetPtr->btagging()->MVx_discriminant("MVb", mvx);
            m_trackjet_mvb[i] = mvx;
            mvx = -999;
            trackjetPtr->btagging()->MVx_discriminant("MV2c00", mvx);
            m_trackjet_mv2c00[i] = mvx;
            mvx = -999;
            trackjetPtr->btagging()->MVx_discriminant("MV2c10", mvx);
            m_trackjet_mv2c10[i] = mvx;
            mvx = -999;
            trackjetPtr->btagging()->MVx_discriminant("MV2c20", mvx);
            m_trackjet_mv2c20[i] = mvx;
            */
    
            // track jet flavor labeling
            m_trackjet_nghostb[i] = trackjetPtr->getAttribute<int>("GhostBHadronsFinalCount");
            m_trackjet_nghostc[i] = trackjetPtr->getAttribute<int>("GhostCHadronsFinalCount");
    
            ++i;
        }
    }

    EventSaverFlatNtuple::saveEvent(event, systematicNumber, xaodEvent);
}

}

