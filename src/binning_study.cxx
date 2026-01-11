#include "ConsoleLoggingService.hxx"
#include "LoggerObject.hxx"
#include "LoggingServiceBase.hxx"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

// constexpr float pi = 3.14159;

using namespace LoggingService;

using String = std::string;
using Function = std::vector<float>;
using Iterator = Function::iterator;

Logger binning_logger = ConsoleLoggingService{"BINNING_STUDY"};

class LinearTrajectoryGenerator {
public:
	LinearTrajectoryGenerator(const float& a, const float& b)
		: a_{a}, b_{b} { }

	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			*current = a_ * index + b_;
		}
	}

private:
	const float a_;
	const float b_;
};

class SineTrajectoryGenerator {
public:
	SineTrajectoryGenerator(const float& equilibrium, const float& amplitude)
		: equilibrium_{equilibrium}, amplitude_{amplitude} { }

	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			float radians = 3.14 * static_cast<float> (index) / 180.0;
			*current = 2 * amplitude_ * std::sin(radians) + equilibrium_;
		}
	}

private:
	const float equilibrium_;
	const float amplitude_;
};

class GaussianTrajectoryGenerator {
public:
	GaussianTrajectoryGenerator(
		const float& amplitude,
		const float& mu,
		const float& sigma
	) : amplitude_{amplitude}, mu_{mu}, sigma_{sigma} { }
	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			*current = amplitude_ * std::exp(
				-(std::pow(index - mu_, 2))
					/ (2 * std::pow(sigma_, 2))
			);
		}
	}

private:
	const float amplitude_;
	const float mu_;
	const float sigma_;
};

class SawtoothTrajectoryGenerator {
public:
	SawtoothTrajectoryGenerator(
		const float& amplitude,
		const float& equilibrium,
		const float& period
	) : amplitude_{amplitude}, equilibrium_{equilibrium}, period_{period} { }
	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			*current = amplitude_ * (
				index / period_ - std::floor(index / period_)
			) - 0.5 * amplitude_ + equilibrium_;
		}
	}

private:
	const float amplitude_;
	const float equilibrium_;
	const float period_;
};

class TriangleTrajectoryGenerator {
public:
	TriangleTrajectoryGenerator(
		const float& amplitude,
		const float& equilibrium,
		const float& period
	) : amplitude_{amplitude}, equilibrium_{equilibrium}, period_{period} { }
	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			*current = (amplitude_ / period_)
				* (period_ - std::abs(
					std::fmod(index, 2 * period_) - period_
				)) - 0.5 * amplitude_ + equilibrium_;
		}
	}

private:
	const float amplitude_;
	const float equilibrium_;
	const float period_;
};

class SpikeyTrajectoryGenerator {
public:
	SpikeyTrajectoryGenerator(
		const float& amplitude,
		const float& equilibrium,
		const float& period
	) : amplitude_{amplitude}, equilibrium_{equilibrium}, period_{period} { }
	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{static_cast<size_t>(current - begin)};
			float phase = std::fmod(index / period_, 1.0);
			if (0 > phase) phase += 1.0;

			if  (0.5 > phase) {
				float x = phase * 2.0;
				*current = 2.0 * x * x;
			} else {
				float x = (phase - 0.5) * 2.0;
				*current = 2.0 * (1.0 - x) * (1.0 - x);
			}

			*current = 0.5 * amplitude_ * (*current - 1.0) + equilibrium_;
		}
	}

private:
	const float amplitude_;
	const float equilibrium_;
	const float period_;
};

class FidTrajectoryGenerator {
public:
	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
		}
	}
};

class BinBySignalStep {
public:
	BinBySignalStep() = default;
	explicit BinBySignalStep(const float& width) {
		if (1.0 > width) {
			ErrorMessage(
                binning_logger,
				String{"Bin width too small. "}
				+ String{"Expected >= 1.0, got: "}
				+ std::to_string(width)
			);

			throw std::runtime_error{"Bin width too small."};
		}

		bin_width_ = width;
	}
	
	void operator()(
		const Iterator& beginIn,
		const Iterator& endIn,
		const Iterator& beginOut
	) {
		float bin = std::round(*beginIn);
		float left_bound = bin - bin_width_ / 2;
		float right_bound = bin + bin_width_ / 2;

		for (Iterator current{beginIn}; current != endIn; current++) {
			size_t offset{static_cast<size_t>(current - beginIn)};

			if (left_bound > *current) {
				// Calculate how many widths aparat are we
				while (left_bound > *current) {
					left_bound -= bin_width_;
				}
				bin = std::round(left_bound + bin_width_ / 2);
				right_bound = left_bound + bin_width_;
			} else if (right_bound <= *current) {
				// Calculate how many widths aparat are we
				while ( right_bound <= *current) {
					right_bound += bin_width_;
				}
				bin = std::round(right_bound - bin_width_ / 2);
				left_bound = right_bound - bin_width_;
			}

			*(beginOut + offset) = bin;
		}
	}

private:
	float bin_width_{1.0};
};

void printFunction(
	const Iterator& begin1,
	const Iterator& end1,
	const Iterator& begin2
) {
	size_t abscissa{0};
	Iterator current2{begin2};
	for (Iterator current1{begin1}; current1 != end1; current1++) {
		std::cout << std::to_string(static_cast<float> (abscissa))
			<< ", " << std::to_string(*current1)
			<< ", " << std::to_string(*current2)
			<< "\n";
		abscissa++;
		current2++;
	}
}

int main(int argc, char* argv[]) {

    // Silent unused parameter warnings
    (void) argc;
    (void) argv;

	constexpr size_t data_points{360};
    Function f1(data_points, 0);
    Function f1binned(data_points, 0);
	LinearTrajectoryGenerator makeLineTrajectory{-1.0, 360.0};
	SineTrajectoryGenerator makeSineTrajectory{180.0, 180.0};
	GaussianTrajectoryGenerator makeGaussianTrajectory{360.0, 180.0, 45.0};
	SawtoothTrajectoryGenerator makeSawtoothTrajectory{360.0, 180.0, 180.0};
	TriangleTrajectoryGenerator makeTriangleTrajectory{360.0, 180.0, 180.0};
	SpikeyTrajectoryGenerator makeSpikeyTrajectory{360.0, 180.0, 180.0};
	BinBySignalStep binByTen{1.0};

	InfoMessage(binning_logger, "Starting ...");

	makeSpikeyTrajectory(f1.begin(), f1.end());
	binByTen(
		f1.begin(),
		f1.end(),
		f1binned.begin()
	);

	printFunction(
		f1.begin(),
		f1.end(),
		f1binned.begin()
	);

	InfoMessage(binning_logger, "Finished ...");

	return EXIT_SUCCESS;
}

// End of `binning_study.cxx'
