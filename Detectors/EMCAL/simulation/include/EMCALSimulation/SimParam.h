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
#include "SimConfig/ConfigurableParam.h"
#include "SimConfig/ConfigurableParamHelper.h"
#include "Rtypes.h"

namespace o2
{
namespace emcal
{
/// \class SimParam
/// \brief EMCal simulation parameters

class SimParam : public o2::conf::ConfigurableParamHelper<SimParam>
{
 public:
  ~SimParam() = default;

  // Parameters used in Digitizer
  void setDigitThreshold(Int_t val) { mDigitThreshold = val; }
  Int_t getDigitThreshold() const { return mDigitThreshold; }

  void setPinNoise(Float_t val) { mPinNoise = val; }
  Float_t getPinNoise() const { return mPinNoise; }

  void setTimeNoise(Float_t val) { mTimeNoise = val; }
  Float_t getTimeNoise() const { return mTimeNoise; }

  void setTimeDelay(Float_t val) { mTimeDelay = val; }
  Float_t getTimeDelay() const { return mTimeDelay; }

  void setTimeDelayFromOCDB(Bool_t val) { mTimeDelayFromCDB = val; }
  Bool_t isTimeDelayFromOCDB() const { return mTimeDelayFromCDB; }

  void setTimeResolutionPar0(Float_t val) { mTimeResolutionPar0 = val; }
  Float_t getTimeResolutionPar0() const { return mTimeResolutionPar0; }
  void setTimeResolutionPar1(Float_t val) { mTimeResolutionPar1 = val; }
  Float_t getTimeResolutionPar1() const { return mTimeResolutionPar1; }
  Double_t getTimeResolution(Double_t energy) const;

  void setNADCEC(Int_t val) { mNADCEC = val; }
  Int_t setNADCEC() const { return mNADCEC; }

  void setMeanPhotonElectron(Int_t val) { mMeanPhotonElectron = val; }
  Int_t getMeanPhotonElectron() const { return mMeanPhotonElectron; }

  void setGainFluctuations(Float_t val) { mGainFluctuations = val; }
  Float_t getGainFluctuations() const { return mGainFluctuations; }

  void setTimeResponseTau(Int_t val) { mTimeResponseTau = val; }
  Int_t getTimeResponseTau() const { return mTimeResponseTau; }

  void setTimeResponsePower(Float_t val) { mTimeResponsePower = val; }
  Float_t getTimeResponsePower() const { return mTimeResponsePower; }

  void setTimeResponseThreshold(Float_t val) { mTimeResponsePower = val; }
  Float_t getTimeResponseThreshold() const { return mTimeResponsePower; }

  // Parameters used in SDigitizer
  void setA(Float_t val) { mA = val; }
  Float_t getA() const { return mA; }
  void setB(Float_t val) { mB = val; }
  Float_t getB() const { return mB; }

  void setECPrimaryThreshold(Float_t val) { mECPrimThreshold = val; }
  Float_t getECPrimaryThreshold() const { return mECPrimThreshold; }

  void setSignalDelay(Float_t val) { mSignalDelay = val; }
  Float_t getSignalDelay() const { return mSignalDelay; }

  void setLiveTime(Float_t val) { mLiveTime = val; }
  Float_t getLiveTime() const { return mLiveTime; }

  void setBusyTime(Float_t val) { mBusyTime = val; }
  Float_t getBusyTime() const { return mBusyTime; }

  void setDisablePileup(Bool_t val = true) { mDisablePileup = val; }
  Bool_t isDisablePileup() const {return mDisablePileup; }

  void PrintStream(std::ostream& stream) const;

 private:

  // Digitizer
  Int_t mDigitThreshold{3};              ///< Threshold for storing digits in EMC
  Int_t mMeanPhotonElectron{4400};       ///< number of photon electrons per GeV deposited energy
  Float_t mGainFluctuations{15.};        ///< correct fMeanPhotonElectron by the gain fluctuations
  Float_t mPinNoise{0.012};              ///< Electronics noise in EMC, APD
  Float_t mTimeNoise{1.28e-5};           ///< Electronics noise in EMC, time
  Float_t mTimeDelay{600e-9};            ///< Simple time delay to mimick roughly delay in data
  Bool_t mTimeDelayFromCDB{false};       ///< Get time delay from OCDB
  Float_t mTimeResolutionPar0{0.26666};  ///< Time resolution of FEE electronics
  Float_t mTimeResolutionPar1{1.4586};   ///< Time resolution of FEE electronics
  Int_t mNADCEC{0x10000};                ///< number of channels in EC section ADC
  Float_t mTimeResponseTau{2.35};        ///< Raw time response function tau parameter
  Float_t mTimeResponsePower{2};         ///< Raw time response function power parameter
  Float_t mTimeResponseThreshold{0.001}; ///< Raw time response function energy threshold

  // SDigitizer
  Float_t mA{0.};                 ///< Pedestal parameter
  Float_t mB{1.e+6};              ///< Slope Digitizition parameters
  Float_t mECPrimThreshold{0.05}; ///< To store primary if EC Shower Elos > threshold

  // Timing
  Float_t mSignalDelay{700}; ///< Signal delay time (ns)
  Float_t mLiveTime{1500};   ///< EMCal live time (ns)
  Float_t mBusyTime{0};      ///< EMCal busy time (ns)

  // DigitizerSpec
  Bool_t mDisablePileup{false}; ///< disable pileup simulation

  O2ParamDef(SimParam, "EMCSimParam");
};

std::ostream& operator<<(std::ostream& stream, const SimParam& s);

} // namespace emcal
} // namespace o2

#endif
