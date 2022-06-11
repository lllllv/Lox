//
// Created by 吕孝焱 on 2022/6/10.
//

#ifndef LOX_INTERPRETER_EXCEPTIONS_H
#define LOX_INTERPRETER_EXCEPTIONS_H

class parse_error : public exception {

    const char * what () const noexcept override
    {
        return "parse error!";
    }
};

class interpreter_runtime_error : public runtime_error {
public:
    Token* t;

    interpreter_runtime_error(Token* t, const string& s) : runtime_error(s), t(t){};
    const char * what () const noexcept override
    {
        return "interpreter runtime error!";
    }
};

#endif //LOX_INTERPRETER_EXCEPTIONS_H
