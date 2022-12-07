#include "../interface/SVfitProducerCppWorker.h"

int main () {

    SVfitProducerCppWorker svFit;

    svFit.setCovMET(23.,43.,45.,22.);
    svFit.setMeasuredMET(100.,30.);
    svFit.setMeasuredTauLeptons();

    auto mass = svFit.getSVfit();

    return 0;

}