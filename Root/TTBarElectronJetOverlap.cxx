#include "TtResonancesTools/TTBarElectronJetOverlap.h"

#include <iostream>
#include <cmath>

#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"


using namespace std;

void TTBarElectronJetOverlap::Load(xAOD::JetContainer *jets, xAOD::ElectronContainer *electrons) {
    m_jets = jets;
    m_electrons = electrons;

    size_t se = m_electrons->size();
    fElClTLVs.resize(se);
    fElTLVs.resize(se);
    fElGood.resize(se);

    size_t sj = m_jets->size();
    fJetTLVs.resize(sj);
    fJetJVFs.resize(sj);
    fJetD3PDTrkPtSums.resize(sj);
    fJetD3PDTrkPtPVSums.resize(sj);

    for (size_t i = 0; i < sj; i++) {
      fJetTLVs[i].SetPtEtaPhiE(m_jets->at(i)->pt(), m_jets->at(i)->eta(), m_jets->at(i)->phi(), m_jets->at(i)->e());
      std::vector<float> JVF = m_jets->at(i)->getAttribute<std::vector<float> >("JVF");
      fJetJVFs[i] = JVF.size() > 0 ? JVF[0] : -1; // (TODO) NOTA BENE: Assumes PV is the first vertex
      std::vector<float> trkPtSumVec = m_jets->at(i)->getAttribute<std::vector<float> >("SumPtTrkPt500");
      float trkPtSum = trkPtSumVec.size() > 0 ? trkPtSumVec[0] : 0; // (TODO) NOTA BENE: Assumes PV is the first vertex
      fJetD3PDTrkPtSums[i] = fJetJVFs[i] ? trkPtSum/JVF[0] : -1;
      fJetD3PDTrkPtPVSums[i] = trkPtSum;
    }

    for (size_t i = 0; i < se; i++) {
        fElGood[i] = m_electrons->at(i)->auxdata<unsigned int>("passPreORSelection");
        if (!fElGood[i]) continue;

        fElClTLVs[i].SetPtEtaPhiM(m_electrons->at(i)->caloCluster()->e()/std::cosh(m_electrons->at(i)->caloCluster()->eta()),
                m_electrons->at(i)->caloCluster()->eta(), m_electrons->at(i)->caloCluster()->phi(), 0.511);
        //const ElementLink<xAOD::TrackParticleContainer> origTrackLink = electrons->at(i)->trackParticle()->auxdata< ElementLink<xAOD::TrackParticleContainer> >("originalTrackParticle");
        fElTLVs[i].SetPtEtaPhiM(m_electrons->at(i)->caloCluster()->e()/std::cosh(m_electrons->at(i)->trackParticle()->eta()),
                                m_electrons->at(i)->trackParticle()->eta(), m_electrons->at(i)->trackParticle()->phi(), 0.511);
    }
}

void TTBarElectronJetOverlap::FindAssocEls() {
    size_t nJets = m_jets->size();
    fJetAssocElCls = vector<set<int> >(nJets);

    size_t nEls = m_electrons->size();
    fElClAssocJet = vector<int>(nEls, -1);

    // find the associated electron clusters in each jet
    double drmin, dr;
    TLorentzVector elcl, jet;
    for (size_t z = 0 ; z < nEls; ++z) {
        if (!fElGood[z]) continue;

        elcl = fElClTLVs[z];
        drmin = 0.4;
        int drmin_idx = -1;
        for (size_t y = 0 ; y < nJets; ++y) {
            jet = fJetTLVs[y];
            dr = elcl.DeltaR(jet);

            // attempt to match the jet to the electron.
            if (dr < drmin) {
                drmin = dr;
                drmin_idx = y;
            }
        }

        if (drmin_idx == -1)
            continue;

        fJetAssocElCls[drmin_idx].insert(z);
        fElClAssocJet[z] = drmin_idx;
    }
}

void TTBarElectronJetOverlap::SubtractEls() {
    size_t nJets = m_jets->size();
    int ElIdx;
    for (size_t iJet = 0; iJet < nJets; iJet++) {
        for (set<int>::iterator iEl = fJetAssocElCls[iJet].begin();
                iEl != fJetAssocElCls[iJet].end(); iEl++) {
            ElIdx = *iEl;
            TLorentzVector elcorr = fElTLVs[ElIdx];
            fJetTLVs[iJet] -= elcorr;
            //m_jets->at(iJet).setP4(xAOD::JetFourMom_t(jet.Perp(), jet.Eta(), jet.Phi(), jet.M()));
        }
    }
}

