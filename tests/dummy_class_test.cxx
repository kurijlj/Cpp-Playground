#include <dummy_class.hxx>

#include <gtest/gtest.h>

TEST(DummyClassTest, FiveTest) {
	LogService::LogRecord expected = {
		LogService::String{
			"DUMMY_CLASS: DEBUG None->Default constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG B->Parametric constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG B->Copy constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG D->Parametric constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG E->Parametric constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG E->Move constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG None->Destructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG None->Default constructor call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG B->Copy assignment call"
		},
		LogService::String{
			"DUMMY_CLASS: DEBUG B->Move assignment call"
		},
	};

	LogService::Logger logger = LogService::TraceableLogService{"DUMMY_CLASS"};
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