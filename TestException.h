#ifndef TESTEXCEPTION_H
#define TESTEXCEPTION_H

#include <exception>

class TestException : public std::exception
{
private:
    char *message;
public:
    explicit TestException(const char *msg):std::exception() {
        message = (char*) msg;
    }
    const char *what() const noexcept{
        return message;
    }
};

#endif // TESTEXCEPTION_H
