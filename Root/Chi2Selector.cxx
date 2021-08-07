#include "TtResonancesTools/Chi2Selector.h"
#include "TopEvent/Event.h"
#include "TLorentzVector.h"
#include <vector>
#include "xAODBTaggingEfficiency/BTaggingEfficiencyTool.h"
#include "xAODBTaggingEfficiency/BTaggingSelectionTool.h"

namespace top {

    Chi2Selector::Chi2Selector(const std::string& params) : SignValueSelector("LOG10_CHI2", params) {

        std::string units = "MeV";  
        m_chi2 = new TtresChi2(units);
        // using PFlow jets for b-tagging
        m_chi2->Init(TtresChi2::DATA_MC_Run2_CaloJET);

    }//Chi2Selector::Chi2Selector


    bool Chi2Selector::apply(const top::Event& event) const {

        // inputs 
        // LEPTON --> TLorentzVector for your lepton
        // vjets -->  std::vector<TLorentzVector*> for the jets
        // vjets_btagged --> std::vector<bool> to say if the jets are btagged or not
        // met --> TLorentzVector for your MET

        int igj3, igj4; // index for the Whad
        int igb3, igb4; // index for the b's
        int ign1;       // index for the neutrino (because chi2 can test both pz solution)
        double chi2ming1, chi2ming1H, chi2ming1L;

        std::vector<TLorentzVector *> vjets;
        std::vector<bool> vjets_btagged;

        //leptons
        TLorentzVector lepton;
        if      (event.m_electrons.size()==1 && event.m_muons.size()==0)    lepton = event.m_electrons.at(0)->p4();
        else if (event.m_electrons.size()==0 && event.m_muons.size()==1)    lepton = event.m_muons.at(0)->p4();
        else return false;

        //b-tagging on pflow jets
        for (size_t z = 0; z < event.m_jets.size(); ++z) {

            bool isbtag_calojet(false);

            vjets.push_back(new TLorentzVector());
            vjets[z]->SetPtEtaPhiE(event.m_jets[z]->pt(), event.m_jets[z]->eta(), event.m_jets[z]->phi(), event.m_jets[z]->e());
            if (event.m_jets[z]->isAvailable<char>("isbtagged_DL1r_FixedCutBEff_77")){
                if (event.m_jets[z]->auxdataConst<char>("isbtagged_DL1r_FixedCutBEff_77")){
                    isbtag_calojet =  true;
                }
            }
            vjets_btagged.push_back(isbtag_calojet);

            // // b-tagging on the track-jet

            // bool is_btagged(false);
            // for (size_t bidx = 0; bidx < event.m_trackJets.size(); ++bidx)
            //  {
            //   TLorentzVector tmpTJet;
            //   tmpTJet.SetPtEtaPhiE(event.m_trackJets[bidx]->pt(),event.m_trackJets[bidx]->eta(),event.m_trackJets[bidx]->phi(),event.m_trackJets[bidx]->e());
            //   int isbtag_tjet = 0;
            //   if (event.m_trackJets[bidx]->isAvailable<char>("isbtagged_DL1r_FixedCutBEff_77")){
            //     isbtag_tjet = event.m_trackJets[bidx]->auxdataConst<char>("isbtagged_DL1r_FixedCutBEff_77");
            //   }
            //   if(tmpTJet.DeltaR(*vjets[z]) <= 0.4 && isbtag_tjet == 1) {
            //       is_btagged = true;
            //       break;
            //   } // if(tmpTJet.DeltaR(*vjets[z]) <= 0.4) 
            // } // for (size_t bidx = 0; bidx < evt.tjet().size(); ++bidx) 

            // vjets_btagged.push_back(is_btagged);
        }//for

        //met
        TLorentzVector met;
        met.SetPtEtaPhiM(event.m_met->met(), 0, event.m_met->phi(), 0);

        //chi2 algorithm
        bool status = m_chi2->findMinChiSquare(&lepton, &vjets, &vjets_btagged, &met, igj3, igj4, igb3, igb4, ign1, chi2ming1, chi2ming1H, chi2ming1L); 

        float chi2Value = 999;
        if (status) chi2Value = chi2ming1;

        //delete pointers
        for (size_t z = 0; z < vjets.size(); ++z)	delete vjets[z];  
        vjets.clear();
        vjets_btagged.clear();

        //if (status) mtt = m_chi2->getResult_Mtt();
        return checkFloat(log10(chi2Value), value());

    }//Chi2Selector::apply

}//namespace
