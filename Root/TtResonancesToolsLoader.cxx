#include "TtResonancesTools/TtResonancesToolsLoader.h"

#include "TtResonancesTools/NLargeJetTtresSLSelector.h"
#include "TtResonancesTools/NLargeJetTtresAHSelector.h"
#include "TtResonancesTools/NJetCloseLeptonSelector.h"

#include <iostream>

#include "TFile.h"

namespace top {

top::EventSelectorBase* TtResonancesToolsLoader::initTool(const std::string& name, const std::string& line, TFile* outputFile, EL::Worker* wk) {
    //get the first bit of the string and store it in toolname
    std::istringstream iss(line);
    std::string toolname;
    getline(iss, toolname, ' ');

    //any parameters?
    std::string param;
    if (line.size() > toolname.size())
        param = line.substr(toolname.size() + 1);

    if (toolname == "LARGEJETTTRESSL_N")
        return new top::NLargeJetTtresSLSelector(param);
    else if (toolname == "LARGEJETTTRESAH_N")
        return new top::NLargeJetTtresAHSelector(param);
    else if (toolname == "JETCLOSELEPTON_N")
        return new top::NJetCloseLeptonSelector(param);

    return nullptr;
}

}
