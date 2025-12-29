#pragma once

#include <log_service_base.hxx>

#include <vector>

namespace LogService {
	using LogRecord = std::vector<String>;

	class TraceableLogService: public LogServiceBase {
	public:
		explicit TraceableLogService(const String& module_name)
			: module_name_{module_name} { }

		[[nodiscard]] LogRecord Record() const;
		void Reset();

	protected:
		void OnLog(
			const SeverityLevel::Severity& severity,
			const String message
		) override;

	protected:
		String module_name_;
		LogRecord log_record_;
	};
};

// End of 'traceable_log_service.hxx'
