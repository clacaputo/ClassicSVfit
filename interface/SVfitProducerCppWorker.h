#ifndef PhysicsTools_NanoAODTools_fastMTTProducerCppWorker_h
#define PhysicsTools_NanoAODTools_fastMTTProducerCppWorker_h

#include <utility>
#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>

#include "ClassicSVfit.h"
#include "MeasuredTauLepton.h"
#include "svFitHistogramAdapter.h"

using namespace classic_svFit;

class SVfitProducerCppWorker{

public:
    SVfitProducerCppWorker(): m_covMET(2,2) {}
    
    void setCovMET(double cov00, double cov01, double cov10, double cov11);
   
    void setMeasuredMET(double x, double y);

    void setMeasuredTauLeptons();

    const double getSVfit(int verbosity = 0 );

private:
    double m_measuredMETx, m_measuredMETy;
    TMatrixD  m_covMET;
    std::vector<MeasuredTauLepton> m_measuredTauLeptons;
};

#endif
