#include "traceable_log_service.hxx"

LogService::TraceableLogService dummy_log{"DUMMY_CLASS"};

class DummyClass {
public:
	DummyClass() : identifier_{"None"}
	{
		dummy_log.Debug(
			identifier_ + "->Default constructor call"
		);
	}
	DummyClass(const LogService::String& identifier)
		: identifier_(identifier)
	{
		dummy_log.Debug(
			identifier_ + "->Parametric constructor call"
		);
	}
	DummyClass(const DummyClass& other)
	{
		identifier_ = other.identifier_;
		dummy_log.Debug(
			identifier_ + "->Copy constructor call"
		);
	}
	DummyClass(DummyClass&& other)
	{
		if (this != &other) {
            // Free old memory
			identifier_ = "None";
            // Steal the pointer
            identifier_ = other.identifier_;
            // Set source to null
            other.identifier_ = "None"; 
        }
		dummy_log.Debug(
			identifier_ + "->Move constructor call"
		);
	}
	~DummyClass ()
	{
		dummy_log.Debug(
			identifier_ + "->Destructor call"
		);
	}

	DummyClass& operator=(const DummyClass& other)
	{
		identifier_ = other.identifier_;

		dummy_log.Debug(
			identifier_ + "->Copy assignment call"
		);

		return *this;
	}
	DummyClass& operator=(DummyClass&& other)
	{
		if (this != &other) {
            // Free old memory
			identifier_ = "None";
            // Steal the pointer
            identifier_ = other.identifier_;
            // Set source to null
            other.identifier_ = "None"; 
        }
		dummy_log.Debug(
			identifier_ + "->Move assignment call"
		);

		return *this;
	}

protected:
	LogService::String identifier_;
};

// End of `dummy_class.hxx'
