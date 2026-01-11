#pragma once

#include "LoggingServiceBase.hxx"
#include "TraceableLoggingService.hxx"
#include "LoggerObject.hxx"

#include <optional>
#include <variant>
#include <memory>

using namespace LoggingService;

namespace DummyClass {
	Logger* dummy_logger{nullptr};

	void SetLogger(Logger* logger) {
		dummy_logger = logger;
	}

	std::optional<LogRecord> GetRecord() {
		return GetRecord(*dummy_logger);
	}

	class DummyClass {
	public:
		DummyClass() : m_Identifier{"None"}
		{
			DebugMessage("->Default constructor call");
		}

		DummyClass(const String& identifier)
			: m_Identifier(identifier)
		{
			DebugMessage("->Parametric constructor call");
		}

		DummyClass(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			DebugMessage("->Copy constructor call");
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

			DebugMessage("->Move constructor call");
		}

		~DummyClass ()
		{
			DebugMessage("->Destructor call");
		}


		DummyClass& operator=(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			DebugMessage("->Copy assignment call");
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

			DebugMessage("->Move assignment call");

			return *this;
		}

	protected:
		void DebugMessage(
			const String& message
		)
		{
			if (nullptr != dummy_logger) {
				LoggingService::DebugMessage(
					*dummy_logger,
					m_Identifier + message
				);
			}
		}

	protected:
		String m_Identifier;
	};
};

// End of `DummyClass.hxx'
