//
// Created by 吕孝焱 on 2022/7/7.
//
#include "interpreter_exceptions.h"

interpreter_runtime_error::interpreter_runtime_error(Token *t, const string &s) : runtime_error(s), t(t)
{

}

return_control_flow_exception::return_control_flow_exception(const string &s, lox_object *value) : runtime_error(s), value(value)
{

}

return_result_exception::return_result_exception(const string &s, lox_object *value) : runtime_error(s), value(value)
{

}
