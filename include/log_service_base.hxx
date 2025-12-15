#include <string>
#include <variant>

namespace LogService {
	using String = std::string;
    namespace SeverityLevel {
        struct Emergency {};  // system is unusable
        struct Alert {};      // action must be taken immediately
        struct Critical {};   // critical conditions
        struct Error {};      // error conditions
        struct Warning {};    // warning conditions
        struct Notice {};     // normal but significant condition
        struct Info {};       // informational
        struct Debug {};      // debug-level messages
    };

    struct SeverityValue {
        [[nodiscard]] int
		operator()(const SeverityLevel::Emergency&) const {
			return 0;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Alert&) const {
			return 1;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Critical&) const {
			return 2;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Error&) const {
			return 3;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Warning&) const {
			return 4;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Notice&) const {
			return 5;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Info&) const {
			return 6;
		}
        [[nodiscard]] int
		operator()(const SeverityLevel::Debug&) const {
			return 7;
		}
    };

    struct SeverityToString {
        [[nodiscard]] String
		operator()(const SeverityLevel::Emergency&) const {
			return String{"EMERGENCY"}; 
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Alert&) const {
			return String{"ALERT"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Critical&) const {
			return String{"CRITICAL"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Error&) const {
			return String{"ERROR"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Warning&) const {
			return String{"WARNING"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Notice&) const {
			return String{"NOTICE"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Info&) const {
			return String{"INFO"};
		}
        [[nodiscard]] String
		operator()(const SeverityLevel::Debug&) const {
			return String{"DEBUG"};
		}
    };

    using LogSeverity = std::variant<
        SeverityLevel::Emergency,
        SeverityLevel::Alert,
        SeverityLevel::Critical,
        SeverityLevel::Error,
        SeverityLevel::Warning,
        SeverityLevel::Notice,
        SeverityLevel::Info,
        SeverityLevel::Debug
    >;  

	class LogServiceBase {
	public:
		LogServiceBase() = delete;
		explicit LogServiceBase(const String& module_name)
			: module_name_(module_name) { }

		void Emergency(String message) {
			return OnLog(SeverityLevel::Emergency(), message);
		}
		void Alert(String message) {
			return OnLog(SeverityLevel::Alert(), message);
		}
		void Critical(String message) {
			return OnLog(SeverityLevel::Critical(), message);
		}
		void Error(String message) {
			return OnLog(SeverityLevel::Error(), message);
		}
		void Warning(String message) {
			return OnLog(SeverityLevel::Warning(), message);
		}
		void Notice(String message) {
			return OnLog(SeverityLevel::Notice(), message);
		}
		void Info(String message) {
			return OnLog(SeverityLevel::Info(), message);
		}
		void Debug(String message) {
			return OnLog(SeverityLevel::Debug(), message);
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
