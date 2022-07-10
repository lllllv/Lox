#ifndef LOX_NATIVE_FUNCTIONS_H
#define LOX_NATIVE_FUNCTIONS_H
#include <chrono>
#include "lox_callable.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
class native_clock : public lox_callable
{
public:
    int arity() override;
    shared_ptr<lox_object> call(interpreter& i, vector<shared_ptr<lox_object>>& arguments) override;
    string to_string() override;
};


#endif //LOX_NATIVE_FUNCTIONS_H
