// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "EMCALBase/Cell.h"
#include <iostream>
#include <bitset>

using namespace o2::EMCAL;

ClassImp(Cell)

  Cell::Cell(Double_t amplitude, Double_t time, Short_t tower)
{
  setAmplitudeToADC(amplitude);
  setTime(time);
  setTower(tower);
}

void Cell::setAmplitudeToADC(Double_t amplitude)
{
  ULong_t a = 0;
  if (amplitude > 1023*0.0167) a=1023;
  else if (amplitude < 0) a=0;
  else a = (ULong_t) (amplitude/0.0167);

  a <<= 25;
  std::bitset<40> b1(a);
  std::bitset<40> b2 = mBits & 0x1ffffff; // mBits & (2^25 - 1)
  mBits = b1 + b2;
}

void Cell::setADC(Short_t adc)
{
  if (adc > 1023) adc = 1023;
  else if (adc < 0) adc = 0;
  ULong_t a = (Ulong_t) adc;

  a <<= 25;
  std::bitset<40> b1(a);
  std::bitset<40> b2 = mBits & 0x1ffffff; // mBits & (2^25 - 1)
  mBits = b1 + b2;
}

Short_t Cell::getADC()
{
  ULong_t a = getLong();
  a >>= 25;
  a &= 1023;
  return ((Short_t) a);
}

void Cell::setTime(Double_t time)
{
  ULong_t t = 0;
  if (time > 511) t=511;
  else if (time < 0) t=0;
  else t = (ULong_t) time;

  t <<= 16;
  std::bitset<40> b1(t);
  std::bitset<40> b2 = mBits & 34326249471; // mBits & 0000011111111110000000001111111111111111
  mBits = b1 + b2;
}

Short_t Cell::getTime()
{
  ULong_t t = getLong();
  t >>= 16;
  t &= 511;
  return ((Short_t) t);
}

void Cell::setTower(Short_t tower)
{
  if (tower > 32767 || tower < 0) tower = 32767;
  ULong_t t = (ULong_t) tower;

  std::bitset<40> b1(t);
  std::bitset<40> b2 = mBits & 34359672832; // mBits & 0000011111111111111111110000000000000000
  mBits = b1 + b2;
}

Short_t Cell::getTower()
{
  ULong_t t = getLong();
  t &= 32767;
  return ((Short_t) t);
}

void Cell::setLong(ULong_t l)
{
  bitset<40> b(l);
  mBits = b;
}

void Cell::PrintStream(std::ostream& stream) const
{
  stream << "EMCAL Cell: Tower " << getTower() << ", Time " << getTime() << ", ADC " << getAmplitude() << ", Bits " << mBits;
}

std::ostream& operator<<(std::ostream& stream, const Cell& c)
{
  c.PrintStream(stream);
  return stream;
}
