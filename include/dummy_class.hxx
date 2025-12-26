#pragma once

#include "console_log_service.hxx"
#include "traceable_log_service.hxx"

#include <optional>
#include <variant>
#include <memory>

namespace DummyClass {
	using namespace LogService;
	using ConsoleLogServicePointer = std::shared_ptr<ConsoleLogService>;
	using TraceableLogServicePointer = std::shared_ptr<TraceableLogService>;

	struct NoLogService {};

	std::variant<
		NoLogService,
		ConsoleLogServicePointer,
		TraceableLogServicePointer
	> dummy_log{NoLogService{}};

	class DebugMessageDispatcher{
	public:
		DebugMessageDispatcher(const String& message) : m_Message{message} { }

		void operator()(const NoLogService&) const
		{
			return;
		}
		void operator()(const ConsoleLogServicePointer& spLogService) const
		{
			return spLogService->Debug(m_Message);
		}
		void operator()(const TraceableLogServicePointer& spLogService) const
		{
			return spLogService->Debug(m_Message);
		}

	private:
		const String m_Message;
	};

	class DummyClass {
	public:
		DummyClass() : m_Identifier{"None"}
		{
			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Default constructor call"
			};
			std::visit(logDebugMessage, dummy_log);
		}

		DummyClass(const LogService::String& identifier)
			: m_Identifier(identifier)
		{
			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Parametric constructor call"
			};
			std::visit(logDebugMessage, dummy_log);
		}

		DummyClass(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Copy constructor call"
			};
			std::visit(logDebugMessage, dummy_log);
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

			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Move constructor call"
			};
			std::visit(logDebugMessage, dummy_log);
		}

		~DummyClass ()
		{
			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Destructor call"
			};
			std::visit(logDebugMessage, dummy_log);
		}


		DummyClass& operator=(const DummyClass& other)
		{
			m_Identifier = other.m_Identifier;

			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Copy assignment call"
			};
			std::visit(logDebugMessage, dummy_log);

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

			const DebugMessageDispatcher logDebugMessage{
				m_Identifier + "->Move assignment call"
			};
			std::visit(logDebugMessage, dummy_log);

			return *this;
		}

	protected:
		String m_Identifier;
	};
};

// End of `dummy_class.hxx'