void TTBarElectronJetOverlap::FindGoodObjects() {
    size_t nEls = m_electrons->size();
    fGoodEls = vector<bool>(nEls, true);

    size_t nJets = fJetTLVs.size();
    vector<TLorentzVector> TmpJetTLVs = fJetTLVs;

    TLorentzVector el, jet;
    for (size_t iEl = 0; iEl < nEls; iEl++) {
        if (!fElGood[iEl]) continue;

        el = fElTLVs[iEl];

        if (fDebug) {
            cout << "El # " << iEl <<
                " Pt Eta Phi: " <<
                el.Pt() << " " <<
                el.Eta() << " " <<
                el.Phi() << endl;
        }

        for (size_t iJet = 0; iJet < nJets; iJet++) {
            jet = fJetTLVs[iJet];

            if (fDebug) {
                cout << "  Jet # " << iJet <<
                    " Pt Eta Phi M: " <<
                    jet.Pt() << " " <<
                    jet.Eta() << " " <<
                    jet.Phi() << " " <<
                    jet.M() << endl;
            }

            if (jet.Pt() < 25e3)
                continue;

            // if the electron is too close to a jet...
            if (jet.DeltaR(el) < 0.2) {

                if (fDebug)
                    cout << "    El too close to jet. Removing." << endl;

                // remove from good electrons list.
                fGoodEls[iEl] = false;

                if (fElClAssocJet[iEl] >= 0) {
                    // add electron 4-vector back to jet.
                    TmpJetTLVs[fElClAssocJet[iEl]] += el; 

                    // remove this electron from the association.
                    fJetAssocElCls[iJet].erase(iEl);
                }
            }
        }
    }

    fJetTLVs = TmpJetTLVs;

    fGoodJets.resize(nJets);
    for (size_t iJet = 0; iJet < nJets; iJet++)
        fGoodJets[iJet] = fJetTLVs[iJet].Pt() > 25e3;

}

void TTBarElectronJetOverlap::RecalcJVF() {

    size_t nJets = m_jets->size();
    int ElIdx;
    //int TrkIdx;
    TLorentzVector trk;

    for (size_t iJet = 0; iJet < nJets; iJet++) {

        // if jvf == 0 or -1, no need to recalulate...
        if (!fJetJVFs[iJet] ||
                fJetJVFs[iJet] < 0)
            continue;

        for (set<int>::iterator iEl = fJetAssocElCls[iJet].begin();
                iEl != fJetAssocElCls[iJet].end(); iEl++) {

            ElIdx = *iEl;

            trk.SetPtEtaPhiE(m_electrons->at(ElIdx)->trackParticle()->pt(),
                             m_electrons->at(ElIdx)->trackParticle()->eta(), m_electrons->at(ElIdx)->trackParticle()->phi(), m_electrons->at(ElIdx)->trackParticle()->e());

            // not in the associated tracks.
            bool foundMatch = false;
            std::vector<const xAOD::TrackParticle*> jetTracks;
            //bool haveJetTracks = m_jets->at(iJet)->getAssociatedObjects(xAOD::JetAttribute::GhostTrack, jetTracks);
            for (size_t t = 0; t < jetTracks.size(); ++t) {
                TLorentzVector jet_trk;
                jet_trk.SetPtEtaPhiE(jetTracks[t]->pt(), jetTracks[t]->eta(), jetTracks[t]->phi(), jetTracks[t]->e());
                if (jet_trk.DeltaR(trk) < 0.01) {
                    foundMatch = true;
                }
            }

            if (!foundMatch)
                continue;

            // recompute JVF.
            fJetD3PDTrkPtSums[iJet] -= trk.Pt();

            if (std::fabs(std::sin(m_electrons->at(ElIdx)->trackParticle()->theta())*m_electrons->at(ElIdx)->trackParticle()->z0()) < 1.0 &&
                std::fabs(m_electrons->at(ElIdx)->trackParticle()->d0()) < 1.0)
                fJetD3PDTrkPtPVSums[iJet] -= trk.Pt();
        }

        // we subtracted too much for some reason?
        if (fJetD3PDTrkPtSums[iJet] < 0 ||
                fJetD3PDTrkPtPVSums[iJet] < 0)
            fJetJVFs[iJet] = 0;
        // no tracks associated with the jet.
        else if (fJetD3PDTrkPtSums[iJet] == 0)
            fJetJVFs[iJet] = -1;
        // all good. recalculate JVF.
        else
            fJetJVFs[iJet] = fJetD3PDTrkPtPVSums[iJet]/fJetD3PDTrkPtSums[iJet];
    }
}

void TTBarElectronJetOverlap::AnalyzeEvent() {
    FindAssocEls();
    SubtractEls();
    FindGoodObjects();
    RecalcJVF();

    // put the results back in place
    size_t se = m_electrons->size();
    size_t sj = m_jets->size();
    for (size_t i = 0; i < sj; i++) {
        m_jets->at(i)->setJetP4(xAOD::JetFourMom_t(fJetTLVs[i].Perp(), fJetTLVs[i].Eta(), fJetTLVs[i].Phi(), fJetTLVs[i].M()));
        std::vector<float> newJVF;
        newJVF.push_back(fJetJVFs[i]);
        m_jets->at(i)->setAttribute<std::vector<float> >("JVF", newJVF);
    }
    for (size_t i = 0, j = 0; j < se; i++, j++) {
        if (!fGoodEls[j] || !fElGood[j]) {
          // do not remove the electron here
          // it is a shallow copy!
          m_electrons->at(i)->auxdecor<int>("PassElJetOR") = 0;
          // remove electron
          //m_electrons->erase(m_electrons->begin() + i);
          //i--;
       } else {
          m_electrons->at(i)->auxdecor<int>("PassElJetOR") = 1;
       }
    }
}

