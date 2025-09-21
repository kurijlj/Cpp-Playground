// ============================================================================
//
// File:        cli_template_app.cpp
// Description: Main application file for the CLI Template App
//
// This file is part of `C++ Playground'
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
// * cli_template_app.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers Include Section
// ============================================================================

// Project library headers
#include "cli_actions.hxx"
#include "cli_template_app.hxx"
#include "hello_world_strategy.hxx"

// Standard library headers
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <filesystem>

int main(int argc, char** argv)
{    
    namespace fs = std::filesystem;  // Define a shorter alias for filesystem
    using Action = CliActions::CliAction;
    using ActionPointer = std::unique_ptr<Action>;

    // Determine the exec name under wich program is beeing executed
    std::string execName = fs::path(argv[0]).filename().string();

    // Parse command line options
    auto result = clipp::parse(argc, argv, appOptions);

    // Reference to a program action that will be executed
    ActionPointer programAction;

    // Check for the unsupported options --------------------------------------
    if (!userOptionValues.m_Unsupported.empty())
    {
        programAction
            = std::make_unique<CliActions::CliAction> (
                execName,
                CliActions::UnsupportedOptionsStrategyClipp(
                    userOptionValues.m_Unsupported
                )
            );
    }

    // Check for high priority switches ---------------------------------------
    // (i.e. '--help', '--usage', '--version')
    else if (userOptionValues.m_ShowHelp)
    {
        // Check if the help switch was triggered. We give help switch the
        // highest priority, so if it is triggered we don't need to check
        // anything else.
        programAction = std::make_unique<Action> (
            execName,
            CliActions::ShowHelpStrategyClipp(
                appOptions,
                kAppDoc,
                kAuthorEmail
            )
        );
    }
    else if (userOptionValues.m_PrintUsage)
    {
        // Check if the usage switch was triggered. Usge switch has the second
        // highest priority, so if it is triggered we don't need to check
        // anything else.
        auto fmt = clipp::doc_formatting {}
            .first_column(CliActions::DEFAULT_PAGE_IDENT)
            .last_column(CliActions::DEFAULT_PAGE_WIDTH);
        programAction = std::make_unique<Action> (
            execName,
            CliActions::ShowUsageStrategyClipp(appOptions, fmt)
        );
    }
    else if (userOptionValues.m_ShowVersion)
    {
        // Check if the version switch was triggered. Version switch has the
        // third highest priority.
        programAction = std::make_unique<Action> (
            execName,
            CliActions::ShowVersionInfoStrategy (
                kVersionString,
                kYearString,
                kCopyrightHolder,
                kLicense
            )
        );
    }
    // No high priority switch was passed. Proceed with normal execution
    programAction = std::make_unique<Action> (
        execName,
        HelloWorldStrategy()
    );

    return programAction->execute();
}

// End of `cli_template_app.cpp`
