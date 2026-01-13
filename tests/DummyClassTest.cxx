#include "DummyClass/DummyClass.hxx"

#include <gtest/gtest.h>

using namespace LoggingService;

TEST(DummyClassTest, FiveTest) {
	LogRecord expected = {
		String{
			"DUMMY_CLASS: DEBUG None->Default constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG B->Parametric constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG B->Copy constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG D->Parametric constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG E->Parametric constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG E->Move constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG None->Destructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG None->Default constructor call"
		},
		String{
			"DUMMY_CLASS: DEBUG B->Copy assignment call"
		},
		String{
			"DUMMY_CLASS: DEBUG B->Move assignment call"
		},
	};

	Logger logger = TraceableLoggingService{"DUMMY_CLASS"};
	DummyClass::SetLogger(&logger);

	DummyClass::DummyClass A{},
		B{"B"},
		C(B),
		D(DummyClass::DummyClass{"D"}),
		E = std::move(DummyClass::DummyClass{"E"}),
		F{};

	A = B;
	F = std::move(C);
	
	EXPECT_EQ(
		expected,
		DummyClass::GetRecord()
	);
}


// End of `DummyClassTest.cxx'
