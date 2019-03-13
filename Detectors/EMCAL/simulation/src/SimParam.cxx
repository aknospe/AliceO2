// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "EMCALSimulation/SimParam.h"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const o2::EMCAL::SimParam& s)
{
  s.PrintStream(stream);
  return stream;
}

void o2::EMCAL::SimParam::PrintStream(std::ostream& stream) const
{
  stream << "EMCAL::SimParam.mDigitThreshold = " << mDigitThreshold;
  stream << "\nEMCAL::SimParam.mMeanPhotonElectron = " << mMeanPhotonElectron;
  stream << "\nEMCal::SimParam.mGainFluctuations = " << mGainFluctuations;
  stream << "\nEMCal::SimParam.mPinNoise = " << mPinNoise;
  stream << "\nEMCal::SimParam.mTimeNoise = " << mTimeNoise;
  stream << "\nEMCal::SimParam.mTimeDelay = " << mTimeDelay;
  stream << "\nEMCal::SimParam.mTimeDelayFromCDB = " << ((mTimeDelayFromCDB) ? "true" : "false");
  stream << "\nEMCal::SimParam.mTimeResolutionPar0 = " << mTimeResolutionPar0;
  stream << "\nEMCal::SimParam.mTimeResolutionPar1 = " << mTimeResolutionPar1;
  stream << "\nEMCal::SimParam.mNADCEC = " << mNADCEC;
  stream << "\nEMCal::SimParam.mA = " << mA;
  stream << "\nEMCal::SimParam.mB = " << mB;
  stream << "\nEMCal::SimParam.mECPrimThreshold = " << mECPrimThreshold;
}
