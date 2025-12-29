#include <traceable_log_service.hxx>

#include <sstream>

LogService::LogRecord
LogService::TraceableLogService::Record() const {
	return log_record_;
}

void
LogService::TraceableLogService::Reset() {
	log_record_.clear();
}

void
LogService::TraceableLogService::OnLog(
	const SeverityLevel::Severity& severity,
	const String message
) {
	std::ostringstream msgStream;

	msgStream << module_name_ << ": "
		<< severity << " " << message;

	log_record_.push_back(msgStream.str());
}

// End of 'tracable_log_service.cxx'
