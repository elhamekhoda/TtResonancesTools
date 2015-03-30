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
  m_akt4truthjetcollection = "AntiKt4TruthJets";
  m_akt10truthjetcollection = "AntiKt10TruthJets";
  m_saveTruthJets = true;
  m_savePartons = true;
}

TtresEventSaverFlatNtuple::~TtresEventSaverFlatNtuple() {
}

/**
 * Add our extra variable to each systematic TTree
 */
void TtresEventSaverFlatNtuple::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches, xAOD::TEvent& xaodEvent) {
    EventSaverFlatNtuple::initialize(config, file, extraBranches, xaodEvent);

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

        // saving truth jet
        if (m_saveTruthJets) {
            systematicTree->makeOutputVariable(m_akt4truthjet_pt,  "akt4truthjet_pt");
            systematicTree->makeOutputVariable(m_akt4truthjet_eta, "akt4truthjet_eta");
            systematicTree->makeOutputVariable(m_akt4truthjet_phi, "akt4truthjet_phi");
            systematicTree->makeOutputVariable(m_akt4truthjet_e,   "akt4truthjet_e");

            systematicTree->makeOutputVariable(m_akt10truthjet_pt,  "akt10truthjet_pt");
            systematicTree->makeOutputVariable(m_akt10truthjet_eta, "akt10truthjet_eta");
            systematicTree->makeOutputVariable(m_akt10truthjet_phi, "akt10truthjet_phi");
            systematicTree->makeOutputVariable(m_akt10truthjet_e,   "akt10truthjet_e");
        }

        if (m_savePartons) {
            systematicTree->makeOutputVariable(m_MC_b_from_t_pt,      "MC_b_from_t_pt");
            systematicTree->makeOutputVariable(m_MC_b_from_t_eta,     "MC_b_from_t_eta");
            systematicTree->makeOutputVariable(m_MC_b_from_t_phi,     "MC_b_from_t_phi");
            systematicTree->makeOutputVariable(m_MC_b_from_t_e,       "MC_b_from_t_e");
            systematicTree->makeOutputVariable(m_MC_b_from_t_match,   "MC_b_from_t_match");
            systematicTree->makeOutputVariable(m_MC_b_from_t_jetidx,  "MC_b_from_t_jetidx");
            systematicTree->makeOutputVariable(m_MC_b_from_t_recodr,  "MC_b_from_t_recodr");
            systematicTree->makeOutputVariable(m_MC_b_from_t_truthdr, "MC_b_from_t_truthdr");

            systematicTree->makeOutputVariable(m_MC_b_from_t_jet_pt,  "MC_b_from_t_jet_pt");
            systematicTree->makeOutputVariable(m_MC_b_from_t_jet_eta, "MC_b_from_t_jet_eta");
            systematicTree->makeOutputVariable(m_MC_b_from_t_jet_phi, "MC_b_from_t_jet_phi");
            systematicTree->makeOutputVariable(m_MC_b_from_t_jet_e,   "MC_b_from_t_jet_e");
        }

    }
}

