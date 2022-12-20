#ifndef SVfitBambooProducer_h
#define SVfitBambooProducer_h

#include "ClassicSVfit.h"
#include "MeasuredTauLepton.h"
#include "svFitHistogramAdapter.h"

#include "FastMTT.h"

#include "TH1F.h"
#include <set>

using namespace classic_svFit;

namespace utils{
    using decayTypePair = std::pair<MeasuredTauLepton::kDecayType,MeasuredTauLepton::kDecayType>;
    //class enum TauPairCatories {MuTau, EleTau, TauTau}

    std::set<std::string> TauPairCategories {"1mu1tau", "1ele1tau", "2tau"};

    std::map<int, std::string> intToCatMap { {0, "1mu1tau"}, {1, "1ele1tau"}, { 2,"2tau"} };

    std::map<std::string, decayTypePair> catToDecayPair { {"1mu1tau" , std::make_pair(MeasuredTauLepton::kTauToMuDecay, MeasuredTauLepton::kTauToHadDecay)},
                                                          {"1ele1tau", std::make_pair(MeasuredTauLepton::kTauToElecDecay, MeasuredTauLepton::kTauToHadDecay)},
                                                          {"2tau", std::make_pair(MeasuredTauLepton::kTauToHadDecay, MeasuredTauLepton::kTauToHadDecay)}, };
    
}

class SVfitBambooProducer{

public:
    SVfitBambooProducer(){}

    const double computeSVfit(double cov00, double cov01, double cov10, double cov11,
                              double METx, double METy, 
                              double pT1, double eta1, double phi1, double mass1,
                              double pT2, double eta2, double phi2, double mass2,
                              std::string category
                             );

    const double computeFastMTT(double cov00, double cov01, double cov10, double cov11,
                              double METx, double METy, 
                              double pT1, double eta1, double phi1, double mass1,
                              double pT2, double eta2, double phi2, double mass2,
                              std::string category
                             );

};

#endif