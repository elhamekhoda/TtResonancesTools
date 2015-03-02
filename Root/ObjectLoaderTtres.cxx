#include "TtResonancesTools/ObjectLoaderTtres.h"

#include "TopConfiguration/TopConfig.h"

#include "TopObjectSelectionTools/TopObjectSelection.h"

#include "TopObjectSelectionTools/ElectronLikelihoodDC14.h"
#include "TopObjectSelectionTools/ElectronCutBasedDC14.h"
#include "TopObjectSelectionTools/MuonDC14.h"

#include "TopObjectSelectionTools/IsolationTools.h"
#include "TtResonancesTools/ElectronTtres.h"
#include "TtResonancesTools/MuonTtres.h"
#include "TtResonancesTools/JetTtres.h"
#include "TtResonancesTools/FirstOverlapRemovalIndicesTtres.h"
#include "TtResonancesTools/OverlapRemovalIndicesTtres.h"

namespace top {

top::TopObjectSelection* ObjectLoaderTtres::init(top::TopConfig* topConfig) {
    top::TopObjectSelection* objectSelection = new top::TopObjectSelection(topConfig);

    // cut based is tt resonances default, but use the top standard one if the user wants LH (but with mini isolation)
    if (topConfig->electronID().find("LH") == std::string::npos && topConfig->electronIDLoose().find("LH") == std::string::npos) {
        //both the tight and loose user settings do not contain LH -> cut based
        objectSelection->electronSelection(new top::ElectronTtres(topConfig->electronPtcut(), topConfig->electronVetoLArCrack(), topConfig->electronID(), topConfig->electronIDLoose(), new top::RelativePTVarCone(20, 0.05, 20, 99.)));
    } else if (topConfig->electronID().find("LH") == 0 && topConfig->electronIDLoose().find("LH") == 0) {
        //user wants likelihood electrons
        LikeEnum::Menu operatingPoint = top::ElectronLikelihoodDC14::textToEgammaEnum(topConfig->electronID());
        LikeEnum::Menu operatingPointLoose = top::ElectronLikelihoodDC14::textToEgammaEnum(topConfig->electronIDLoose());
        objectSelection->electronSelection(new top::ElectronLikelihoodDC14(topConfig->electronPtcut(), topConfig->electronVetoLArCrack(), operatingPoint, operatingPointLoose, new top::RelativePTVarCone(20, 0.05, 20, 99.)));
    } else {
        std::cout << "\nHo hum\n";
        std::cout << "Not sure it makes sense to use a mix of LH and cut-based electrons for the tight/loose definitions\n";
        std::cout << "Tight electron definition is " << topConfig->electronID() << "\n";
        std::cout << "Loose electron definition is " << topConfig->electronIDLoose() << "\n";
        std::cout << "If it does make sense, feel free to fix this\n";
        exit(1);
    }

    objectSelection->muonSelection(new top::MuonTtres(25000., 2.5, 3.0, new top::RelativePTVarCone(20, 0.05, 20, 99.)));

    objectSelection->jetSelection(new top::JetTtres(25000., 2.5, 0.5, "GhostAntiKt3TrackJet"));
    objectSelection->largeJetSelection(new top::JetTtres(200000., 2., 0., "GhostAntiKt3TrackJet"));

    objectSelection->overlapRemovalPreSelection(new top::FirstOverlapRemovalIndicesTtres());
    objectSelection->overlapRemovalPostSelection(new top::OverlapRemovalIndicesTtres());

    return objectSelection;
}

}


