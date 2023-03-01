#ifndef LOX_LOX_OBJECT_H
#define LOX_LOX_OBJECT_H

#include <string>
#include <iostream>
#include <memory>
#include "token.h"
using namespace std;

class lox_object : public enable_shared_from_this<lox_object>{
public:
    double num;
    string str;
    bool boolean;
    TokenType type;

    lox_object();
    lox_object(const lox_object&) = default;
    virtual ~lox_object() = default;

    explicit lox_object(string& s);
    explicit lox_object(string&& s);
    explicit lox_object(double num);
    explicit lox_object(bool boolean);
};


#endif //LOX_LOX_OBJECT_H
