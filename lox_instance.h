//
// Created by 吕孝焱 on 2022/6/26.
//

#ifndef LOX_LOX_INSTANCE_H
#define LOX_LOX_INSTANCE_H


#include "lox_object.h"


class lox_class;

class lox_instance : public lox_object {
public:
    lox_class* c;
    explicit lox_instance(lox_class* c) : c(c){};
    string to_string();
};


#endif //LOX_LOX_INSTANCE_H
