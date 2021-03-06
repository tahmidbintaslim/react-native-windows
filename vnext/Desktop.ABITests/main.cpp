// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "gtest/gtest.h"
#include "motifCpp/gTestAdapter.h"

int main(int argc, char **argv) {
  Mso::UnitTests::GTest::RegisterUnitTests();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
