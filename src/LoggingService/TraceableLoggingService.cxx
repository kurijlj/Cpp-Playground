// Related Header
#include "LoggingService/TraceableLoggingService.hxx"

// Component Headers
#include "LoggingService/LoggingServiceBase.hxx"

// C++ Standard Library
#include <sstream>

// Namespace Usage
using namespace LoggingService;

LogRecord
TraceableLoggingService::Record() const {
	return log_record_;
}

void
TraceableLoggingService::Reset() {
	log_record_.clear();
}

void
TraceableLoggingService::OnLog(
	const SeverityLevel::Severity& severity,
	const String message
) {
	std::ostringstream msgStream;

	msgStream << module_name_ << ": "
		<< severity << " " << message;

	log_record_.push_back(msgStream.str());
}

// End of `TraceableLoggingService.cxx`
