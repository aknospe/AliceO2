// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "DataFormatsEMCAL/LabeledDigit.h"
#include <iostream>

using namespace o2::emcal;

LabeledDigit::LabeledDigit(Digit digit, o2::MCCompLabel label)
: mDigit(digit)
{
  mLabels.push_back(label);
}

LabeledDigit::LabeledDigit(Short_t tower, Double_t energy, Double_t time, o2::MCCompLabel label)
: mDigit(time, tower, energy)
{
  mLabels.push_back(label);
}

LabeledDigit& LabeledDigit::operator+=(const LabeledDigit& other)
{
  if (canAdd(other)) {
    mDigit += other.getDigit();
      
    for(auto label : other.getLabels()) {
      mLabels.push_back(label);
    }
  }
  // Does nothing if the digits are in different towers.
  return *this;
}

void LabeledDigit::PrintStream(std::ostream& stream) const
{
  stream << "EMCAL LabeledDigit: Tower " << getTower() << ", Time " << getTimeStamp() << ", Energy " << getEnergy() << ", Labels ( ";
    for(auto label : mLabels) {
        stream << label.getRawValue() << " ";
    }
    stream << ")";
}

std::ostream& operator<<(std::ostream& stream, const LabeledDigit& digi)
{
  digi.PrintStream(stream);
  return stream;
}
