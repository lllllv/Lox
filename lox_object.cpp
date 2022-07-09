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

lox_object::lox_object(double num) {
    val = num;
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

/*
void lox_object::print() const
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
            cout << this->l.val;
            break;
        case STRING:
            cout << this->l.str;
        default:

    }
}*/




