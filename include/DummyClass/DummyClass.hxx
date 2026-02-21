#pragma once

#include "LoggingService/LoggingServiceBase.hxx"
#include "LoggingService/TraceableLoggingService.hxx"
#include "LoggingService/LoggerObject.hxx"

#include <optional>
#include <variant>
#include <memory>

namespace DummyClass {
	using namespace LoggingService;

	extern Logger* dummy_logger;

	void SetLogger(Logger* logger);

	std::optional<LogRecord> GetRecord();

	class DummyClass {
	public:
		DummyClass();

		DummyClass(const String& identifier);

		DummyClass(const DummyClass& other);

		DummyClass(DummyClass&& other);

		~DummyClass();

		DummyClass& operator=(const DummyClass& other);

		DummyClass& operator=(DummyClass&& other);

        bool operator==(const DummyClass& other) const;

        bool operator==(const DummyClass&& other) const;

		void WhoIsIt() const;

	protected:
		void DebugMessage(const String& message) const;

		String m_Identifier;
	};
};

// End of `DummyClass.hxx'
