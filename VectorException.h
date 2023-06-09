#ifndef VECTOREXCEPTION_H
#define VECTOREXCEPTION_H

#include <exception>

class VectorException : public std::exception
{
private:
    char *message;
public:
    explicit VectorException(const char *msg):std::exception() {
        message = (char*) msg;
    }
    const char *what() const noexcept{
        return message;
    }
};

#endif // VECTOREXCEPTION_H
