// $Id: OverlapRemovalIndicesTtres.h 639409 2015-01-14 12:56:37Z simon $
#ifndef ANALYSISTOP_TOPOBJECTSELECTONTOOLS_OVERLAPREMOVALINDICESTTRES_H
#define ANALYSISTOP_TOPOBJECTSELECTONTOOLS_OVERLAPREMOVALINDICESTTRES_H

/**
  * @author Danilo Ferreira de Lima  <dferreir@cern.ch>
  * 
  * @brief OverlapRemovalIndicesTtres
  *   Do overlap removal based on selected indices
  * 
  * $Revision: 639409 $
  * $Date: 2015-01-14 12:56:37 +0000 (Wed, 14 Jan 2015) $
  * 
  **/ 

#include "TopObjectSelectionTools/OverlapRemovalBase.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"

namespace top {

class OverlapRemovalIndicesTtres : public top::OverlapRemovalBase {
public:
    OverlapRemovalIndicesTtres();
    virtual ~OverlapRemovalIndicesTtres(){}

    virtual void overlapremoval(const xAOD::ElectronContainer* el,
                                const xAOD::MuonContainer* mu,
                                const xAOD::JetContainer* jet,
                                const xAOD::JetContainer* ljet,
				const xAOD::TauJetContainer* tau ,
				const xAOD::PhotonContainer* photon,
                                std::shared_ptr<std::vector<unsigned int>> OUT_el,
                                std::shared_ptr<std::vector<unsigned int>> OUT_mu,
                                std::shared_ptr<std::vector<unsigned int>> OUT_jet,
                                std::shared_ptr<std::vector<unsigned int>> OUT_ljet,
				std::shared_ptr<std::vector<unsigned int>>  OUT_tau,
				std::shared_ptr<std::vector<unsigned int>>  OUT_photon,
                                const bool isLoose);
                               
    virtual void print(std::ostream&) const;
};

}
#endif  
