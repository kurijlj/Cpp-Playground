// ============================================================================
//
// File:        cli_actions.hxx
// Description: Function objects encapsulating various CLI program actions to be
//              called based on the user input from CLI, and strategy
//              implementations for specified actions
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
// * cli_actions.hxx: created.
//
// ============================================================================

#pragma once

// ============================================================================
// Headers Include Section
// ============================================================================

// Project library headers
#include "common.hxx"

// Standard library headers
#include <functional>
#include <iostream>
#include <string_view>

// External library headers
#include <clipp.h>

// ============================================================================
// Action and Common Strategies Section
// ============================================================================

namespace CliActions {
	constexpr int DEFAULT_PAGE_IDENT{0};
	constexpr int DEFAULT_PAGE_WIDTH{79};

	// ------------------------------------------------------------------------
	// CliAction
	// ------------------------------------------------------------------------
	//
	// Description: Command-line action wrapper using the strategy pattern for
	//              flexible execution.
	//
    //              Accepts a callable strategy at construction that defines how
    //              the action executes. The strategy receives the action
    //              instance and an execution name identifier.
	//
	// ------------------------------------------------------------------------
	class CliAction {
	public:
		using ExecutiveStrategy = std::function<int(CliAction const&)>;

		explicit CliAction(
			std::string_view const& exec_name,
			ExecutiveStrategy executor
		) : m_ExecName{exec_name},
			m_Executor{std::move(executor)}
		{ }

		int execute() const {
			return m_Executor(*this);
		}

		std::string_view execName() const {
			return std::string_view{this->m_ExecName};
		}

	private:
		const std::string m_ExecName;
		const ExecutiveStrategy m_Executor;
	};

	// ------------------------------------------------------------------------
	// BaseStrategy
	// ------------------------------------------------------------------------
	//
	// Description: Abstract base class for functional objects. All derived
	//              classes must implement the call operator.
	//
	// ------------------------------------------------------------------------
	class BaseStrategy {
	public:
	    // Virtual destructor for proper cleanup of derived classes
	    virtual ~BaseStrategy() = default;
	
	    // Pure virtual function that must be implemented by derived classes
	    // Takes two const reference arguments and must be overridden
	    virtual int operator()(CliAction const& action) const = 0;
		
	protected:
	    // Protected constructor prevents direct instantiation
	    BaseStrategy () = default;
		
	    // Allow derived classes to use default copy/move operations
	    BaseStrategy (BaseStrategy  const&) = default;
	    BaseStrategy (BaseStrategy &&) = default;
	    BaseStrategy & operator=(BaseStrategy const&) = default;
	    BaseStrategy & operator=(BaseStrategy &&) = default;
	};

	// ------------------------------------------------------------------------
	// ShowHelpStrategyClipp
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying help information about the program
	//
	// ------------------------------------------------------------------------
	class ShowHelpStrategyClipp : public BaseStrategy {
	public:
		explicit ShowHelpStrategyClipp(
			clipp::group const& group,
			std::string_view const& app_doc,
			std::string_view const& author_email
		) : m_Group(group),
			m_AppDoc(app_doc),
			m_AuthorEmail(author_email)
		{ }
	
		// Shows help information
		int operator()(CliAction const& action) const override {
			auto fmt = clipp::doc_formatting{}
				.first_column(DEFAULT_PAGE_IDENT)
				.last_column(DEFAULT_PAGE_WIDTH);
			clipp::man_page man;
			
			man.prepend_section(
				"USAGE",
				clipp::usage_lines(
					m_Group,
					std::string {action.execName()},
					fmt
				).str()
			);
			man.append_section("", std::string {m_AppDoc});
			man.append_section(
				"",
				clipp::documentation(m_Group, fmt).str()
			);
			man.append_section(
				"",
				"Report bugs to <" + std::string {m_AuthorEmail} + ">."
			);
		
			std::cout << man;
		
			return EXIT_SUCCESS;
		}
  
	private:
		clipp::group m_Group;
		std::string m_AppDoc;
		std::string m_AuthorEmail;
	};

	// ------------------------------------------------------------------------
	// ShowShortHelpStrategy
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying short help information
	//              about the program
	//
	// -------------------------------------------------------------------------
	class ShowShortHelpStrategy : public BaseStrategy {
	public:
		explicit ShowShortHelpStrategy() = default;

