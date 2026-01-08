// Related Header
#include "LoggingService/LoggerObject.hxx"

// Component Headers
#include "LoggingService/ConsoleLoggingService.hxx"
#include "LoggingService/LoggingServiceBase.hxx"
#include "LoggingService/TraceableLoggingService.hxx"

// Namespace Usage
using namespace LoggingService;

void
Alert::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Alert::operator()(ConsoleLoggingService& obj) const
{
	return obj.Alert(message_);
}

void
Alert::operator()(TraceableLoggingService& obj) const
{
	return obj.Alert(message_);
}

void
Critical::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Critical::operator()(ConsoleLoggingService& obj) const
{
	return obj.Critical(message_);
}

void
Critical::operator()(TraceableLoggingService& obj) const
{
	return obj.Critical(message_);
}

void
Debug::operator()(const NoLoggingService& obj) const
{
	(void) obj;  // Suppress unused parameter warning
	return;
}

void
Debug::operator()(ConsoleLoggingService& obj) const
{
	return obj.Debug(message_);
}

void
Debug::operator()(TraceableLoggingService& obj) const
{
	return obj.Debug(message_);
}

void
Emergency::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Emergency::operator()(ConsoleLoggingService& obj) const
{
	return obj.Emergency(message_);
}

void
Emergency::operator()(TraceableLoggingService& obj) const
{
	return obj.Emergency(message_);
}

void
Error::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Error::operator()(ConsoleLoggingService& obj) const
{
	return obj.Error(message_);
}

void
Error::operator()(TraceableLoggingService& obj) const
{
	return obj.Error(message_);
}

void
Info::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Info::operator()(ConsoleLoggingService& obj) const
{
	return obj.Info(message_);
}

void
Info::operator()(TraceableLoggingService& obj) const
{
	return obj.Info(message_);
}

void
Notice::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Notice::operator()(ConsoleLoggingService& obj) const
{
	return obj.Notice(message_);
}

void
Notice::operator()(TraceableLoggingService& obj) const
{
	return obj.Notice(message_);
}

std::optional<LogRecord>
Record::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return std::nullopt;
}

std::optional<LogRecord>
Record::operator()(const ConsoleLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return std::nullopt;
}

std::optional<LogRecord>
Record::operator()(const TraceableLoggingService& obj) const
{
	return obj.Record();
}

void
Reset::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Reset::operator()(const ConsoleLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Reset::operator()(TraceableLoggingService& obj) const
{
	obj.Reset();
    return;
}

void
Warning::operator()(const NoLoggingService& obj) const
{
    (void) obj;  // Suppress unused parameter warning
	return;
}

void
Warning::operator()(ConsoleLoggingService& obj) const
{
	return obj.Warning(message_);
}

void
Warning::operator()(TraceableLoggingService& obj) const
{
	return obj.Warning(message_);
}


void
LoggingService::AlertMessage(Logger& obj, const String& message)
{
	return std::visit(Alert{message}, obj);
}

void
LoggingService::CriticalMessage(Logger& obj, const String& message)
{
	return std::visit(Critical{message}, obj);
}

void
LoggingService::DebugMessage(Logger& obj, const String& message)
{
	return std::visit(Debug{message}, obj);
}

void
LoggingService::EmergencyMessage(Logger& obj, const String& message)
{
	return std::visit(Emergency{message}, obj);
}

void
LoggingService::ErrorMessage(Logger& obj, const String& message)
{
	return std::visit(Error{message}, obj);
}

std::optional<LogRecord>
LoggingService::GetRecord(const Logger& obj)
{
	return std::visit(Record{}, obj);
}

void
LoggingService::InfoMessage(Logger& obj, const String& message)
{
	return std::visit(Info{message}, obj);
}

void
LoggingService::NoticeMessage(Logger& obj, const String& message)
{
	return std::visit(Notice{message}, obj);
}

void
LoggingService::ResetRecord(Logger& obj)
{
	return std::visit(Reset{}, obj);
}

void
LoggingService::WarningMessage(Logger& obj, const String& message)
{
	return std::visit(Warning{message}, obj);
}

// End of file `LoggerObject.cxx'
