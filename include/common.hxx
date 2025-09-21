// ============================================================================
//
// File:        common.hxx
// Description: Provides project-wide definitions.
//
// This file is part of `C++ Playground'.
// 
// Copyright (C) 2025 Ljubomir Kurij <ljubomir_kurij@proton.me>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// ============================================================================


// ============================================================================
//
// 2025-09-21 Ljubomir Kurij <ljubomir_kurij@proton.me>
//
// * common.hxx: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Macro Definitions Section
// ============================================================================

#define PROJECT_VERSION_MAJOR 
/* #undef PROJECT_VERSION_MINOR */
/* #undef PROJECT_VERSION_PATCH */
#define USE_DEBUG ON

// ============================================================================
// Headers Include Section
// ============================================================================

// Standard library headers
#include <cstdlib>
#include <iostream>
#include <string>

// External library headers
#include <clipp.h>


// ============================================================================
// Project Wide Global Constants Definition Section
// ============================================================================

// ----------------------------------------------------------------------------
// Project Documentation Section
// ----------------------------------------------------------------------------
static constexpr auto kYearString      = "2025";
static constexpr auto kVersionString   = "1.0.0";
static constexpr auto kAuthorName      = "Ljubomir Kurij";
static constexpr auto kAuthorEmail     = "ljubomir_kurij@proton.me";
static constexpr auto kCopyrightHolder = "Ljubomir Kurij";
static constexpr auto kLicense         = "\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n";

// ----------------------------------------------------------------------------
// CLI Options Global Documentation Section
// ----------------------------------------------------------------------------
static constexpr std::string_view kHelpOptionDoc = "\
show this help message and exit";
static constexpr std::string_view kUsageOptionDoc = "\
give a short usage message";
static constexpr std::string_view kVersionOptionDoc = "print program version";


// End of `common.hxx'
