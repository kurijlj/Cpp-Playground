#include <log_service.hxx>
#include <log_service_base.hxx>

void
LogService::Emergency::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Emergency::operator()(ConsoleLogService& obj) const
{
	return obj.Emergency(message_);
}

void
LogService::Emergency::operator()(TraceableLogService& obj) const
{
	return obj.Emergency(message_);
}

void
LogService::Alert::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Alert::operator()(ConsoleLogService& obj) const
{
	return obj.Alert(message_);
}

void
LogService::Alert::operator()(TraceableLogService& obj) const
{
	return obj.Alert(message_);
}

void
LogService::Critical::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Critical::operator()(ConsoleLogService& obj) const
{
	return obj.Critical(message_);
}

void
LogService::Critical::operator()(TraceableLogService& obj) const
{
	return obj.Critical(message_);
}

void
LogService::Error::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Error::operator()(ConsoleLogService& obj) const
{
	return obj.Error(message_);
}

void
LogService::Error::operator()(TraceableLogService& obj) const
{
	return obj.Error(message_);
}

void
LogService::Warning::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Warning::operator()(ConsoleLogService& obj) const
{
	return obj.Warning(message_);
}

void
LogService::Warning::operator()(TraceableLogService& obj) const
{
	return obj.Warning(message_);
}

void
LogService::Notice::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Notice::operator()(ConsoleLogService& obj) const
{
	return obj.Notice(message_);
}

void
LogService::Notice::operator()(TraceableLogService& obj) const
{
	return obj.Notice(message_);
}

void
LogService::Info::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Info::operator()(ConsoleLogService& obj) const
{
	return obj.Info(message_);
}

void
LogService::Info::operator()(TraceableLogService& obj) const
{
	return obj.Info(message_);
}

void
LogService::Debug::operator()(const NoLogService& obj) const
{
	return;
}

void
LogService::Debug::operator()(ConsoleLogService& obj) const
{
	return obj.Debug(message_);
}

void
LogService::Debug::operator()(TraceableLogService& obj) const
{
	return obj.Debug(message_);
}

std::optional<LogService::LogRecord>
LogService::Record::operator()(const NoLogService& obj) const
{
	return std::nullopt;
}

std::optional<LogService::LogRecord>
LogService::Record::operator()(const ConsoleLogService& obj) const
{
	return std::nullopt;
}

std::optional<LogService::LogRecord>
LogService::Record::operator()(const TraceableLogService& obj) const
{
	return obj.record();
}


void
LogService::EmergencyMessage(Logger& obj, const String& message)
{
	return std::visit(Emergency{message}, obj);
}

void
LogService::AlertMessage(Logger& obj, const String& message)
{
	return std::visit(Alert{message}, obj);
}

void
LogService::CriticalMessage(Logger& obj, const String& message)
{
	return std::visit(Critical{message}, obj);
}

void
LogService::ErrorMessage(Logger& obj, const String& message)
{
	return std::visit(Error{message}, obj);
}

void
LogService::WarningMessage(Logger& obj, const String& message)
{
	return std::visit(Warning{message}, obj);
}

void
LogService::NoticeMessage(Logger& obj, const String& message)
{
	return std::visit(Notice{message}, obj);
}

void
LogService::InfoMessage(Logger& obj, const String& message)
{
	return std::visit(Info{message}, obj);
}

void
LogService::DebugMessage(Logger& obj, const String& message)
{
	return std::visit(Debug{message}, obj);
}

std::optional<LogService::LogRecord>
LogService::GetRecord(const Logger& obj)
{
	return std::visit(Record{}, obj);
}

// End of file `log_service.cxx'
