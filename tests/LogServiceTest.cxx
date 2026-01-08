// Component Headers
#include "LoggerObject.hxx"
#include "LoggingServiceBase.hxx"
#include "TraceableLoggingService.hxx"

// C++ Standard Library Headers
#include <optional>
#include <string>

// External Headers
#include <gtest/gtest.h>

// Namspeace Usage
using namespace LoggingService;

class TraceableLogServiceTest: public testing::Test {
protected:
    Logger logger = TraceableLoggingService{"TRACEABLE_TEST"};
};

TEST_F(TraceableLogServiceTest, LogMessageDispatchTest) {
	LogRecord expected = {
		String{
			"TRACEABLE_TEST: ALERT This is an alert message"
		},
		String{
			"TRACEABLE_TEST: CRITICAL This is an critical message"
		},
		String{
			"TRACEABLE_TEST: DEBUG This is an debug message"
		},
		String{
			"TRACEABLE_TEST: EMERGENCY This is an emergency message"
		},
		String{
			"TRACEABLE_TEST: ERROR This is an error message"
		},
		String{
			"TRACEABLE_TEST: INFO This is an info message"
		},
		String{
			"TRACEABLE_TEST: NOTICE This is an notice message"
		},
		String{
			"TRACEABLE_TEST: WARNING This is an warning message"
		}
	};
	AlertMessage(logger, "This is an alert message");
	CriticalMessage(logger, "This is an critical message");
	DebugMessage(logger, "This is an debug message");
	EmergencyMessage(logger, "This is an emergency message");
	ErrorMessage(logger, "This is an error message");
	InfoMessage(logger, "This is an info message");
	NoticeMessage(logger, "This is an notice message");
	WarningMessage(logger, "This is an warning message");

	EXPECT_EQ(expected, GetRecord(logger).value());

    ResetRecord(logger);

    EXPECT_EQ(LogRecord{}, GetRecord(logger).value());
}

// End of 'LogServiceTest.cxx'
