#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string msg;

public:
    Exception() noexcept : msg("Error indefinido") {}
    Exception(const Exception& ex) noexcept : msg(ex.msg) {}
    Exception(const std::string& m) : msg(m) {}
    Exception& operator=(const Exception& ex) noexcept {
        msg = ex.msg;
        return *this;
    }

    virtual ~Exception() {}
    virtual const char* what() const noexcept { return msg.c_str(); }
};

#endif // EXCEPTION_HPP
