#include "../interface/SVfitBambooProducer.h"
#include "TLorentzVector.h"

#include <cassert>
 
// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))


const double SVfitBambooProducer::computeSVfit(double cov00, double cov01, double cov10, double cov11,
                                                   double METx, double METy, 
                                                   double pT1, double eta1, double phi1, double mass1,
                                                   double pT2, double eta2, double phi2, double mass2,
                                                   std::string category
                                                  ){
  
  // Check if the category is valid and defined in SVfitBambooProduce.h
  assertm(utils::TauPairCategories.count(category), "The tau-pair category you passed is not defined in interface/SVfitBambooProducer.h. Please, make sure the category make sense!");

  ClassicSVfit svFitAlgo(0);
  svFitAlgo.addLogM_fixed(true, 6.);
  //svFitAlgo.setLikelihoodFileName("testClassicSVfit.root");

  std::vector<MeasuredTauLepton> measuredTauLeptons;
  TMatrixD  covMET(2,2);
  covMET[0][0] = cov00; covMET[0][1] = cov01; covMET[1][0] = cov10; covMET[1][1] = cov11;

  auto decayPair       = utils::catToDecayPair[category];

  // Strange but it happens
  if ( decayPair.first == MeasuredTauLepton::kTauToElecDecay && mass1 < 0 ) mass1 = 0.51100e-3;

  measuredTauLeptons.push_back(MeasuredTauLepton(decayPair.first,  pT1, eta1, phi1, mass1)); // tau -> decayType (Pt, eta, phi, mass)
  measuredTauLeptons.push_back(MeasuredTauLepton(decayPair.second, pT2, eta2, phi2, mass2)); // tau -> decayType (Pt, eta, phi, mass)
  
  svFitAlgo.integrate(measuredTauLeptons, METx, METy, covMET);

  bool isValidSolution = svFitAlgo.isValidSolution();
  double mass = static_cast<DiTauSystemHistogramAdapter*>(svFitAlgo.getHistogramAdapter())->getMass();
  double massErr = static_cast<DiTauSystemHistogramAdapter*>(svFitAlgo.getHistogramAdapter())->getMassErr();
  double transverseMass = static_cast<DiTauSystemHistogramAdapter*>(svFitAlgo.getHistogramAdapter())->getTransverseMass();
  double transverseMassErr = static_cast<DiTauSystemHistogramAdapter*>(svFitAlgo.getHistogramAdapter())->getTransverseMassErr();

  //if ( isValidSolution ) {
  //  std::cout << "found valid solution: mass = " << mass << " +/- " << massErr << " ,"
  //            << " transverse mass = " << transverseMass << " +/- " << transverseMassErr << " " << std::endl;
  //} else {
  //  std::cout << "sorry, failed to find valid solution !!" << std::endl;
  //}

  measuredTauLeptons.clear();
  return mass;
}

const double SVfitBambooProducer::computeFastMTT(double cov00, double cov01, double cov10, double cov11,
                                                   double METx, double METy, 
                                                   double pT1, double eta1, double phi1, double mass1,
                                                   double pT2, double eta2, double phi2, double mass2,
                                                   std::string category
                                                  ){
  
  // Check if the category is valid and defined in SVfitBambooProduce.h
  assertm(utils::TauPairCategories.count(category), "The tau-pair category you passed is not defined in interface/SVfitBambooProducer.h. Please, make sure the category make sense!");
  
  FastMTT aFastMTTAlgo;

  std::vector<MeasuredTauLepton> measuredTauLeptons;
  TMatrixD  covMET(2,2);
  covMET[0][0] = cov00; covMET[0][1] = cov01; covMET[1][0] = cov10; covMET[1][1] = cov11;

  auto decayPair       = utils::catToDecayPair[category];

  // Strange but it happens
  if ( decayPair.first == MeasuredTauLepton::kTauToElecDecay && mass1 < 0 ) mass1 = 0.51100e-3;

  measuredTauLeptons.push_back(MeasuredTauLepton(decayPair.first,  pT1, eta1, phi1, mass1)); // tau -> decayType (Pt, eta, phi, mass)
  measuredTauLeptons.push_back(MeasuredTauLepton(decayPair.second, pT2, eta2, phi2, mass2)); // tau -> decayType (Pt, eta, phi, mass)
  
  aFastMTTAlgo.run(measuredTauLeptons, METx, METy, covMET);
  LorentzVector ttP4 = aFastMTTAlgo.getBestP4();
  //std::cout<<std::endl;
  //std::cout << "FastMTT found best p4 with mass = " << ttP4.M()<<std::endl;
  //std::cout<<"Real Time =   "<<aFastMTTAlgo.getRealTime("scan")<<" seconds "
	//   <<" Cpu Time =   "<<aFastMTTAlgo.getCpuTime("scan")<<" seconds"<<std::endl;

  measuredTauLeptons.clear();

  return ttP4.M();
}