#include <log_service_base.hxx>

#include <vector>

namespace LogService {
	using LogRecord = std::vector<String>;

	class TracableLogService: public LogServiceBase {
	public:
		LogRecord record() const;
		void reset();

	protected:
		void OnLog(const LogSeverity severity, const String message) override;

	protected:
		LogRecord log_record_;
	};
};

// End of 'tracable_log_service.hxx'