		// Shows short help message
		int operator()(CliAction const& action) const override {
			std::cout << "\n";

			// Print short help message
			std::cout << "Try '"
				<< action.execName()
				<< " --help' for more information.\n";

			return EXIT_FAILURE;
		}
	};

	// ------------------------------------------------------------------------
	// ShowUsageStrategyClipp
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying usage information about the program
	//
	// ------------------------------------------------------------------------
	class ShowUsageStrategyClipp : public BaseStrategy {
	public:
		explicit ShowUsageStrategyClipp(
			clipp::group const& group,
			clipp::doc_formatting const& fmt = clipp::doc_formatting{}
		) : m_Group(group), m_Format(fmt)
		{ }

		// Shows usage information
		int operator()(CliAction const& action) const override {
			std::cout << clipp::usage_lines(
				m_Group,
				std::string {action.execName()},
				m_Format
			) << "\n";

		  return EXIT_SUCCESS;
		}

	private:
		clipp::group m_Group;
		clipp::doc_formatting m_Format;
	};

	// ------------------------------------------------------------------------
	// ShowVersionInfoStrategy
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying version information about
	//              the program
	//
	// ------------------------------------------------------------------------
	class ShowVersionInfoStrategy : public BaseStrategy {
	public:
		explicit ShowVersionInfoStrategy(
			std::string_view const& app_version,
			std::string_view const& release_year,
			std::string_view const& author_name,
			std::string_view const& license
		) : m_AppVersion(app_version),
			m_ReleaseYear(release_year),
			m_AuthorName(author_name),
			m_License(license)
		{ }

		// Shows version information
		int operator()(CliAction const& action) const override {
			std::cout << action.execName() << " "
				<< m_AppVersion << " Copyright (C) "
				<< m_ReleaseYear << " "
				<< m_AuthorName << "\n"
				<< m_License;

			return EXIT_SUCCESS;
		}

	private:
		std::string m_AppVersion;
		std::string m_ReleaseYear;
		std::string m_AuthorName;
		std::string m_License;
	};

	// ------------------------------------------------------------------------
	// UnsupportedOptionsClippStrategy
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying aggregated unsupported options
	//              and short help message about the program using
	//              Clipp library
	//
	// ------------------------------------------------------------------------
	class UnsupportedOptionsStrategyClipp : public BaseStrategy {
	public:
		explicit UnsupportedOptionsStrategyClipp(
			std::vector<std::string> const& unsupported_options
		) : m_UnsupportedOptions(unsupported_options) { }

		// Shows aggregated unsupported options and short help message
		int operator()(CliAction const& action) const override {
			std::cerr << action.execName() << ": Unsupported options: ";
			for (const auto& opt : m_UnsupportedOptions) {
				std::cerr << opt << " ";
			}
			std::cerr << "\n";

			// Print short help message
			std::cout << "Try '" << action.execName()
				<< " --help' for more information.\n";

			return EXIT_FAILURE;
		}

	private:
		std::vector<std::string> const& m_UnsupportedOptions;
	};

	// ------------------------------------------------------------------------
	// MissingArgumentStrategyClipp
	// ------------------------------------------------------------------------
	//
	// Description: Strategy for displaying error on missing argument
	//
	// ------------------------------------------------------------------------
	class MissingArgumentStrategyClipp : public BaseStrategy {
	public:
		explicit MissingArgumentStrategyClipp(
			std::string_view const& errorMessage,
			clipp::group const& group,
			clipp::doc_formatting const& fmt = clipp::doc_formatting{}
		) : m_ErrorMessage(errorMessage), m_Group(group), m_Format(fmt)
		{ }

		// Shows error message and short usage
		int operator()(CliAction const& action) const override {
			std::cerr << action.execName() << ": ERROR: "
				<< m_ErrorMessage << "\n";
			std::cout << "Usage: " << clipp::usage_lines(
				m_Group,
				std::string {action.execName()},
				m_Format
			) << "\n";

		  return EXIT_FAILURE;
		}

	private:
		std::string m_ErrorMessage;
		clipp::group m_Group;
		clipp::doc_formatting m_Format;
	};

};

// End of `cli_actions.hxx`
