#include "../interface/SVfitProducerCppWorker.h"


void SVfitProducerCppWorker::setCovMET(double cov00, double cov01, double cov10, double cov11){
	//m_covMET[0][0] = cov00; m_covMET[0][1] = cov01; m_covMET[1][0] = cov10; m_covMET[1][1] = cov11;
	m_covMET[0][0] = 700; m_covMET[0][1] = -178; m_covMET[1][0] = -178; m_covMET[1][1] = 179;
    }
   
void SVfitProducerCppWorker::setMeasuredMET(double x, double y){
    m_measuredMETx = x; m_measuredMETy = y;
}

void SVfitProducerCppWorker::setMeasuredTauLeptons(){
   m_measuredTauLeptons.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToElecDecay, 33.7393, 0.9409,  -0.541458, 0.51100e-3)); // tau -> electron decay (Pt, eta, phi, mass)
   m_measuredTauLeptons.push_back(MeasuredTauLepton(MeasuredTauLepton::kTauToHadDecay,  25.7322, 0.618228, 2.79362,  0.13957, 0)); // tau -> 1prong0pi0 hadronic decay (Pt, eta, phi, mass)
}

const double SVfitProducerCppWorker::getSVfit(int verbosity /*= 0*/){
   ClassicSVfit svFitAlgo(verbosity);
   svFitAlgo.addLogM_fixed(true, 6.);
   svFitAlgo.setLikelihoodFileName("testClassicSVfit.root");

   svFitAlgo.integrate(m_measuredTauLeptons, m_measuredMETx, m_measuredMETy, m_covMET);
   
   bool isValidSolution = svFitAlgo.isValidSolution();
   double mass = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass();
   double massErr = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMassErr();
   double transverseMass = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getTransverseMass();
   double transverseMassErr = static_cast<HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getTransverseMassErr();

   if ( isValidSolution ) {
     std::cout << "found valid solution: mass = " << mass << " +/- " << massErr << " ,"
               << " transverse mass = " << transverseMass << " +/- " << transverseMassErr << " " << std::endl;
   } else {
     std::cout << "sorry, failed to find valid solution !!" << std::endl;
   }

   m_measuredTauLeptons.clear();
   return mass;
 } 