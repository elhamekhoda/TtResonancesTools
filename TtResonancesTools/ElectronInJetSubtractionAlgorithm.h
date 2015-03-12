// $Id$
#ifndef ANALYSISTOP_TTRESONANCESTOOLS_ELECTRONINJETSUBTRACTIONALGORITHM_H
#define ANALYSISTOP_TTRESONANCESTOOLS_ELECTRONINJETSUBTRACTIONALGORITHM_H

#include "xAODEgamma/ElectronContainer.h"
#include "xAODJet/JetContainer.h"

namespace top{
  class ElectronInJetSubtractionAlgorithm final {
    public:
      ElectronInJetSubtractionAlgorithm();
      virtual ~ElectronInJetSubtractionAlgorithm(){}
      
      ElectronInJetSubtractionAlgorithm(const ElectronInJetSubtractionAlgorithm& rhs) = delete;
      ElectronInJetSubtractionAlgorithm(ElectronInJetSubtractionAlgorithm&& rhs) = delete;
      ElectronInJetSubtractionAlgorithm& operator=(const ElectronInJetSubtractionAlgorithm& rhs) = delete; 
      
      inline void setDoLooseCuts() {m_doLooseCuts = true;}
      
      void apply( xAOD::ElectronContainer* electrons , xAOD::JetContainer* jets );
      
    private:
      bool m_doLooseCuts;
      // Pass selection strings
      const std::string m_passPreORSelection;
      const std::string m_passPreORSelectionLoose;      
  };
}

#endif
