#include <console_log_service.hxx>

#include <ctime>

#include <iostream>

void
LogService::ConsoleLogService::OnLog(
	const SeverityLevel::Severity& severity,
	const String message
) {
	time_t current_time = time(nullptr);
	constexpr size_t buffer_size{30};
	char time_stamp[buffer_size] {0};
	ctime_s(time_stamp, buffer_size, &current_time);
	time_stamp[24] = 0;  // Delete new line char at the end

	std::cout << time_stamp << " " << module_name_ << ": "
		<< severity << " " << message << "\n";
}

// End of 'console_log_service.cxx'
