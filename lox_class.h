#ifndef LOX_LOX_CLASS_H
#define LOX_LOX_CLASS_H
#include <unordered_map>
#include <string>
#include <utility>
#include "lox_callable.h"
#include "lox_instance.h"
class lox_instance;

using namespace std;

class lox_class : public lox_callable/*, enable_shared_from_this<lox_class>*/ {
public:
    string name;
    shared_ptr<lox_class> super_class;
    shared_ptr<unordered_map<string, shared_ptr<lox_function>>> methods;
    lox_class(string  name,shared_ptr<lox_class> super_class, shared_ptr<unordered_map<string, shared_ptr<lox_function>>> methods);
    string to_string() override;
    shared_ptr<lox_object> call(interpreter& i, vector<shared_ptr<lox_object>>& arguments) override;
    shared_ptr<lox_function> find_method(const string& str) const;
    int arity() override;
};


#endif //LOX_LOX_CLASS_H
