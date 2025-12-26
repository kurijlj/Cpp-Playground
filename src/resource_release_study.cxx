#include <dummy_class.hxx>

#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	using String = std::string;
	using DataSet = std::vector<DummyClass::DummyClass>;
	using DataStack = std::vector<DataSet>;

	DummyClass::ConsoleLogServicePointer spLogger
		= std::make_shared<
			LogService::ConsoleLogService
		>("RESOURCE_RELEASE");
	DummyClass::dummy_log = spLogger;

	spLogger->Debug("Initializing data set 1 ...");
	DataSet ds1;
	ds1.push_back(std::move(DummyClass::DummyClass{"A"}));
	ds1.push_back(std::move(DummyClass::DummyClass{"B"}));

	spLogger->Debug("Initializing data set 2 ...");
	DataSet ds2;
	ds2.push_back(std::move(DummyClass::DummyClass{"C"}));
	ds2.push_back(std::move(DummyClass::DummyClass{"D"}));

	spLogger->Debug("Initializing data stack ...");
	DataStack dstk;

	spLogger->Debug("Moving data set 1 to stack ...");
	dstk.push_back(std::move(ds1));

	spLogger->Debug("Moving data set 2 to stack ...");
	dstk.push_back(std::move(ds2));

	spLogger->Debug("Exit ...");

	return EXIT_SUCCESS;
}

// End of file `resource_release_study.cxx'
