// Related Header
#include "LoggingService/ConsoleLoggingService.hxx"

// Component Headers
#include "LoggingService/LoggingServiceBase.hxx"

// C Standard Library
#include <ctime>

// C++ Standard Library
#include <iostream>
#include <iterator>

// Namespace Usage
using namespace LoggingService;

void
ConsoleLoggingService::OnLog(
	const SeverityLevel::Severity& severity,
	const String message
) {
	std::time_t current_time = std::time({});
	constexpr size_t buffer_size{std::size("yyyy-mm-ddThh:mm:ss") + 1};
	char time_stamp[buffer_size] {0};
    std::strftime(
        std::data(time_stamp),
        buffer_size,
        "%FT%T",
        std::localtime(&current_time)
    );

	std::cout << time_stamp << " " << module_name_ << ": "
		<< severity << " " << message << "\n";
}

// End of 'ConsoleLoggingService.cxx'
