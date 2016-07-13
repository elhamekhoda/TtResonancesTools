#include "TtResonancesTools/Chi2Selector.h"
#include "TopEvent/Event.h"
#include "TLorentzVector.h"
#include <vector>

namespace top {

Chi2Selector::Chi2Selector(const std::string& params) : SignValueSelector("LOG10_CHI2", params) {

  std::string units = "MeV";  
  m_chi2 = new TtresChi2(units);
  m_chi2->Init(TtresChi2::DATA2015_MC15C);
  std::cout << "Chi2Selector is going to use mv2c10> 0.6455 to get the b-tagging information" << std::endl;
   
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
  if      (event.m_electrons.size()==1 && event.m_muons.size()==0)  	lepton = event.m_electrons.at(0)->p4();
  else if (event.m_electrons.size()==0 && event.m_muons.size()==1)	lepton = event.m_muons.at(0)->p4();    
  else return false;
  
  //jets     
  for (size_t z = 0; z < event.m_jets.size(); ++z) {
      vjets.push_back(new TLorentzVector());
      vjets[z]->SetPtEtaPhiE(event.m_jets[z]->pt(), event.m_jets[z]->eta(), event.m_jets[z]->phi(), event.m_jets[z]->e());      
      /*
      double mv2c20_discriminant = 0.;
      const bool hasMv2c20 = event.m_jets[z]->btagging()->MVx_discriminant("MV2c20", mv2c20_discriminant);
      vjets_btagged.push_back( hasMv2c20 && mv2c20_discriminant>-0.0436); 
      */
      bool is_btagged(false);
      for (size_t bidx = 0; bidx < event.m_trackJets.size(); ++bidx)
       {
        TLorentzVector tmpTJet;
        tmpTJet.SetPtEtaPhiE(event.m_trackJets[bidx]->pt(),event.m_trackJets[bidx]->eta(),event.m_trackJets[bidx]->phi(),
                             event.m_trackJets[bidx]->e());

        if(tmpTJet.DeltaR(*vjets[z]) <= 0.4) {
        double mv2c10_discriminant = 0.;
        const bool hasMv2c10 = event.m_jets[z]->btagging()->MVx_discriminant("MV2c10", mv2c10_discriminant);
        if(hasMv2c10 && mv2c10_discriminant> 0.6455)
        is_btagged = true;
        break; 
        } // if(tmpTJet.DeltaR(*vjets[z]) <= 0.4) 
      } // for (size_t bidx = 0; bidx < evt.tjet().size(); ++bidx) 

      vjets_btagged.push_back(is_btagged);

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