void TtresEventSaverFlatNtuple::saveEvent(const top::Event& event, xAOD::TEvent& xaodEvent) {
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

    if (m_saveTruthJets) {
        const xAOD::JetContainer* akt4truthjets = nullptr;
        if (m_akt4truthjetcollection != "") {
            top::check(xaodEvent.retrieve(akt4truthjets, m_akt4truthjetcollection), "FAILURE");
            m_akt4truthjet_pt.resize(akt4truthjets->size());
            m_akt4truthjet_eta.resize(akt4truthjets->size());
            m_akt4truthjet_phi.resize(akt4truthjets->size());
            m_akt4truthjet_e.resize(akt4truthjets->size());

            i = 0;
            for (xAOD::JetContainer::const_iterator jet_itr = akt4truthjets->begin(); jet_itr != akt4truthjets->end(); ++jet_itr) {
                const xAOD::Jet* akt4truthjetPtr = *jet_itr;
    
                m_akt4truthjet_pt[i] = akt4truthjetPtr->pt();
                m_akt4truthjet_eta[i] = akt4truthjetPtr->eta();
                m_akt4truthjet_phi[i] = akt4truthjetPtr->phi();
                m_akt4truthjet_e[i] = akt4truthjetPtr->e();
                ++i;
            }
        }

        const xAOD::JetContainer* akt10truthjets = nullptr;
        if (m_akt10truthjetcollection != "") {

            top::check(xaodEvent.retrieve(akt10truthjets, m_akt10truthjetcollection), "FAILURE");

            m_akt10truthjet_pt.resize(akt10truthjets->size());
            m_akt10truthjet_eta.resize(akt10truthjets->size());
            m_akt10truthjet_phi.resize(akt10truthjets->size());
            m_akt10truthjet_e.resize(akt10truthjets->size());
            // setup extra branches here

            i = 0;
            for (xAOD::JetContainer::const_iterator jet_itr = akt10truthjets->begin(); jet_itr != akt10truthjets->end(); ++jet_itr) {
                const xAOD::Jet* akt10truthjetPtr = *jet_itr;
    
                m_akt10truthjet_pt[i] = akt10truthjetPtr->pt();
                m_akt10truthjet_eta[i] = akt10truthjetPtr->eta();
                m_akt10truthjet_phi[i] = akt10truthjetPtr->phi();
                m_akt10truthjet_e[i] = akt10truthjetPtr->e();
                // do dr matching here
                ++i;
            }
        }
    }

    m_MC_b_from_t_pt     = -999;
    m_MC_b_from_t_eta    = -999;
    m_MC_b_from_t_phi    = -999;
    m_MC_b_from_t_e      = -999;
    m_MC_b_from_t_match  = 0;
    m_MC_b_from_t_jetidx = -1;
    m_MC_b_from_t_recodr = -1;
    m_MC_b_from_t_truthdr= -1;

    m_MC_b_from_t_jet_pt = -999;
    m_MC_b_from_t_jet_eta= -999;
    m_MC_b_from_t_jet_phi= -999;
    m_MC_b_from_t_jet_e  = -999;

    if (m_savePartons) {
        const xAOD::JetContainer* akt4truthjets = nullptr;
        top::check(xaodEvent.retrieve(akt4truthjets, m_akt4truthjetcollection), "FAILURE");
        // after John's new TopAnalysis and TopEvent tags, you can use the following instead:
        //const xAOD::JetContainer *akt4truthjets = event.m_truthJets;
        //change to use John's setup when it is on nightly to avoid breaking package in the
        //mean time

        // the following require latest TopPartons tag
        const xAOD::TopPartonHistoryContainer* topPartonCont = nullptr;
        //top::check(xaodEvent.retrieve(topPartonCont, m_config->sgKeyTopPartonHistory()), "FAILURE"); //m_config is private ...
        top::check(xaodEvent.retrieve(topPartonCont, "TopPartonHistory"), "FAILURE");
        const xAOD::TopPartonHistory *topParton = topPartonCont->at(0);
        

        // get partons
        // b from t
        TLorentzVector b_from_t;
        b_from_t.SetPtEtaPhiM(topParton->MC_b_from_t_pt(), topParton->MC_b_from_t_eta(), topParton->MC_b_from_t_phi(), topParton->MC_b_from_t_m());

        // match parton to truth
        float truth_MC_b_from_t_dr = 999;
        int   truth_MC_b_from_t_idx = -1;
        float reco_MC_b_from_t_dr = 999;
        int   reco_MC_b_from_t_idx = -1;

        i = 0;
        for (xAOD::JetContainer::const_iterator jet_itr = akt4truthjets->begin(); jet_itr != akt4truthjets->end(); ++jet_itr) {
            const xAOD::Jet* akt4truthjetPtr = *jet_itr;
            // cuts on truth jet
            //if (akt4truthjetPtr->pt() < 25e3) {
            //    ++i;
            //    continue;
            //}
            //if (std::fabs(akt4truthjetPtr->eta()) < 2.5) {
            //    ++i;
            //    continue;
            //}

            // check the dr between this parton and the truth jet
            float dr = akt4truthjetPtr->p4().DeltaR(b_from_t);
            if (dr < truth_MC_b_from_t_dr) {
                truth_MC_b_from_t_dr = dr;
                truth_MC_b_from_t_idx = i;
            }

            // do the same for other partons
            // (same as code above for b_from_antit, W quarks, etc

            ++i;
        }
        // in each case, try to match it to reco
        if (truth_MC_b_from_t_idx >= 0) { // it was matched to truth
            // match it to reco
            i = 0;
            for (xAOD::JetContainer::const_iterator jet_itr = event.m_jets.begin(); jet_itr != event.m_jets.end(); ++jet_itr) {
                const xAOD::Jet* jetPtr = *jet_itr;

                // check the dr between this parton's truth jet and the reco jet
                float dr = akt4truthjets->at(truth_MC_b_from_t_idx)->p4().DeltaR(jetPtr->p4());
                if (dr < reco_MC_b_from_t_dr) {
                    reco_MC_b_from_t_dr = dr;
                    reco_MC_b_from_t_idx = i;
                }
                i++;
            }
        }
        m_MC_b_from_t_pt   = b_from_t.Perp();
        m_MC_b_from_t_eta  = b_from_t.Eta();
        m_MC_b_from_t_phi  = b_from_t.Phi();
        m_MC_b_from_t_e    = b_from_t.E();
        m_MC_b_from_t_match= (reco_MC_b_from_t_idx >= 0 && reco_MC_b_from_t_dr < 0.4 && truth_MC_b_from_t_dr < 0.4);
        m_MC_b_from_t_jetidx= reco_MC_b_from_t_idx;
        m_MC_b_from_t_recodr= reco_MC_b_from_t_dr;
        m_MC_b_from_t_truthdr= truth_MC_b_from_t_dr;
        if (m_MC_b_from_t_match) {
          // in principle all the information below is available 
          // from jet_pt[MC_b_from_t_jetidx], jet_eta[MC_b_from_t_jetidx], jet_phi[MC_b_from_t_jetidx] and jet_e[MC_b_from_t_jetidx]
          // so it could be removed, unless it is easier to have it directly as a float
          m_MC_b_from_t_jet_pt = event.m_jets.at(reco_MC_b_from_t_idx)->pt();
          m_MC_b_from_t_jet_eta = event.m_jets.at(reco_MC_b_from_t_idx)->eta();
          m_MC_b_from_t_jet_phi = event.m_jets.at(reco_MC_b_from_t_idx)->phi();
          m_MC_b_from_t_jet_e = event.m_jets.at(reco_MC_b_from_t_idx)->e();
        }
    }

    EventSaverFlatNtuple::saveEvent(event, xaodEvent);
}

}

