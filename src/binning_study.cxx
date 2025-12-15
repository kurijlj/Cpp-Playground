#include <console_log_service.hxx>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

using String = std::string;
using Function = std::vector<float>;
using Iterator = Function::iterator;

LogService::ConsoleLogService binning_log{"BINNING_STUDY"};

struct SineMovementGenerator {
	using Iterator = std::vector<float>::iterator;

	void operator()(const Iterator& begin, const Iterator& end) {
		for (Iterator current(begin); current != end; current++) {
			size_t index{current - begin};
			float position = 3.14 * static_cast<float> (index) / 180.0;
			*current = 360.0 * std::sin(position);
		}
	}
};

class BinToWidth {
public:
	BinToWidth() = default;
	explicit BinToWidth(const float& width) {
		if (1.0 > width) {
			binning_log.Error(
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
			size_t offset{current - beginIn};

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
	constexpr size_t data_points{360};
    Function f1(data_points, 0);
    Function f1binned(data_points, 0);
	SineMovementGenerator makeSineMovement{};
	BinToWidth binToOneDegree{10.0};

	binning_log.Info("Starting ...");

	makeSineMovement(f1.begin(), f1.end());
	binToOneDegree(
		f1.begin(),
		f1.end(),
		f1binned.begin()
	);

	printFunction(
		f1.begin(),
		f1.end(),
		f1binned.begin()
	);

	binning_log.Info("Finished ...");

	return EXIT_SUCCESS;
}

// End of `binning_study.cxx'
