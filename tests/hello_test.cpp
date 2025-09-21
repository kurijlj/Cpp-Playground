// ============================================================================
// <one line to give the test's name and a brief idea of what it does.>
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
//
// This file is part of <program_name>.
// 
// <program_name> is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software  Foundation, either version 3 of the License, or (at your option)
// any later version.
// 
// <program_name> is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// <program_name>. If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * <testfilename>.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For how to generate test cases with GoogleTest framework, see:
//   <https://google.github.io/googletest/primer.html>
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// External libraries headers
#include <gtest/gtest.h>  // GoogleTest framework


// ============================================================================
// Test fixtures section
// ============================================================================


// ============================================================================
// Test cases section
// ============================================================================

// ----------------------------------------------------------------------------
// HelloTest
// ----------------------------------------------------------------------------
//
// Description: This test suite demonstrates some basic assertions.
//
// ----------------------------------------------------------------------------

// Case: BasicAssertions ------------------------------------------------------
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}