#include "log_service_base.hxx"

namespace LogService {
	class ConsoleLogService: public LogServiceBase {
	protected:
		void OnLog(const LogSeverity severity, const String message) override;
	};
};

// End of 'console_log_service.hxx'
