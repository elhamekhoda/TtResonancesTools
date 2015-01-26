#ifndef NLARGEJETTTRESSLSELECTOR_H_
#define NLARGEJETTTRESSLSELECTOR_H_

#include "TopEventSelectionTools/SignValueSelector.h"

namespace top {

/**
 * @brief Does some stuff
 */
class NLargeJetTtresSLSelector : public SignValueSelector {
public:
    explicit NLargeJetTtresSLSelector(const std::string& params);

    /**
     * @brief Write a description ;)
     *
     * @param event The event to perform the operations on.
     * @return True if the event passes the selection, false otherwise.
     */
     bool apply(const top::Event& event) const override;
};

}

#endif
