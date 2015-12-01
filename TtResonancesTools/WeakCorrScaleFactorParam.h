#ifndef WEAKCORRSCALEFACTORPARAM_H
#define WEAKCORRSCALEFACTORPARAM_H
// weak corrections for powheg ttbar MC
// using parametrisations based on the HATHOR
// implementation of calculations from J. Kuehn, P. Uwer

// if using this code, please cite:
// * J. H. Kuehn, A. Scharf and P. Uwer,
//    "Electroweak corrections to top-quark pair production in quark-antiquark annihilation",
//     Eur.Phys.J. C45, 139 (2006), hep-ph/0508092.
// * J. H. Kuehn, A. Scharf and P. Uwer, 
//     "Electroweak effects in top-quark pair production at hadron colliders”, 
//     Eur.Phys.J. C51, 37 (2007), hep-ph/0610335.
// * J. Kuehn, A. Scharf and P. Uwer, 
//     "Weak Interactions in Top-Quark Pair Production at Hadron Colliders: An Update”,
//     arxiv:1305.5773.
// * G. van Oldenborgh, "FF: A Package to evaluate one loop Feynman diagrams",
//     Comput.Phys.Commun. 66, 1 (1991).
// * M. Luscher,
//     "A Portable high quality random number generator for lattice field theory simulations",
//     Comput.Phys.Commun. 79, 100 (1994), hep-lat/9309020.
// * G. P. Lepage, "A New Algorithm for Adaptive Multidimensional Integration",
//     J.Comput.Phys. 27, 192 (1978).
// * G. P. Lepage, "VEGAS: AN ADAPTIVE MULTIDIMENSIONAL INTEGRATION PROGRAM".


// #include "Hathor.h"
#include "TH2F.h"
#include "ScaleFactor.h"
#include <vector>

// class Hathor;
// class Lhapdf;
namespace WeakCorr {

class WeakCorrScaleFactorParam {
  
public:
    enum InitialStateType {
        Undefined,
        UU,
        DD,
        GG,
        GD,
        GU
    };
    WeakCorrScaleFactorParam(TString mapfile="EWcorr_param.root");    
    ~WeakCorrScaleFactorParam();
    ScaleFactor getScaleFactor(const double& shat, const double& z, const int& type);
    ScaleFactor getScaleFactor(
        float& MC_t_pt,
        float& MC_t_eta,
        float& MC_t_phi,
        float& MC_t_m,
        float& MC_tbar_pt,
        float& MC_tbar_eta,
        float& MC_tbar_phi,
        float& MC_tbar_m,
        int& type);
    double getWeight(const double& shat, const double& z, const int& type);
    double getWeight(
        float& MC_t_pt,
        float& MC_t_eta,
        float& MC_t_phi,
        float& MC_t_m,
        float& MC_tbar_pt,
        float& MC_tbar_eta,
        float& MC_tbar_phi,
        float& MC_tbar_m,
        int& type);
private:
    bool init();
//     Lhapdf m_pdf;
    // use pointer here to ease dictionary creation:
//     Hathor* m_weak;
    bool init(TString mapfile);
    TH2F* m_fuu;
    TH2F* m_fdd;
    TH2F* m_fgg;
    double m_mt;
};
} // namespace WeakCorr

#endif //WEAKCORRSCALEFACTORPARAM_H
