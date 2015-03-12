// $Id$
#include "TtResonancesTools/ElectronInJetSubtractionAlgorithm.h"

#include <iostream>

namespace top{
  
  ElectronInJetSubtractionAlgorithm::ElectronInJetSubtractionAlgorithm() :
    m_doLooseCuts(false),
    m_passPreORSelection("passPreORSelection"),
    m_passPreORSelectionLoose("passPreORSelectionLoose")  
  {
    
  }
  
  void ElectronInJetSubtractionAlgorithm::apply( xAOD::ElectronContainer* electrons , xAOD::JetContainer* jets )
  {
    unsigned int passedElectrons(0);
    for (auto e : *electrons) {
      if (e->auxdataConst<char>(m_passPreORSelection) == 1) {
        ++passedElectrons;
      }
    }
    
    std::cout<<"Total number of electrons = "<<electrons->size()<<" that pass cuts = "<<passedElectrons<<" :: Total number of jets = "<<jets->size()<<std::endl;
    
  }
  
}
