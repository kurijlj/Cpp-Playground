#include "DummyClass/DummyClass.hxx"

#include "MonadicTypes/MonadicTypes.hxx"

#include "LoggingService/ConsoleLoggingService.hxx"
#include "LoggingService/LoggerObject.hxx"
#include "LoggingService/LoggingServiceBase.hxx"

#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    // Silent unused parameter compiler warnings
    (void)argc;
    (void)argv;

    using namespace LoggingService;

	Logger logger = ConsoleLoggingService{"EITHER_STUDY"};
	DummyClass::SetLogger(&logger);

	// Move dummy to the result
	MonadicTypes::Result<DummyClass::DummyClass> result_a(
		std::in_place_index<1>,
		std::move(DummyClass::DummyClass{"A"})
	);

	// This returns reference to dummy
	std::get<1>(result_a).WhoIsIt();

	auto result_b = MonadicTypes::validate(DummyClass::DummyClass{"B"});

	// This also returns reference to dummy
	std::get<1>(result_b).WhoIsIt();

	// Create named dummy object
	DummyClass::DummyClass dummy_c{"C"};

	// This should make a copy of the dummy
	auto result_c = MonadicTypes::validate(dummy_c);

	// This also returns reference to dummy
	std::get<1>(result_c).WhoIsIt();

	return EXIT_SUCCESS;
}

// End of file `either_study.cxx'
