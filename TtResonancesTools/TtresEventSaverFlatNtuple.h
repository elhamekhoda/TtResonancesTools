#ifndef TTRESEVENTSAVERFLATNTUPLE_H
#define TTRESEVENTSAVERFLATNTUPLE_H

#include "TopAnalysis/EventSaverFlatNtuple.h"
#include "TLorentzVector.h"
#include "TopEvent/Event.h"

namespace top {

  class TtresEventSaverFlatNtuple : public top::EventSaverFlatNtuple {
    public:
      TtresEventSaverFlatNtuple();

      virtual ~TtresEventSaverFlatNtuple();

      void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches, xAOD::TEvent& xaodEvent);

      void saveEvent(const top::Event& event, xAOD::TEvent& xaodEvent);
      
      void RecoJetMatching(const top::Event& event, const xAOD::Jet* trueJet, float & reco_dr, int & reco_idx); 
            
    private:

      std::string m_ghostjetcollection;
      std::string m_trackjetcollection;
      std::string m_akt4truthjetcollection;
      std::string m_akt10truthjetcollection;
      bool m_saveTruthJets;
      bool m_savePartons;

      std::vector<int>   m_ljet_good;

      std::vector<int>   m_jet_closeToLepton;

      // small-R calo jet trackjet b-tagging information
      std::vector<std::vector<int> > m_jet_ghosttrackjet_idx;
      std::vector<int> m_jet_nghosttrackjet;
      std::vector<int> m_jet_nghosttrackjetb;
      std::vector<int> m_jet_nghosttrackjetbb;
      std::vector<int> m_jet_nghosttrackjetc;
      std::vector<int> m_jet_nghosttrackjetcc;
      std::vector<int> m_jet_nghosttrackjetl;

      // large-R calo jet ghosttrackjet b-tagging information
      std::vector<std::vector<int> > m_ljet_ghosttrackjet_idx;
      std::vector<int> m_ljet_nghosttrackjet;
      std::vector<int> m_ljet_nghosttrackjetb;
      std::vector<int> m_ljet_nghosttrackjetbb;
      std::vector<int> m_ljet_nghosttrackjetc;
      std::vector<int> m_ljet_nghosttrackjetcc;
      std::vector<int> m_ljet_nghosttrackjetl;

      // book track jet info
      std::vector<float> m_trackjet_pt;
      std::vector<float> m_trackjet_eta;
      std::vector<float> m_trackjet_phi;
      std::vector<float> m_trackjet_e;

      std::vector<int> m_trackjet_nghostb;
      std::vector<int> m_trackjet_nghostc;

      // truth jet info
      std::vector<float> m_akt4truthjet_pt;
      std::vector<float> m_akt4truthjet_eta;
      std::vector<float> m_akt4truthjet_phi;
      std::vector<float> m_akt4truthjet_m;

      std::vector<float> m_akt10truthjet_pt;
      std::vector<float> m_akt10truthjet_eta;
      std::vector<float> m_akt10truthjet_phi;
      std::vector<float> m_akt10truthjet_m;

      // Partons 
      float m_MC_b_from_t_pt;
      float m_MC_b_from_t_eta;
      float m_MC_b_from_t_phi;
      float m_MC_b_from_t_m;
      int   m_MC_b_from_t_jetidx;
      float m_MC_b_from_t_recodr;
      float m_MC_b_from_t_truthdr;
      
      float m_MC_b_from_tbar_pt;
      float m_MC_b_from_tbar_eta;
      float m_MC_b_from_tbar_phi;
      float m_MC_b_from_tbar_m;
      int   m_MC_b_from_tbar_jetidx;
      float m_MC_b_from_tbar_recodr;
      float m_MC_b_from_tbar_truthdr;
      
      float m_MC_Wdecay1_from_t_pt;
      float m_MC_Wdecay1_from_t_eta;
      float m_MC_Wdecay1_from_t_phi;
      float m_MC_Wdecay1_from_t_m;
      int   m_MC_Wdecay1_from_t_pdgId;
      int   m_MC_Wdecay1_from_t_jetidx;
      float m_MC_Wdecay1_from_t_recodr;
      float m_MC_Wdecay1_from_t_truthdr;
      
