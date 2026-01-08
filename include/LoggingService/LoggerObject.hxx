#pragma once

// Component Headers
#include "LoggingServiceBase.hxx"
#include "ConsoleLoggingService.hxx"
#include "TraceableLoggingService.hxx"

// C++ Standard Library Headers
#include <optional>
#include <string>
#include <variant>

namespace LoggingService {
	using Logger = std::variant<
		NoLoggingService,
		ConsoleLoggingService,
		TraceableLoggingService
	>;

	class Alert {
	public:
		explicit Alert(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Critical {
	public:
		explicit Critical(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Debug {
	public:
		explicit Debug(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Emergency {
	public:
		explicit Emergency(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Error {
	public:
		explicit Error(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Info {
	public:
		explicit Info(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Notice {
	public:
		explicit Notice(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	class Record {
	public:
		Record() = default;

		std::optional<LogRecord> operator()(
            const NoLoggingService& obj
        ) const;
		std::optional<LogRecord> operator()(
            const ConsoleLoggingService& obj
        ) const;
		std::optional<LogRecord> operator()(
			const TraceableLoggingService& obj
		) const;
	};

	class Reset {
	public:
		Reset() = default;

		void operator()(const NoLoggingService& obj) const;
		void operator()(const ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;
	};

	class Warning {
	public:
		explicit Warning(const String& message) : message_{message} { }

		void operator()(const NoLoggingService& obj) const;
		void operator()(ConsoleLoggingService& obj) const;
		void operator()(TraceableLoggingService& obj) const;

	private:
		const String message_;
	};

	void AlertMessage(Logger& obj, const String& message);
	void CriticalMessage(Logger& obj, const String& message);
	void DebugMessage(Logger& obj, const String& message);
	void EmergencyMessage(Logger& obj, const String& message);
	void ErrorMessage(Logger& obj, const String& message);
	std::optional<LogRecord> GetRecord(const Logger& obj);
	void InfoMessage(Logger& obj, const String& message);
	void NoticeMessage(Logger& obj, const String& message);
	void ResetRecord(Logger& obj);
	void WarningMessage(Logger& obj, const String& message);
};

// End of file `LoggerObject.hxx'
