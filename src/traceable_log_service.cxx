#include <traceable_log_service.hxx>

#include <sstream>

LogService::LogRecord
LogService::TraceableLogService::record() const {
	return log_record_;
}

void
LogService::TraceableLogService::reset() {
	log_record_.clear();
}

void
LogService::TraceableLogService::OnLog(
	const LogSeverity severity,
	const String message
) {
	std::ostringstream msgStream;

	msgStream << module_name_ << ": "
		<< std::visit(SeverityToString(), severity) << " "
		<< message;

	log_record_.push_back(msgStream.str());
}

// End of 'tracable_log_service.cxx'
