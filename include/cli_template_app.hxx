// ============================================================================
//
// File:        cli_template_app.hxx
// Description: App wide global constants and variables for `cli_template_app',
//              and user options parser configuration
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
// * cli_template_app.hxx: created.
//
// ============================================================================


// Project headers
#include "common.hxx"

// External library headers
#include <clipp.h>


// ============================================================================
// CLI Options Documentation Section
// ============================================================================

static constexpr std::string_view kAppName = "cli_template_app";
static constexpr std::string_view kAppDoc = "\
A small CLI program to demonstrate the use of the framework.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n";


// ============================================================================
// CLI Options Data Structure Section
// ============================================================================

// Define the data structure to store user selected (parsed) option values.
// We use the same data structure to define, and store the default
// option values
struct CliOptionValues
{
    std::vector<std::string> m_Unsupported;  // Store parsed options that do
                                              // not fit any of the provided
                                              // options
    bool m_ShowHelp;
    bool m_PrintUsage;
    bool m_ShowVersion;
};

// Define the default values for the command line options
static CliOptionValues userOptionValues
{
    {},     // m_Unsupported
    false,  // m_ShowHelp
    false,  // m_PrintUsage
    false   // m_ShowVersion
};


// ============================================================================
// Parser Setup Section
// ============================================================================

auto appOptions = (
    // Define the command line options and their default values.
    // - Must have more than one option.
    // - The order of the options is important.
    // - The order of the options in the group is important.
    // - Take care not to omitt value filter when parsing file
    //   and directory names. Otherwise, the parser will treat options
    //   as values.
    // - Define positional arguments first
    // - Define positional srguments as optional to enforce
    //   the priority of help, usage and version switches. Then enforce
    //   the required positional arguments by checking if their
    //   values are set.
    (
        (
            clipp::option("-h", "--help")
                .set(userOptionValues.m_ShowHelp)
        ).doc(kHelpOptionDoc.data()),
        (
            clipp::option("--usage")
                .set(userOptionValues.m_PrintUsage)
        ).doc(kUsageOptionDoc.data()),
        (
            clipp::option("-V", "--version")
                .set(userOptionValues.m_ShowVersion)
        ).doc(kVersionOptionDoc.data())
    ).doc("general options:"),
    clipp::any_other(userOptionValues.m_Unsupported)
);

// End of 'cli_template_app.hxx'
