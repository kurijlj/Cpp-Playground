#pragma once

#include "log_service_base.hxx"
#include "console_log_service.hxx"
#include "traceable_log_service.hxx"

#include <variant>

namespace LogService {
	using Logger = std::variant<
		NoLogService,
		ConsoleLogService,
		TraceableLogService
	>;

	class Emergency {
	public:
		explicit Emergency(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Alert {
	public:
		explicit Alert(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Critical {
	public:
		explicit Critical(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Error {
	public:
		explicit Error(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Warning {
	public:
		explicit Warning(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Notice {
	public:
		explicit Notice(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Info {
	public:
		explicit Info(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Debug {
	public:
		explicit Debug(const String& message) : message_{message} { }

		void operator()(const NoLogService& obj) const;
		void operator()(ConsoleLogService& obj) const;
		void operator()(TraceableLogService& obj) const;

	private:
		const String message_;
	};

	class Record {
	public:
		Record() = default;

		LogRecord operator()(const NoLogService& obj) const;
		LogRecord operator()(const ConsoleLogService& obj) const;
		LogRecord operator()(
			const TraceableLogService& obj
		) const;
	};

	void EmergencyMessage(Logger& obj, const String& message);
	void AlertMessage(Logger& obj, const String& message);
	void CriticalMessage(Logger& obj, const String& message);
	void ErrorMessage(Logger& obj, const String& message);
	void WarningMessage(Logger& obj, const String& message);
	void NoticeMessage(Logger& obj, const String& message);
	void InfoMessage(Logger& obj, const String& message);
	void DebugMessage(Logger& obj, const String& message);
	LogRecord GetRecord(const Logger& obj);
};

// End of file `log_service.hxx'
