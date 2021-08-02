#ifndef _QUICKE_UNIT_TESTING_FRAMEWORK_H
#define _QUICKE_UNIT_TESTING_FRAMEWORK_H

#include <exception>
#include <string>
#include <iostream>

namespace test {

class TestFailedExcept : public std::exception {
public:
    TestFailedExcept(std::string msg): msg(msg) {}

    const char* what() const throw() {
        return msg.data();
    }

private:
    std::string msg;
};

static const std::string _defaultTestFailMessage = "Condition not met.";

void check(bool test_cond, std::string fail_msg = _defaultTestFailMessage) {
    if (!test_cond) {
        try {
            throw TestFailedExcept(fail_msg);
        } 
        catch(const TestFailedExcept& e) {
            std::cerr << "Test failed: " << e.what() << "\n";
            exit(1);
        }
    }
}

template <typename T>
void check(T a, T b, T delta = (T)1e-6, std::string fail_msg = _defaultTestFailMessage) {
    fail_msg.append("Expected " + std::to_string(b) + ", got " + std::to_string(a));
    check(abs(a - b) <= delta, fail_msg);
}

} // namespace test

#endif
