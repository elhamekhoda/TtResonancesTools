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

      std::vector<int>   m_ljet_good;

      std::vector<int>   m_jet_closeToLepton;

      ClassDef(TtresEventSaverFlatNtuple, 0);
  };

}

#endif

