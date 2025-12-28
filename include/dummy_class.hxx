#pragma once

#include "log_service.hxx"

#include <optional>
#include <variant>
#include <memory>

namespace DummyClass {
	LogService::Logger default_logger = LogService::NoLogService{};
	LogService::Logger& dummy_logger = default_logger;

	class DummyClass {
	public:
		DummyClass() : m_Identifier{"None"}
		{
			LogService::debug(
				dummy_logger,
				m_Identifier + "->Default constructor call"
			);
		}

		DummyClass(const LogService::String& identifier)
			: m_Identifier(identifier)
		{
			LogService::debug(
				dummy_logger,
				m_Identifier + "->Parametric constructor call"
			);
		}

		DummyClass(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			LogService::debug(
				dummy_logger,
				m_Identifier + "->Copy constructor call"
			);
		}

		DummyClass(DummyClass&& other)
		{
			if (this != &other) {
	            // Free old memory
				m_Identifier = "None";
	            // Steal the pointer
	            m_Identifier = other.m_Identifier;
	            // Set source to null
	            other.m_Identifier = "None"; 
	        }

			LogService::debug(
				dummy_logger,
				m_Identifier + "->Move constructor call"
			);
		}

		~DummyClass ()
		{
			LogService::debug(
				dummy_logger,
				m_Identifier + "->Destructor call"
			);
		}


		DummyClass& operator=(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			LogService::debug(
				dummy_logger,
				m_Identifier + "->Copy assignment call"
			);

			return *this;
		}

		DummyClass& operator=(DummyClass&& other)
		{
			if (this != &other) {
	            // Free old memory
				m_Identifier = "None";
	            // Steal the pointer
	            m_Identifier = other.m_Identifier;
	            // Set source to null
	            other.m_Identifier = "None"; 
	        }

			LogService::debug(
				dummy_logger,
				m_Identifier + "->Move assignment call"
			);

			return *this;
		}

	protected:
		LogService::String m_Identifier;
	};
};

// End of `dummy_class.hxx'
