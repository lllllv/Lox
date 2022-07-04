//
// Created by 吕孝焱 on 2022/6/19.
//

#include "native_functions.h"

lox_object *clock::call(interpreter &i, vector<lox_object *> &arguments)
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    //return new lox_object((double)millisec_since_epoch/1000.0);
    return new lox_object((double)millisec_since_epoch);
}

int clock::arity()
{
    return 0;
}

string clock::to_string()
{
    return "<native fn>";
}

