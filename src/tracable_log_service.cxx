#include <tracable_log_service.hxx>

#include <sstream>

LogService::LogRecord
LogService::TracableLogService::record() const {
	return log_record_;
}

void
LogService::TracableLogService::reset() {
	log_record_.clear();
}

void
LogService::TracableLogService::OnLog(
	const LogSeverity severity,
	const String message
) {
	std::ostringstream msgStream;

	msgStream << module_name_ << ": "
		<< toString(severity) << " "
		<< message;

	log_record_.push_back(msgStream.str());
}

// End of 'tracable_log_service.cxx'
