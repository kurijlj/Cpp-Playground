#pragma once

#include <iostream>
#include <string>

namespace LoggingService {
	using String = std::string;
	namespace SeverityLevel {
        class Severity {
        public:
            Severity(const int& value, const String identifier)
                : value_{value}, identifier_{identifier} { }

            int value() const;
            String string() const;
            friend std::ostream& operator<<(
                std::ostream& os,
                const Severity& sv
            );
            bool operator==(const Severity& other) const;

        private:
            const int value_;
            const String identifier_;
        };

        extern const Severity EMERGENCY_LEVEL;  // system is unusable
        extern const Severity ALERT_LEVEL;      // action must be taken
												// immediately
		extern const Severity CRITICAL_LEVEL;   // critical conditions
		extern const Severity ERROR_LEVEL;      // error conditions
		extern const Severity WARNING_LEVEL;    // warning conditions
		extern const Severity NOTICE_LEVEL;     // normal but significant
											    // condition
		extern const Severity INFO_LEVEL;       // informational
		extern const Severity DEBUG_LEVEL;      // debug-level messages
    }; 

	struct NoLoggingService {};

	class LoggingServiceBase {
	public:
        virtual ~LoggingServiceBase() = default;
		void Alert(String message);
		void Critical(String message);
		void Debug(String message);
		void Emergency(String message);
		void Error(String message);
		void Info(String message);
		void Notice(String message);
		void Warning(String message);

	protected:
        // Pure virtual function to be implemented by derived classes
		virtual void OnLog(
			const SeverityLevel::Severity& severity,
			const String message
		) = 0;
	};
};

// End of "loggingServiceBase.hxx"
