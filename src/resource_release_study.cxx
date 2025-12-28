#include <dummy_class.hxx>

#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	using String = std::string;
	using DataSet = std::vector<DummyClass::DummyClass>;
	using DataStack = std::vector<DataSet>;

	LogService::Logger logger
		= LogService::ConsoleLogService{"RESOURCE_RELEASE"};
	DummyClass::dummy_logger = logger;

	LogService::debug(logger, "Initializing data set 1 ...");
	DataSet ds1;
	ds1.push_back(std::move(DummyClass::DummyClass{"A"}));
	ds1.push_back(std::move(DummyClass::DummyClass{"B"}));

	LogService::debug(logger, "Initializing data set 2 ...");
	DataSet ds2;
	ds2.push_back(std::move(DummyClass::DummyClass{"C"}));
	ds2.push_back(std::move(DummyClass::DummyClass{"D"}));

	LogService::debug(logger, "Initializing data stack ...");
	DataStack dstk;

	LogService::debug(logger, "Moving data set 1 to stack ...");
	dstk.push_back(std::move(ds1));

	LogService::debug(logger, "Moving data set 2 to stack ...");
	dstk.push_back(std::move(ds2));

	LogService::debug(logger, "Exit ...");

	return EXIT_SUCCESS;
}

// End of file `resource_release_study.cxx'
