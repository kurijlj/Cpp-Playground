#include "log_service_base.hxx"

namespace LogService {
	class ConsoleLogService: public LogServiceBase {
	public:
		explicit ConsoleLogService(const String& module_name)
			: module_name_{module_name} { }

	protected:
		void OnLog(const LogSeverity severity, const String message) override;

	protected:
		String module_name_;
	};
};

// End of 'console_log_service.hxx'
