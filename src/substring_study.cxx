#include "LoggingService/ConsoleLoggingService.hxx"
#include "LoggingService/LoggerObject.hxx"
#include "LoggingService/LoggingServiceBase.hxx"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <string>

static constexpr int VOID_POSITION{-1};

int contains(const std::string& haystack, const std::string& needle) {
    if (needle.length() > haystack.length()) {
        return VOID_POSITION;
    }

    for (size_t index{0}; haystack.length() - needle.length() >= index; ++index) {
        if (haystack.substr(index, needle.length()) == needle) {
            return static_cast<int> (index);
        }
    }

    return VOID_POSITION;
}

int main(int argc, char* argv[]) {
    // Prevent compiler from complaining on unused variables
    (void) argc;
    (void) argv;

    using namespace LoggingService;

	Logger logger = ConsoleLoggingService{"SUBSTRING"};

    InfoMessage(logger, "Starting app ...");

    std::string msg{"Hello World!"},
        sub1{"Hello"},
        sub2{"World"},
        sub3{"llo"},
        sub4{"ld!"},
        sub5{"Sunshine"},
        sub6{"rold"},
        sub7{"Hello World tonight!"};

    std::cout << sub1 << " is substring of " << msg << ": " << (-1 != contains(msg, sub1) ? "TRUE\n" : "FALSE\n");
    std::cout << sub2 << " is substring of " << msg << ": " << (-1 != contains(msg, sub2) ? "TRUE\n" : "FALSE\n");
    std::cout << sub3 << " is substring of " << msg << ": " << (-1 != contains(msg, sub3) ? "TRUE\n" : "FALSE\n");
    std::cout << sub4 << " is substring of " << msg << ": " << (-1 != contains(msg, sub4) ? "TRUE\n" : "FALSE\n");
    std::cout << sub5 << " is substring of " << msg << ": " << (-1 != contains(msg, sub5) ? "TRUE\n" : "FALSE\n");
    std::cout << sub6 << " is substring of " << msg << ": " << (-1 != contains(msg, sub6) ? "TRUE\n" : "FALSE\n");
    std::cout << sub7 << " is substring of " << msg << ": " << (-1 != contains(msg, sub7) ? "TRUE\n" : "FALSE\n");

    InfoMessage(logger, "Closing app ...");

    return EXIT_SUCCESS;
}