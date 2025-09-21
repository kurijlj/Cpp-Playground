// ============================================================================
//
// File:        hello_world_strategy.cpp
// Description: Strategy implementation
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
// * hello_world_strategy.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers Include Section
// ============================================================================

// Related header
#include "hello_world_strategy.hxx"


// ============================================================================
// Strategy Definition Section
// ============================================================================

int
HelloWorldStrategy::operator()(
	CliActions::CliAction const& action
) const {
    // Print "Hello, World!" message
    std::cout << "Hello, World!" << std::endl;

	return EXIT_SUCCESS;
}

// End of `hello_world_strategy.cpp'
