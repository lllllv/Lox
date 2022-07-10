#include "interpreter_exceptions.h"

#include <utility>

const char *parse_error::what() const noexcept
{
    return "parse error!";
}

interpreter_runtime_error::interpreter_runtime_error(shared_ptr<Token> t, const string &s) : runtime_error(s), t(move(t))
{

}


return_control_flow_exception::return_control_flow_exception(const string &s, shared_ptr<lox_object> value) : runtime_error(s), value(move(value))
{

}

return_result_exception::return_result_exception(const string &s, shared_ptr<lox_object> value) : runtime_error(s), value(move(value))
{

}
