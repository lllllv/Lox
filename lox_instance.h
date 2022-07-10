#ifndef LOX_LOX_INSTANCE_H
#define LOX_LOX_INSTANCE_H
#include <unordered_map>
#include "lox_object.h"


class lox_class;

class lox_instance : public lox_object/*, public enable_shared_from_this<lox_instance>*/{
private:
    unordered_map<string, shared_ptr<lox_object>> fields;
public:
    const   shared_ptr<lox_class> c;
    explicit lox_instance(const shared_ptr<lox_class>& c);
    string to_string();
    shared_ptr<lox_object> get(const shared_ptr<Token>& name);
    void set(const shared_ptr<Token>& name, shared_ptr<lox_object> value);
};


#endif //LOX_LOX_INSTANCE_H
