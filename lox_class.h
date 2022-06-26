//
// Created by 吕孝焱 on 2022/6/26.
//

#ifndef LOX_LOX_CLASS_H
#define LOX_LOX_CLASS_H
#include <unordered_map>
#include <string>
#include <utility>
#include "lox_callable.h"
#include "lox_instance.h"
class lox_instance;

using namespace std;

class lox_class : public lox_callable {
public:
    string name;
    explicit lox_class(string  name);
    string to_string() override;
    lox_object* call(interpreter& i, vector<lox_object*>& arguments) override;
    int arity() override;
};


#endif //LOX_LOX_CLASS_H
