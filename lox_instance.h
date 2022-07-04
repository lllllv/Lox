//
// Created by 吕孝焱 on 2022/6/26.
//

#ifndef LOX_LOX_INSTANCE_H
#define LOX_LOX_INSTANCE_H
#include <unordered_map>
#include "lox_object.h"


class lox_class;

class lox_instance : public lox_object {
private:
    unordered_map<string, lox_object*> fields;
public:
    const   lox_class* c;
    explicit lox_instance(const lox_class* c) : c(c){};
    string to_string();
    lox_object* get(Token* name);
    void set(Token* name, lox_object* value);
};


#endif //LOX_LOX_INSTANCE_H
