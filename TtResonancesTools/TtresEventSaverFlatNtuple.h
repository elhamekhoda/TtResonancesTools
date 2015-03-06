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



      ClassDef(TtresEventSaverFlatNtuple, 0);
  };

}

#endif

