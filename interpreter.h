//
// Created by lvxia on 2022/6/7.
//

#ifndef LOX_INTERPRETER_H
#define LOX_INTERPRETER_H
#include <stack>
#include "AST.h"
#include "visitor.h"
#include "lox_object.h"

using namespace std;

class interpreter : public Visitor{
private:
    stack<lox_object> im_results;
public:
    ~interpreter() override = default;
    void Visit_Literal_Expr(Literal_Expr* l) override;
    void Visit_Grouping_Expr(Grouping_Expr* g) override;
    void Visit_Unary_Expr(Unary_Expr* u) override;

    void evaluate(Expr* exp);
};


#endif //LOX_INTERPRETER_H
