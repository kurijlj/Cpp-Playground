#pragma once

// Related Header
#include "LoggingServiceBase.hxx"

// C++ Standard Library
#include <string>

namespace LoggingService {
	class ConsoleLoggingService: public LoggingServiceBase {
	public:
		explicit ConsoleLoggingService(const String& module_name)
			: module_name_{module_name} { }
        ~ConsoleLoggingService() override = default;

	protected:
		void OnLog(
			const SeverityLevel::Severity& severity,
			const String message
		) override;

	protected:
		String module_name_;
	};
};

// End of `ConsoleLoggingService.hxx'
