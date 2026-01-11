#pragma once

// Component Headers
#include "LoggingServiceBase.hxx"

// C++ Standard Library
#include <string>
#include <vector>

namespace LoggingService {
	using LogRecord = std::vector<String>;

	class TraceableLoggingService: public LoggingServiceBase {
	public:
		explicit TraceableLoggingService(const String& module_name)
			: module_name_{module_name} { }

        ~TraceableLoggingService() override = default;
		[[nodiscard]] LogRecord Record() const;
		void Reset();

	protected:
		void OnLog(
			const SeverityLevel::Severity& severity,
			const String message
		) override;

	protected:
		String module_name_;
		LogRecord log_record_;
	};
};

// End of 'TraceableLoggingService.hxx'
