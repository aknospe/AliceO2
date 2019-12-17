// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file clusterFinderDefs.h
/// \author David Rohr

#ifndef O2_GPU_CLUSTERFINDERDEFS_H
#define O2_GPU_CLUSTERFINDERDEFS_H

#include "GPUDef.h"

#ifndef __OPENCL__
typedef unsigned char uchar;
#endif
#ifdef __APPLE__
typedef unsigned long ulong;
#endif

#ifdef GPUCA_ALIGPUCODE
#define QMAX_CUTOFF 3
#define QTOT_CUTOFF 0
#define NOISE_SUPPRESSION_MINIMA_EPSILON 10
#define SCRATCH_PAD_WORK_GROUP_SIZE GPUCA_THREAD_COUNT_CLUSTERER
#define BUILD_CLUSTER_NAIVE
#ifdef GPUCA_GPUCODE
#define BUILD_CLUSTER_SCRATCH_PAD
#endif
#define DCHARGEMAP_TIME_MAJOR_LAYOUT
#endif

#ifdef __OPENCL__
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#endif

#ifndef __OPENCL__
#define LOOP_UNROLL_ATTR
#elif defined(UNROLL_LOOPS)
#define LOOP_UNROLL_ATTR __attribute__((opencl_unroll_hint))
#else
#define LOOP_UNROLL_ATTR __attribute__((opencl_unroll_hint(1)))
#endif

#define GET_IS_PEAK(val) (val & 0x01)
#define GET_IS_ABOVE_THRESHOLD(val) (val >> 1)

#define SCRATCH_PAD_SEARCH_N 8
#define SCRATCH_PAD_COUNT_N 16
#define SCRATCH_PAD_BUILD_N 8
#define SCRATCH_PAD_NOISE_N 8

#define PADDING_PAD 2
#define PADDING_TIME 2
#define TPC_SECTORS 36
#define TPC_ROWS_PER_CRU 18
#define TPC_NUM_OF_ROWS 152
#define TPC_PADS_PER_ROW 138
#define TPC_PADS_PER_ROW_PADDED (TPC_PADS_PER_ROW + PADDING_PAD)
#define TPC_NUM_OF_PADS (TPC_NUM_OF_ROWS * TPC_PADS_PER_ROW_PADDED + PADDING_PAD)
#define TPC_MAX_TIME 4000
#define TPC_MAX_TIME_PADDED (TPC_MAX_TIME + 2 * PADDING_TIME)

namespace GPUCA_NAMESPACE
{
namespace gpu
{

using Timestamp = ushort;
using Pad = unsigned char;
using GlobalPad = ushort;
using Row = unsigned char;
using Cru = unsigned char;

#if defined(CHARGEMAP_TYPE_HALF)
using Charge = half;
#else
using Charge = float;
#endif

using Delta = short;
using Delta2 = short2;

struct ChargePos {
  GlobalPad gpad;
  Timestamp time;
};

using local_id = short2;

GPUconstexpr() float CHARGE_THRESHOLD = 0.f;
GPUconstexpr() float OUTER_CHARGE_THRESHOLD = 0.f;
GPUconstexpr() float QTOT_THRESHOLD = 500.f;
GPUconstexpr() int MIN_SPLIT_NUM = 1;

} // namespace gpu
} // namespace GPUCA_NAMESPACE

#include "Digit.h"
#include "ClusterNative.h"

#endif