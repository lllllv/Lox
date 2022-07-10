#include "native_functions.h"

shared_ptr<lox_object> native_clock::call(interpreter &i, vector<shared_ptr<lox_object>> &arguments)
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    //return make_shared<lox_object>((double)millisec_since_epoch/1000.0);
    return make_shared<lox_object>((double)millisec_since_epoch);
}

int native_clock::arity()
{
    return 0;
}

string native_clock::to_string()
{
    return "<native fn>";
}

