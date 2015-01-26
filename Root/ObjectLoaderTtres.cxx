#include "TtResonancesTools/ObjectLoaderTtres.h"

#include "TopConfiguration/TopConfig.h"

#include "TopObjectSelectionTools/TopObjectSelection.h"

#include "TtResonancesTools/ElectronTtres.h"
#include "TtResonancesTools/MuonTtres.h"
#include "TopObjectSelectionTools/JetDC14.h"
#include "TtResonancesTools/FirstOverlapRemovalIndicesTtres.h"
#include "TtResonancesTools/OverlapRemovalIndicesTtres.h"

namespace top {

top::TopObjectSelection* ObjectLoaderTtres::init(top::TopConfig* topConfig) {
    top::TopObjectSelection* objectSelection = new top::TopObjectSelection(topConfig);

    objectSelection->electronSelection(new top::ElectronTtres(topConfig->electronPtcut(), topConfig->electronVetoLArCrack(), topConfig->electronID(), topConfig->electronIDBkg()));
    objectSelection->muonSelection(new top::MuonTtres(25000., 2.5));
    objectSelection->jetSelection(new top::JetDC14(25000., 2.5, 0.5));
    objectSelection->largeJetSelection(new top::JetDC14(300000., 2., 0.));

    objectSelection->overlapRemovalPreSelection(new top::FirstOverlapRemovalIndicesTtres());
    objectSelection->overlapRemovalPostSelection(new top::OverlapRemovalIndicesTtres());

    return objectSelection;
}

}


