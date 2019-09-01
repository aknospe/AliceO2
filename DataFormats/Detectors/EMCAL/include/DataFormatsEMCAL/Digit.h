// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#ifndef ALICEO2_EMCAL_DIGIT_H_
#define ALICEO2_EMCAL_DIGIT_H_

#include <iosfwd>
#include <cmath>
#include "Rtypes.h"
#include "CommonDataFormat/TimeStamp.h"
#include "DataFormatsEMCAL/Constants.h"

#include <boost/serialization/base_object.hpp> // for base_object

namespace o2
{

namespace emcal
{
/// \class Digit
/// \brief EMCAL digit implementation

using DigitBase = o2::dataformats::TimeStamp<double>;
class Digit : public DigitBase
{
 public:
  Digit() = default;

  Digit(Short_t tower, Double_t energy, Double_t time, ChannelType_t type = ChannelType_t::HIGH_GAIN);
  ~Digit() = default; // override

  bool operator<(const Digit& other) const { return getTimeStamp() < other.getTimeStamp(); }
  bool operator>(const Digit& other) const { return getTimeStamp() > other.getTimeStamp(); }
  bool operator==(const Digit& other) const { return getTimeStamp() == other.getTimeStamp(); }

  bool canAdd(const Digit other)
  {
    return (mTower == other.getTower() && std::abs(getTimeStamp() - other.getTimeStamp()) <= constants::EMCAL_TIMESAMPLE);
  }

  Digit& operator+=(const Digit& other);              // Adds energy of other digits to this digit.
  friend Digit operator+(Digit lhs, const Digit& rhs) // Adds energy of two digits.
  {
    lhs += rhs;
    return lhs;
  }

  void setTower(Short_t tower) { mTower = tower; }
  Short_t getTower() const { return mTower; }

  void setEnergy(Double_t energy) { mEnergy = energy; }
  Double_t getEnergy() const { return mEnergy; }

  void setType(ChannelType_t ctype);
  ChannelType_t getType() const;

  void setLowGain() { mType = 0; }
  Bool_t getLowGain() { return (!mType); }

  void setHighGain() { mType = 1; }
  Bool_t getHighGain() const { return (mType == 1); }

  void setTRU() { mType = 2; }
  Bool_t getTRU() const { return (mType == 2); }

  void setLEDMon() { mType = 3; }
  Bool_t getLEDMon() const { return (mType == 3); }

  void PrintStream(std::ostream& stream) const;

 private:
  friend class boost::serialization::access;

  Double_t mEnergy; ///< Energy (GeV/c^2)
  Short_t mTower;   ///< Tower index (absolute cell ID)
  UChar_t mType;    ///< Type (Low Gain, High Gain, TRU, LEDMon)

  ClassDefNV(Digit, 1);
};

std::ostream& operator<<(std::ostream& stream, const Digit& dig);
} // namespace emcal
} // namespace o2
#endif
