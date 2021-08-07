# TtResonancesTools

This tool is used for the ChiSquar-based reconstruction of the resolved $t\bar{t}$ final state in semi-leptonic channel. The calculated minimum ChiSquared values are used to select events.

In order to apply the ChiSquare selector use `LOG10_CHI2` config option.
Currently used: `LOG10_CHI2 < 0.9`

## Current Defaults:
* b-tagging done on the PFlow jets checking the `isbtagged` decorators.
* WP used: `DL1r_FixedCutBEff_77`


## Limitations:
* The b-tagging WP is hard coded inside `Chi2Selector.cxx`.
* Need to change the source code in order to change the b-tagging strategy: track jet vs PFlow jets, b-tagging WP.

## ToDOs:
1. Make the tool configurable such that the user can choose the b-tagging strategy and WP.