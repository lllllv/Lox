//
// Created by 吕孝焱 on 2022/6/26.
//

#include "lox_instance.h"
#include "lox_class.h"

string lox_instance::to_string()
{
    return c->name + " instance";
}
