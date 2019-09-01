// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "DataFormatsEMCAL/Digit.h"
#include <iostream>

using namespace o2::emcal;

Digit::Digit(Short_t tower, Double_t energy, Double_t time, ChannelType_t type)
  : DigitBase(time), mTower(tower), mEnergy(energy)
{
  setType(type);
}

Digit& Digit::operator+=(const Digit& other)
{
  if (canAdd(other))
    mEnergy += other.getEnergy();
  // Does nothing if the digits are in different towers.
  return *this;
}

void Digit::setType(ChannelType_t ctype)
{
  if (ctype == ChannelType_t::HIGH_GAIN)
    setHighGain();
  else if (ctype == ChannelType_t::TRU)
    setTRU();
  else if (ctype == ChannelType_t::LEDMON)
    setLEDMon();
  else
    setLowGain();
}

ChannelType_t Digit::getType() const
{
  if (getHighGain())
    return ChannelType_t::HIGH_GAIN;
  else if (getTRU())
    return ChannelType_t::TRU;
  else if (getLEDMon())
    return ChannelType_t::LEDMON;
  return ChannelType_t::LOW_GAIN;
}

void Digit::PrintStream(std::ostream& stream) const
{
  stream << "EMCAL Digit: Tower " << mTower << ", Time " << getTimeStamp() << ", Energy " << mEnergy;
}

std::ostream& operator<<(std::ostream& stream, const Digit& digi)
{
  digi.PrintStream(stream);
  return stream;
}
