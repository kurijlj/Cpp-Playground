#include <log_service_base.hxx>

LogService::String LogService::toString(const LogSeverity severity) {
	switch (severity) {
		case LogSeverity::EMERGENCY:
			return String{"EMERGENCY"};
		case LogSeverity::ALERT:
			return String{"ALERT"};
		case LogSeverity::CRITICAL:
			return String{"CRITICAL"};
		case LogSeverity::ERROR:
			return String{"ERROR"};
		case LogSeverity::WARNING:
			return String{"WARNING"};
		case LogSeverity::NOTICE:
			return String{"NOTICE"};
		case LogSeverity::INFO:
			return String{"INFO"};
		case LogSeverity::DEBUG:
			return String{"DEBUG"};
	}

	return String{"UNKNOWN SEVERITY"};  // This should never happen
}

// End of 'log_service_base.cxx'
