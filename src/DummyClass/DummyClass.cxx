#include "DummyClass/DummyClass.hxx"

namespace DummyClass {
	using namespace LoggingService;

	Logger* dummy_logger{nullptr};

	void SetLogger(Logger* logger) {
		dummy_logger = logger;
	}

	std::optional<LogRecord> GetRecord() {
		return LoggingService::GetRecord(*dummy_logger);
	}

	DummyClass::DummyClass() : m_Identifier{"None"}
	{
		DebugMessage("->Default constructor call");
	}

	DummyClass::DummyClass(const String& identifier)
		: m_Identifier(identifier)
	{
		DebugMessage("->Parametric constructor call");
	}

	DummyClass::DummyClass(const DummyClass& other)
	{
		m_Identifier = other.m_Identifier;

		DebugMessage("->Copy constructor call");
	}

	DummyClass::DummyClass(DummyClass&& other)
	{
		if (this != &other) {
			// Free old memory
			m_Identifier = "None";
			// Steal the pointer
			m_Identifier = other.m_Identifier;
			// Set source to null
			other.m_Identifier = "None"; 
		}

		DebugMessage("->Move constructor call");
	}

	DummyClass::~DummyClass()
	{
		DebugMessage("->Destructor call");
	}

	DummyClass& DummyClass::operator=(const DummyClass& other)
	{
		m_Identifier = other.m_Identifier;

		DebugMessage("->Copy assignment call");
		return *this;
	}

	DummyClass& DummyClass::operator=(DummyClass&& other)
	{
		if (this != &other) {
			// Free old memory
			m_Identifier = "None";
			// Steal the pointer
			m_Identifier = other.m_Identifier;
			// Set source to null
			other.m_Identifier = "None"; 
		}

		DebugMessage("->Move assignment call");

		return *this;
	}

    bool DummyClass::operator==(const DummyClass& other) const
    {
        return other.m_Identifier == this->m_Identifier;
    }

    bool DummyClass::operator==(const DummyClass&& other) const
    {
        return other.m_Identifier == this->m_Identifier;
    }

	void DummyClass::DebugMessage(const String& message)
	{
		if (nullptr != dummy_logger) {
			LoggingService::DebugMessage(
				*dummy_logger,
				m_Identifier + message
			);
		}
	}
};

// End of `DummyClass.cxx'
