#ifndef CHI2SELECTOR_H
#define CHI2SELECTOR_H

#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TopEvent/Event.h"

#include "TopEventReconstructionTools/TtresNeutrinoBuilder.h"
#include "TtResonancesTools/TtresChi2.h"

#include "TopEventSelectionTools/SignValueSelector.h"

namespace top {

class Chi2Selector : public SignValueSelector {
  public:
    explicit Chi2Selector(const std::string& params);

     /**
     * @brief Tool used to select the right jet combination in the resolve regime
     *
     * @param event The event to perform the operations on.
     
     * @return True if the log10(chi2)<0.9, false otherwise.
     */
     
    bool apply(const top::Event& event) const override;

  private:
    float m_Units;

    TtresNeutrinoBuilder * m_neutrinoBuilder;
    TtresChi2 * m_chi2;
};

}//namespace top 

#endif

