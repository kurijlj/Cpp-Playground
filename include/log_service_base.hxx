#include <string>

namespace LogService {
	using String = std::string;

	enum class LogSeverity {
		EMERGENCY = 0,  // system is unusable
		ALERT     = 1,  // action must be taken immediately
		CRITICAL  = 2,  // critical conditions
		ERROR     = 3,  // error conditions
		WARNING   = 4,  // warning conditions
		NOTICE    = 5,  // normal but significant condition
		INFO      = 6,  // informational
		DEBUG     = 7   // debug-level messages
	};

	[[nodiscard]] String toString(const LogSeverity severity);

	class LogServiceBase {
	public:
		LogServiceBase() = delete;
		explicit LogServiceBase(const String& module_name)
			: module_name_(module_name) { }
		explicit LogServiceBase(const char* module_name)
			: module_name_{module_name} { }

		void Emergency(String message) {
			return OnLog(LogSeverity::EMERGENCY, message);
		}
		void Alert(String message) {
			return OnLog(LogSeverity::ALERT, message);
		}
		void Critical(String message) {
			return OnLog(LogSeverity::CRITICAL, message);
		}
		void Error(String message) {
			return OnLog(LogSeverity::ERROR, message);
		}
		void Warning(String message) {
			return OnLog(LogSeverity::WARNING, message);
		}
		void Notice(String message) {
			return OnLog(LogSeverity::NOTICE, message);
		}
		void Info(String message) {
			return OnLog(LogSeverity::INFO, message);
		}
		void Debug(String message) {
			return OnLog(LogSeverity::DEBUG, message);
		}

	protected:
		virtual void OnLog(
			const LogSeverity severity,
			const String message
		) = 0;

	protected:
		String module_name_;
	};
};

// End of "log_service_base.hxx"
