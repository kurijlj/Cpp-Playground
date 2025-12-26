#pragma once

#include <iostream>
#include <string>

namespace LogService {
	using String = std::string;
	namespace SeverityLevel {
        class Severity {
        public:
            Severity(const int& value, const String identifier)
                : value_{value}, identifier_{identifier} { }

            int value() const
            {
                return value_;
            }
            String string() const
            {
                return identifier_; 
            }
            friend std::ostream& operator<<(
				std::ostream& os,
				const Severity& sv
			)
			{
                os << sv.identifier_;
                return os;
            }
            bool operator==(const Severity& other) const
            {
                bool result{false};

                if (other.value_ == value_)
                {
                    result = true;
                }

                return result;
            }

        private:
            const int value_;
            const String identifier_;
        };

        const Severity EMERGENCY{0, "EMERGENCY"};  // system is unusable
		const Severity ALERT{1, "ALERT"};          // action must be taken
												    // immediately
		const Severity CRITICAL{2, "CRITICAL"};    // critical conditions
		const Severity ERROR{3, "ERROR"};          // error conditions
		const Severity WARNING{4, "WARNING"};      // warning conditions
		const Severity NOTICE{5, "NOTICE"};        // normal but significant
												    // condition
		const Severity INFO{6, "INFO"};            // informational
		const Severity DEBUG{7, "DEBUG"};          // debug-level messages
    }; 

	class LogServiceBase {
	public:
		// virtual ~LogServiceBase() = 0;
		void Emergency(String message) {
			return OnLog(SeverityLevel::EMERGENCY, message);
		}
		void Alert(String message) {
			return OnLog(SeverityLevel::ALERT, message);
		}
		void Critical(String message) {
			return OnLog(SeverityLevel::CRITICAL, message);
		}
		void Error(String message) {
			return OnLog(SeverityLevel::ERROR, message);
		}
		void Warning(String message) {
			return OnLog(SeverityLevel::WARNING, message);
		}
		void Notice(String message) {
			return OnLog(SeverityLevel::NOTICE, message);
		}
		void Info(String message) {
			return OnLog(SeverityLevel::INFO, message);
		}
		void Debug(String message) {
			return OnLog(SeverityLevel::DEBUG, message);
		}

	protected:
		virtual void OnLog(
			const SeverityLevel::Severity& severity,
			const String message
		) = 0;
	};
};

// End of "log_service_base.hxx"
