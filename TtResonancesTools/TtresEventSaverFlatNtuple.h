#ifndef TTRESEVENTSAVERFLATNTUPLE_H
#define TTRESEVENTSAVERFLATNTUPLE_H

#include "TopAnalysis/EventSaverFlatNtuple.h"

namespace top {

  class TtresEventSaverFlatNtuple : public top::EventSaverFlatNtuple {
    public:
      TtresEventSaverFlatNtuple();

      virtual ~TtresEventSaverFlatNtuple();

      void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches, xAOD::TEvent& xaodEvent);

      void saveEvent(const top::Event& event, xAOD::TEvent& xaodEvent);

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
      std::vector<float> m_akt4truthjet_e;

      std::vector<float> m_akt10truthjet_pt;
      std::vector<float> m_akt10truthjet_eta;
      std::vector<float> m_akt10truthjet_phi;
      std::vector<float> m_akt10truthjet_e;

      float m_MC_b_from_t_pt;
      float m_MC_b_from_t_eta;
      float m_MC_b_from_t_phi;
      float m_MC_b_from_t_e;
      int   m_MC_b_from_t_match;
      int   m_MC_b_from_t_jetidx;
      float m_MC_b_from_t_recodr;
      float m_MC_b_from_t_truthdr;

      float m_MC_b_from_t_jet_pt;
      float m_MC_b_from_t_jet_eta;
      float m_MC_b_from_t_jet_phi;
      float m_MC_b_from_t_jet_e;


      ClassDef(TtresEventSaverFlatNtuple, 0);
  };

}

#endif

