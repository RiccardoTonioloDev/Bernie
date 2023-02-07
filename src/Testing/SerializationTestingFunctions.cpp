#include "SerializationTestingFunctions.h"

void serializationTest(SerializableObject &input, const std::string &expected, const std::string &testName) {
    std::string serializedObj = input.serialize();
    /*
    std::cout << input.serialize() << std::endl;
    std::cout << expected << std::endl;
     */
    if (serializedObj == expected) {
        std::cout << "TEST (" + testName + "): \033[92mPASSED\033[0m";
    } else std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void deSanitizationTest(const std::string &input, const std::pair<bool, std::vector<std::string>> &expected,
                        const std::string &testName) {
    std::pair<bool, std::vector<std::string>> couple = SerializableObject::deSanitize(input);
    if (expected.first != couple.first) {
        std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
    } else {
        std::vector<std::string>::const_iterator citExpected = expected.second.begin();
        std::vector<std::string>::const_iterator citCouple = couple.second.begin();
        bool areEqual = true;
        while (areEqual && citExpected != expected.second.end() && citCouple != couple.second.end()) {
            if (*citCouple != *citExpected) {
                std::cout << std::endl;
                areEqual = false;
            }
            ++citCouple;
            ++citExpected;
        }
        if (areEqual) {
            std::cout << "TEST (" + testName + "): \033[92mPASSED\033[0m";
        } else {
            std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
        }
    }
    std::cout << std::endl;
}
