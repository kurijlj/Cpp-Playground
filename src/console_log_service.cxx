#include <console_log_service.hxx>

#include <ctime>

#include <iostream>

void
LogService::ConsoleLogService::OnLog(
	const LogSeverity severity,
	const String message
) {
	time_t current_time = time(nullptr);
	char time_stamp[30];
	ctime_s(
		time_stamp,
		sizeof time_stamp,
		&current_time
	);

	std::cout << time_stamp << " "
		<< module_name_ << ": "
		<< toString(severity) << " "
		<< message << "\n";
}

// End of 'console_log_service.cxx'
