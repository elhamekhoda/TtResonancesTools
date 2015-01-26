#ifndef ANALYSISTOP_TOPOBJECTSELECTONTOOLS_FIRSTOVERLAPREMOVALINDICESTTRES_H
#define ANALYSISTOP_TOPOBJECTSELECTONTOOLS_FIRSTOVERLAPREMOVALINDICESTTRES_H

/**
  * @author Danilo Ferreira de Lima  <dferreir@cern.ch>
  * 
  * @brief FirstOverlapRemovalIndicesTtres
  *   Do overlap removal based on selected indices
  * 
  * $Revision: 639409 $
  * $Date: 2015-01-14 12:56:37 +0000 (Wed, 14 Jan 2015) $
  * 
  **/ 

// system include(s):
#include <memory>
#include <vector>

// EDM include(s):
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODJet/JetContainer.h"

#include "TopObjectSelectionTools/OverlapRemovalBase.h"
#include "TtResonancesTools/TTBarElectronJetOverlap.h"

namespace top {

class FirstOverlapRemovalIndicesTtres : public OverlapRemovalBase {
public:
    FirstOverlapRemovalIndicesTtres();
    virtual ~FirstOverlapRemovalIndicesTtres() {}

    virtual void overlapremoval(xAOD::ElectronContainer* el,
            xAOD::MuonContainer* mu,
            xAOD::JetContainer* jet,
            xAOD::JetContainer* ljet,
            std::shared_ptr<std::vector<unsigned int>> OUT_el,
            std::shared_ptr<std::vector<unsigned int>> OUT_mu,
            std::shared_ptr<std::vector<unsigned int>> OUT_jet,
            std::shared_ptr<std::vector<unsigned int>> OUT_ljet);

    virtual void print(std::ostream&) const;

private:
    TTBarElectronJetOverlap m_o;
};

}
#endif  
