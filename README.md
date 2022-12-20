# ClassicSVfit for Bamboo HEP framework
Latest version of SVfit_standalone algorithm and FastMTT for [bamboo](https://gitlab.cern.ch/cp3-cms/bamboo/-/tree/master/bamboo)

# Installation instructions

In order to install the code, execute:

```
git clone git@github.com:clacaputo/ClassicSVfit.git ClassicSVfit -b cmake_build
mkdir build-ClassicSVfit-FastMTT/
cd build-ClassicSVfit-FastMTT/
cmake cmake -DCMAKE_INSTALL_PREFIX=$VIRTUAL_ENV ../ClassicSVfit/
make -j2 
```

In case of compilation problems, please sutmitt an issue on
https://github.com/SVfit/ClassicSVfit/issues


# Structure

## `class SVfitBambooProducer`

A `class SVfitBambooProducer` is defined in [./interface/SVfitBambooProducer.h](./interface/SVfitBambooProducer.h). It contains two methods for computing `ClassicSVfit` and `FastMTT`.
The two methods take as inputs the same variables: 

- Missing Energy Covariance Matrix: `double cov00, double cov01, double cov10, double cov11`
- Missing Energy px-py: `double METx, double METy,`
- first lepton pT-eta-phi-mass: `double pT1, double eta1, double phi1, double mass1,`
- second lepton pT-eta-phi-mass: `double pT1, double eta1, double phi1, double mass1,`
- tau pair category: `std::string category`

```cpp
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
```

The `categories` are also defined in [./interface/SVfitBambooProducer.h](./interface/SVfitBambooProducer.h)

**NOTA**: To add new categories for SVfit, you can intervene here 

```cpp
namespace utils{
    using decayTypePair = std::pair<MeasuredTauLepton::kDecayType,MeasuredTauLepton::kDecayType>;
    //class enum TauPairCatories {MuTau, EleTau, TauTau}

    std::set<std::string> TauPairCategories {"1mu1tau", "1ele1tau", "2tau"};

    std::map<int, std::string> intToCatMap { {0, "1mu1tau"}, {1, "1ele1tau"}, { 2,"2tau"} };

    std::map<std::string, decayTypePair> catToDecayPair { {"1mu1tau" , std::make_pair(MeasuredTauLepton::kTauToMuDecay, MeasuredTauLepton::kTauToHadDecay)},
                                                          {"1ele1tau", std::make_pair(MeasuredTauLepton::kTauToElecDecay, MeasuredTauLepton::kTauToHadDecay)},
                                                          {"2tau", std::make_pair(MeasuredTauLepton::kTauToHadDecay, MeasuredTauLepton::kTauToHadDecay)}, };
    
}
```

## How to use in bamboo

If you have installed `bamboo` following the instructions, you can load the `libClassicSVfit` in you `bamboo` module

```python
import os
from bamboo.root import loadDependency 

if os.environ["VIRTUAL_ENV"] == "":
    print("$VIRTUAL_ENV is not set. Please, activate your virtual environment")
    exit(-1)

loadDependency( headers="SVfitBambooProducer.h",
                includePath="{0}/../ClassicSVfit/interface".format(os.environ["VIRTUAL_ENV"]),
                dynamicPath="{0}/../build-ClassicSVfit-FastMTT/src".format(os.environ["VIRTUAL_ENV"]), 
                libraries="ClassicSVfit")
```

Then you create an instance of `SVfitBambooProducer`:

```python
svFitBambooProducer = op.define("SVfitBambooProducer", 'auto <<name>> = SVfitBambooProducer();')
```

Now you can use the two methods. For example, if you have a `NanoAOD TTree` named `t` and a tau pair named `bestH`, you can compute the tau-pair SVfit mass like this:

```python
mass = svFitBambooProducer.computeSVfit(t.MET.covXX, t.MET.covXY, t.MET.covXY, t.MET.covYY,
                                        t.MET.pt*op.cos(t.MET.phi), t.MET.pt*op.cos(t.MET.phi),
                                        bestH[0].p4.Pt(), bestH[0].p4.Eta(), bestH[0].p4.Phi(), bestH[0].p4.M(),
                                        bestH[1].p4.Pt(), bestH[1].p4.Eta(), bestH[1].p4.Phi(), bestH[1].p4.M(),
                                        Const("std::string", f"\"{cat}\"") )
massFast = svFitBambooProducer.computeFastMTT(t.MET.covXX, t.MET.covXY, t.MET.covXY, t.MET.covYY,
                                              t.MET.pt*op.cos(t.MET.phi), t.MET.pt*op.cos(t.MET.phi),
                                              bestH[0].p4.Pt(), bestH[0].p4.Eta(), bestH[0].p4.Phi(), bestH[0].p4.M(),
                                              bestH[1].p4.Pt(), bestH[1].p4.Eta(), bestH[1].p4.Phi(), bestH[1].p4.M(),
                                              Const("std::string", f"\"{cat}\"") )
```

# Some NON-bamboo examples

- [Presentation, slides 2+3](https://indico.cern.ch/event/684622/contributions/2807248/attachments/1575090/2487044/presentation_tmuller.pdf)
- [Example(s)](https://github.com/SVfit/ClassicSVfit/blob/master/bin/testClassicSVfit.cc)
