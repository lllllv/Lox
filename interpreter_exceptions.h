#ifndef LOX_INTERPRETER_EXCEPTIONS_H
#define LOX_INTERPRETER_EXCEPTIONS_H
#include "lox_object.h"

using namespace std;

class parse_error : public exception {

    const char * what () const noexcept override;
};

class interpreter_runtime_error : public runtime_error {
public:
    shared_ptr<Token> t;

    interpreter_runtime_error(shared_ptr<Token> t, const string& s);
};

class return_control_flow_exception : public runtime_error {
public:
    shared_ptr<lox_object> value;
    return_control_flow_exception(const string &s, shared_ptr<lox_object> value);
};

class return_result_exception : public runtime_error {
public:
    shared_ptr<lox_object> value;
    return_result_exception(const string &s, shared_ptr<lox_object> value);
};


#endif //LOX_INTERPRETER_EXCEPTIONS_H
