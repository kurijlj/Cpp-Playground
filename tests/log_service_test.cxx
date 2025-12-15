#include <traceable_log_service.hxx>

#include <gtest/gtest.h>

class TraceableLogServiceTest: public testing::Test {
protected:
	LogService::TraceableLogService log{"TRACEABLE_TEST"};
};

TEST_F(TraceableLogServiceTest, LogMessageDispatchTest) {
	LogService::LogRecord expected = {
		LogService::String{
			"TRACEABLE_TEST: EMERGENCY This is an emergency message"
		},
		LogService::String{
			"TRACEABLE_TEST: ALERT This is an alert message"
		},
		LogService::String{
			"TRACEABLE_TEST: CRITICAL This is an critical message"
		},
		LogService::String{
			"TRACEABLE_TEST: ERROR This is an error message"
		},
		LogService::String{
			"TRACEABLE_TEST: WARNING This is an warning message"
		},
		LogService::String{
			"TRACEABLE_TEST: NOTICE This is an notice message"
		},
		LogService::String{
			"TRACEABLE_TEST: INFO This is an info message"
		},
		LogService::String{
			"TRACEABLE_TEST: DEBUG This is an debug message"
		}
	};
	log.Emergency("This is an emergency message");
	log.Alert("This is an alert message");
	log.Critical("This is an critical message");
	log.Error("This is an error message");
	log.Warning("This is an warning message");
	log.Notice("This is an notice message");
	log.Info("This is an info message");
	log.Debug("This is an debug message");

	EXPECT_EQ(expected, log.record());
}

// End of 'log_service_test.cxx'
