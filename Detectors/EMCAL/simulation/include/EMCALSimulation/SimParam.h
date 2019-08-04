// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
#ifndef ALICEO2_EMCAL_SIMPARAM_H_
#define ALICEO2_EMCAL_SIMPARAM_H_

#include <iosfwd>
#include "Rtypes.h"

namespace o2
{
namespace emcal
{
/// \class SimParam
/// \brief EMCal simulation parameters

class SimParam
{
 public:
  ~SimParam() = default;

  static SimParam* GetInstance()
  {
    if (!mSimParam)
      mSimParam = new SimParam();

    return mSimParam;
  }

  // Parameters used in Digitizer
  void SetDigitThreshold(Int_t val) { mDigitThreshold = val; }
  Int_t GetDigitThreshold() const { return mDigitThreshold; }

  void SetPinNoise(Float_t val) { mPinNoise = val; }
  Float_t GetPinNoise() const { return mPinNoise; }

  void SetTimeNoise(Float_t val) { mTimeNoise = val; }
  Float_t GetTimeNoise() const { return mTimeNoise; }

  void SetTimeDelay(Float_t val) { mTimeDelay = val; }
  Float_t GetTimeDelay() const { return mTimeDelay; }

  void SetTimeDelayFromOCDB(Bool_t val) { mTimeDelayFromCDB = val; }
  Bool_t IsTimeDelayFromOCDB() const { return mTimeDelayFromCDB; }

  void SetTimeResolutionPar0(Float_t val) { mTimeResolutionPar0 = val; }
  Float_t GetTimeResolutionPar0() const { return mTimeResolutionPar0; }
  void SetTimeResolutionPar1(Float_t val) { mTimeResolutionPar1 = val; }
  Float_t GetTimeResolutionPar1() const { return mTimeResolutionPar1; }
  Double_t GetTimeResolution(Double_t energy) const;

  void SetNADCEC(Int_t val) { mNADCEC = val; }
  Int_t GetNADCEC() const { return mNADCEC; }

  void SetMeanPhotonElectron(Int_t val) { mMeanPhotonElectron = val; }
  Int_t GetMeanPhotonElectron() const { return mMeanPhotonElectron; }

  void SetGainFluctuations(Float_t val) { mGainFluctuations = val; }
  Float_t GetGainFluctuations() const { return mGainFluctuations; }

  void SetTimeResponseTau(Int_t val) { mTimeResponseTau = val; }
  Int_t GetTimeResponseTau() const { return mTimeResponseTau; }

  void SetTimeResponsePower(Float_t val) { mTimeResponsePower = val; }
  Float_t GetTimeResponsePower() const { return mTimeResponsePower; }

  void SetTimeResponseThreshold(Float_t val) { mTimeResponsePower = val; }
  Float_t GetTimeResponseThreshold() const { return mTimeResponsePower; }

  // Parameters used in SDigitizer
  void SetA(Float_t val) { mA = val; }
  Float_t GetA() const { return mA; }
  void SetB(Float_t val) { mB = val; }
  Float_t GetB() const { return mB; }

  void SetECPrimaryThreshold(Float_t val) { mTimeResponseThreshold = val; }
  Float_t GetECPrimaryThreshold() const { return mTimeResponseThreshold; }

  void PrintStream(std::ostream& stream) const;

 private:
  SimParam() = default;

  static o2::emcal::SimParam* mSimParam; // pointer to the unique instance of the class

  // Digitizer
  Int_t mDigitThreshold{ 3 };              // Threshold for storing digits in EMC
  Int_t mMeanPhotonElectron{ 4400 };       // number of photon electrons per GeV deposited energy
  Float_t mGainFluctuations{ 15. };        // correct fMeanPhotonElectron by the gain fluctuations
  Float_t mPinNoise{ 0.012 };              // Electronics noise in EMC, APD
  Float_t mTimeNoise{ 1.28e-5 };           // Electronics noise in EMC, time
  Float_t mTimeDelay{ 600e-9 };            // Simple time delay to mimick roughly delay in data
  Bool_t mTimeDelayFromCDB{ false };       // Get time delay from OCDB
  Float_t mTimeResolutionPar0{ 0.26666 };  // Time resolution of FEE electronics
  Float_t mTimeResolutionPar1{ 1.4586 };   // Time resolution of FEE electronics
  Int_t mNADCEC{ 0x10000 };                // number of channels in EC section ADC
  Float_t mTimeResponseTau{ 2.35 };        // Raw time response function tau parameter
  Float_t mTimeResponsePower{ 2 };         // Raw time response function power parameter
  Float_t mTimeResponseThreshold{ 0.001 }; // Raw time response function energy threshold

  // SDigitizer
  Float_t mA{ 0. };                 // Pedestal parameter
  Float_t mB{ 1.e+6 };              // Slope Digitizition parameters
  Float_t mECPrimThreshold{ 0.05 }; // To store primary if EC Shower Elos > threshold
};

std::ostream& operator<<(std::ostream& stream, const SimParam& s);

} // namespace emcal
} // namespace o2

#endif
