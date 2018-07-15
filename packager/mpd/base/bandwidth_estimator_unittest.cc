// Copyright 2014 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include "packager/mpd/base/bandwidth_estimator.h"

#include <gtest/gtest.h>

namespace shaka {

namespace {
const uint64_t kBitsInByte = 8;
}  // namespace

TEST(BandwidthEstimatorTest, AllBlocks) {
  BandwidthEstimator be;
  const uint64_t kNumBlocksToAdd = 100;
  const double kDuration = 1.0;
  uint64_t total_bytes = 0;
  for (uint64_t i = 1; i <= kNumBlocksToAdd; ++i) {
    be.AddBlock(i, kDuration);
    total_bytes += i;
  }

  const uint64_t kExptectedEstimate =
      total_bytes * kBitsInByte / kNumBlocksToAdd;
  EXPECT_EQ(kExptectedEstimate, be.Estimate());
  const uint64_t kMax = kNumBlocksToAdd * kBitsInByte;
  EXPECT_EQ(kMax, be.Max());
}

} // namespace shaka