      float m_MC_Wdecay2_from_t_pt;
      float m_MC_Wdecay2_from_t_eta;
      float m_MC_Wdecay2_from_t_phi;
      float m_MC_Wdecay2_from_t_m;
      int   m_MC_Wdecay2_from_t_pdgId;
      int   m_MC_Wdecay2_from_t_jetidx;
      float m_MC_Wdecay2_from_t_recodr;
      float m_MC_Wdecay2_from_t_truthdr;
      
      float m_MC_Wdecay1_from_tbar_pt;
      float m_MC_Wdecay1_from_tbar_eta;
      float m_MC_Wdecay1_from_tbar_phi;
      float m_MC_Wdecay1_from_tbar_m;
      int   m_MC_Wdecay1_from_tbar_pdgId;
      int   m_MC_Wdecay1_from_tbar_jetidx;
      float m_MC_Wdecay1_from_tbar_recodr;
      float m_MC_Wdecay1_from_tbar_truthdr;
      
      float m_MC_Wdecay2_from_tbar_pt;
      float m_MC_Wdecay2_from_tbar_eta;
      float m_MC_Wdecay2_from_tbar_phi;
      float m_MC_Wdecay2_from_tbar_m;
      int   m_MC_Wdecay2_from_tbar_pdgId;
      int   m_MC_Wdecay2_from_tbar_jetidx;
      float m_MC_Wdecay2_from_tbar_recodr;
      float m_MC_Wdecay2_from_tbar_truthdr;
           
      // Matched jets
      float m_MA_b_from_t_pt;
      float m_MA_b_from_t_eta;
      float m_MA_b_from_t_phi;
      float m_MA_b_from_t_m;
      
      float m_MA_b_from_tbar_pt;
      float m_MA_b_from_tbar_eta;
      float m_MA_b_from_tbar_phi;
      float m_MA_b_from_tbar_m;
      
      float m_MA_Wdecay1_from_t_pt;
      float m_MA_Wdecay1_from_t_eta;
      float m_MA_Wdecay1_from_t_phi;
      float m_MA_Wdecay1_from_t_m;

      float m_MA_Wdecay2_from_t_pt;
      float m_MA_Wdecay2_from_t_eta;
      float m_MA_Wdecay2_from_t_phi;
      float m_MA_Wdecay2_from_t_m;
            
      float m_MA_Wdecay1_from_tbar_pt;
      float m_MA_Wdecay1_from_tbar_eta;
      float m_MA_Wdecay1_from_tbar_phi;
      float m_MA_Wdecay1_from_tbar_m;

      float m_MA_Wdecay2_from_tbar_pt;
      float m_MA_Wdecay2_from_tbar_eta;
      float m_MA_Wdecay2_from_tbar_phi;
      float m_MA_Wdecay2_from_tbar_m;
      
      // Reconstructed particles from the matched jets
      float m_MA_W_from_t_pt;
      float m_MA_W_from_t_eta;
      float m_MA_W_from_t_phi;
      float m_MA_W_from_t_m;
      
      float m_MA_W_from_tbar_pt;
      float m_MA_W_from_tbar_eta;
      float m_MA_W_from_tbar_phi;
      float m_MA_W_from_tbar_m;
            
      float m_MA_t_pt;
      float m_MA_t_eta;
      float m_MA_t_phi;
      float m_MA_t_m;
      
      float m_MA_tbar_pt;
      float m_MA_tbar_eta;
      float m_MA_tbar_phi;
      float m_MA_tbar_m;
      
      float m_MA_ttbar_pt;
      float m_MA_ttbar_eta;
      float m_MA_ttbar_phi;
      float m_MA_ttbar_m;  
           
      ClassDef(TtresEventSaverFlatNtuple, 0);
  };

}

#endif

