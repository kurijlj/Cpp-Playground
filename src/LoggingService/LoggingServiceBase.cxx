// Related Header
#include "LoggingService/LoggingServiceBase.hxx"

// Namespace Usage
using namespace LoggingService;

int
SeverityLevel::Severity::value() const
{
    return value_;
}

String
SeverityLevel::Severity::string() const
{
    return identifier_;
}

// Full namespace specification to avoid ADL issues
namespace LoggingService::SeverityLevel {
	std::ostream&
	operator<<(
		std::ostream& os,
		const LoggingService::SeverityLevel::Severity& obj
	)
	{
		os << obj.identifier_;
		return os;
	}
}

bool
SeverityLevel::Severity::operator==(
    const Severity& other
) const
{
    bool result{false};

    if (other.value_ == value_)
    {
        result = true;
    }

    return result;
}

const SeverityLevel::Severity SeverityLevel::EMERGENCY_LEVEL{0, "EMERGENCY"};
const SeverityLevel::Severity SeverityLevel::ALERT_LEVEL{1, "ALERT"};
const SeverityLevel::Severity SeverityLevel::CRITICAL_LEVEL{2, "CRITICAL"};
const SeverityLevel::Severity SeverityLevel::ERROR_LEVEL{3, "ERROR"};
const SeverityLevel::Severity SeverityLevel::WARNING_LEVEL{4, "WARNING"};
const SeverityLevel::Severity SeverityLevel::NOTICE_LEVEL{5, "NOTICE"};
const SeverityLevel::Severity SeverityLevel::INFO_LEVEL{6, "INFO"};
const SeverityLevel::Severity SeverityLevel::DEBUG_LEVEL{7, "DEBUG"};

void
LoggingServiceBase::Alert(String message)
{
    return OnLog(SeverityLevel::ALERT_LEVEL, message);
}

void
LoggingServiceBase::Critical(String message)
{
    return OnLog(SeverityLevel::CRITICAL_LEVEL, message);
}

void
LoggingServiceBase::Debug(String message)
{
    return OnLog(SeverityLevel::DEBUG_LEVEL, message);
}

void
LoggingServiceBase::Emergency(String message)
{
    return OnLog(SeverityLevel::EMERGENCY_LEVEL, message);
}

void
LoggingServiceBase::Error(String message)
{
    return OnLog(SeverityLevel::ERROR_LEVEL, message);
}

void
LoggingServiceBase::Info(String message)
{
    return OnLog(SeverityLevel::INFO_LEVEL, message);
}

void
LoggingServiceBase::Notice(String message)
{
    return OnLog(SeverityLevel::NOTICE_LEVEL, message);
}

void
LoggingServiceBase::Warning(String message)
{
    return OnLog(SeverityLevel::WARNING_LEVEL, message);
}

// End of "LoggingServiceBase.cxx"
