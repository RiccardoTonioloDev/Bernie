
#ifndef SERIALIZATIONTESTINGFUNCTIONS_CPP_H
#define SERIALIZATIONTESTINGFUNCTIONS_CPP_H

#include "../Models/SerializableObject.h"

void serializationTest(SerializableObject &input, const std::string &expected, const std::string &testName);

void deSanitizationTest(const std::string &input, const std::pair<bool, std::vector<std::string>> &expected,
                        const std::string &testName);

#endif //SERIALIZATIONTESTINGFUNCTIONS_CPP_H
