//
// Created by lvxia on 2022/6/7.
//

#include "lox_object.h"

lox_object::lox_object() {
    type = NIL;
}

lox_object::lox_object(string &&s) {
    str = s;
    type = STRING;
}

lox_object::lox_object(double num) : num(num) {
    type = NUMBER;
}

lox_object::lox_object(bool boolean) {
    boolean = boolean;
    type = boolean ? TRUE : FALSE;
}

lox_object::lox_object(string &s) {
    str = s;
    type = STRING;
}

void lox_object::print()
{
    switch(this->type)
    {
        case NIL:
            cout << "NIL";
            break;
        case TRUE:
            cout << "TRUE";
            break;
        case FALSE:
            cout << "FALSE";
            break;
        case NUMBER:
            cout << this->num;
            break;
        case STRING:
            cout << this->str;
    }
}




