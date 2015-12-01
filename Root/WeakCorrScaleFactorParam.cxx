// weak corrections for powheg ttbar MC
// using parametrisations based on the HATHOR
// implementation of calculations from J. Kuehn, P. Uwer

#include <iostream>

// #include "LHAPDF/LHAPDF.h"
// #include "Hathor.h"
#include "TtResonancesTools/WeakCorrScaleFactorParam.h"

#include "TLorentzVector.h"
#include "TFile.h"

WeakCorr::WeakCorrScaleFactorParam::WeakCorrScaleFactorParam(TString mapfile) :
    m_fuu(0),
    m_fdd(0),
    m_fgg(0),
    m_mt(172.5)
{
    if (!init(mapfile)) {
        std::cout << "ERROR: Could not initialise histograms!" << std::endl;
        delete m_fuu; m_fuu = 0;
        delete m_fdd; m_fdd = 0;
        delete m_fgg; m_fgg = 0;
    }
}

WeakCorr::WeakCorrScaleFactorParam::~WeakCorrScaleFactorParam() {
    delete m_fuu;
    delete m_fdd;
    delete m_fgg;
}

bool WeakCorr::WeakCorrScaleFactorParam::init(TString mapfile) {
    TFile infile(mapfile.Data(), "READ");
    TH2F* hist = dynamic_cast<TH2F*>(infile.Get("Fuu"));
    if (!hist) return false;
    m_fuu = (TH2F*) hist->Clone("myfuu");
    m_fuu->SetDirectory(0);
    hist = dynamic_cast<TH2F*>(infile.Get("Fdd"));
    if (!hist) return false;
    m_fdd = (TH2F*) hist->Clone("myfdd");
    m_fdd->SetDirectory(0);
    hist = dynamic_cast<TH2F*>(infile.Get("Fgg"));
    if (!hist) return false;
    m_fgg = (TH2F*) hist->Clone("myfgg");
    m_fgg->SetDirectory(0);
    return true;
}

WeakCorr::ScaleFactor WeakCorr::WeakCorrScaleFactorParam::getScaleFactor(const double& shat, const double& z, const int& type) {
    ScaleFactor sf;
    sf.nominal = getWeight(shat, z, type);
    // 10% uncertainty on correction (F being the relative correction):
    // nominal = 1 + F
    // up   = 1 + F + 0.1*F = nominal + 0.1*(nominal - 1) = 1.1*nominal - 0.1
    // down = 1 + F - 0.1*F = nominal - 0.1*(nominal - 1) = 0.9*nominal + 0.1
    // up/down mean stronger/less correction, i.e. down > nominal in case of negative correction
    sf.up = 1.1 * sf.nominal - 0.1;
    sf.down = 0.9 * sf.nominal + 0.1;
    return sf;
}

WeakCorr::ScaleFactor WeakCorr::WeakCorrScaleFactorParam::getScaleFactor(
        float& MC_t_pt,
        float& MC_t_eta,
        float& MC_t_phi,
        float& MC_t_m,
        float& MC_tbar_pt,
        float& MC_tbar_eta,
        float& MC_tbar_phi,
        float& MC_tbar_m,
        int& type) {
    ScaleFactor sf;
    sf.nominal = getWeight(MC_t_pt,MC_t_eta,MC_t_phi,MC_t_m,MC_tbar_pt,MC_tbar_eta,MC_tbar_phi,MC_tbar_m,type);
    // 10% uncertainty on correction (F being the relative correction):
    // nominal = 1 + F
    // up   = 1 + F + 0.1*F = nominal + 0.1*(nominal - 1) = 1.1*nominal - 0.1
    // down = 1 + F - 0.1*F = nominal - 0.1*(nominal - 1) = 0.9*nominal + 0.1
    // up/down mean stronger/less correction, i.e. down > nominal in case of negative correction
    sf.up = 1.1 * sf.nominal - 0.1;
    sf.down = 0.9 * sf.nominal + 0.1;
    return sf;    
}

double WeakCorr::WeakCorrScaleFactorParam::getWeight(const double& shat, const double& z, const int& type) {
    if (!m_fuu || !m_fdd  || !m_fgg) {
        return -1.;
    }
    double weight = 1.;
    const double mtt = sqrt(shat);
    if (mtt < m_mt*2.) {
        return weight;
    }
    if (type == 1) {
//         weight = m_fgg->Interpolate(shat, z);
        weight = m_fgg->Interpolate(mtt, z);
    } else if (type == 2) {
        weight = m_fuu->Interpolate(mtt, z);
//         weight = m_fuu->Interpolate(shat, z);
    } else if (type == 3) {
        weight = m_fdd->Interpolate(mtt, z);
//         weight = m_fdd->Interpolate(shat, z);
    } else {
        std::cout << "ERROR: Wrong initial state type given" << std::endl;
    }
    
    return weight;
}

double WeakCorr::WeakCorrScaleFactorParam::getWeight(
        float& MC_t_pt,
        float& MC_t_eta,
        float& MC_t_phi,
        float& MC_t_m,
        float& MC_tbar_pt,
        float& MC_tbar_eta,
        float& MC_tbar_phi,
        float& MC_tbar_m,
        int& type) {
    double weight = 1.;
    TLorentzVector topMomentum;
    topMomentum.SetPtEtaPhiM( MC_t_pt*0.001,
                              MC_t_eta,
                              MC_t_phi,
                              MC_t_m*0.001  );


    TLorentzVector antitopMomentum;
    antitopMomentum.SetPtEtaPhiM( MC_tbar_pt*0.001,
                              MC_tbar_eta,
                              MC_tbar_phi,
                              MC_tbar_m*0.001  );




    TLorentzVector ttbarSystem = topMomentum + antitopMomentum;
    const double shat = ttbarSystem.M2(); // give it a value from Marino's varaibles -  MC_ttbar_lpj_beforeFSR_m

    TLorentzVector beam1(0., 0.,  13000., 13000.);
    TLorentzVector beam2(0., 0., -13000., 13000.);
    TVector3 boostVec = ttbarSystem.BoostVector();
    boostVec *= -1.;

    topMomentum.Boost(boostVec);
    beam1.Boost(boostVec);
    beam2.Boost(boostVec);

    TVector3 scatteringAxis = (beam1 - beam2).Vect().Unit();

    const double z = topMomentum.Vect().Unit() * scatteringAxis;

    weight = getWeight(shat, z, type);

    return weight;
    
}
