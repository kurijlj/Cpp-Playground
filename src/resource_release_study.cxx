#include "DummyClass/DummyClass.hxx"

#include "LoggingService/ConsoleLoggingService.hxx"
#include "LoggingService/LoggerObject.hxx"
#include "LoggingService/LoggingServiceBase.hxx"

#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    // Silent unused parameter warnings
    (void)argc;
    (void)argv;

    using namespace LoggingService;

	using String = std::string;
	using DataSet = std::vector<DummyClass::DummyClass>;
	using DataStack = std::vector<DataSet>;

	Logger logger = ConsoleLoggingService{"RESOURCE_RELEASE"};
	DummyClass::SetLogger(&logger);

	DebugMessage(
		logger,
		"Initializing data set 1 ..."
	);
	DataSet ds1;
	ds1.push_back(std::move(DummyClass::DummyClass{"A"}));
	ds1.push_back(std::move(DummyClass::DummyClass{"B"}));

	DebugMessage(
		logger,
		"Initializing data set 2 ..."
	);
	DataSet ds2;
	ds2.push_back(std::move(DummyClass::DummyClass{"C"}));
	ds2.push_back(std::move(DummyClass::DummyClass{"D"}));

	DebugMessage(
		logger,
		"Initializing data stack ..."
	);
	DataStack dstk;

	DebugMessage(
		logger,
		"Moving data set 1 to stack ..."
	);
	dstk.push_back(std::move(ds1));

	DebugMessage(
		logger,
		"Moving data set 2 to stack ..."
	);
	dstk.push_back(std::move(ds2));

	DebugMessage(logger, "Exit ...");

	return EXIT_SUCCESS;
}

// End of file `resource_release_study.cxx'
