#include "log_service_base.hxx"

namespace LogService {
	class ConsoleLogService: public LogServiceBase {
	protected:
		void OnLog(LogSeverity severity, String message) override;
	};
};

// End of 'console_log_service.hxx'
