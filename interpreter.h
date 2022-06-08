//
// Created by lvxia on 2022/6/7.
//

#ifndef LOX_INTERPRETER_H
#define LOX_INTERPRETER_H
#include <stack>
#include <exception>
#include "AST.h"
#include "visitor.h"
#include "lox_object.h"

using namespace std;

class interpreter_runtime_error : public runtime_error {
public:
    const char * what () const noexcept override
    {
        return "interpreter runtime error!";
    }
};

class interpreter : public Visitor{
private:
    Expr* expr;
    stack<lox_object> im_results;
    static bool is_truthy(const lox_object&);
    static bool is_equal(const lox_object&, const lox_object&);

    void Visit_Literal_Expr(Literal_Expr* l) override;
    void Visit_Grouping_Expr(Grouping_Expr* g) override;
    void Visit_Unary_Expr(Unary_Expr* u) override;
    void Visit_Binary_Expr(Binary_Expr* b) override;

    void _evaluate(Expr* exp);
    static void print(const lox_object&);
public:
    ~interpreter() override = default;
    explicit interpreter(Expr* exp);
    void eval();
};


#endif //LOX_INTERPRETER_H
