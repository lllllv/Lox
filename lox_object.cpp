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




