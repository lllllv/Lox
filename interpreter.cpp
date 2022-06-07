//
// Created by lvxia on 2022/6/7.
//

#include "interpreter.h"


void interpreter::Visit_Literal_Expr(Literal_Expr *l) {
    switch(l->t->type)
    {
        case NUMBER:
            this->im_results.push(lox_object(l->t->it.val));
            break;
        case STRING:
            this->im_results.push(lox_object(l->t->it.str));
            break;
        case NIL:
            this->im_results.push(lox_object());
            break;
        case TRUE:
            this->im_results.push(lox_object(true));
            break;
        case FALSE:
            this->im_results.push(lox_object(false));
            break;
        default:
            cout << "Unexpected Literal value!." << endl;
            exit(255);
    }
}

void interpreter::Visit_Grouping_Expr(Grouping_Expr *g) {
    evaluate(g->exp);
}

void interpreter::evaluate(Expr *exp) {
    exp->accept(this);
}

void interpreter::Visit_Unary_Expr(Unary_Expr *u) {
    evaluate(u->operand);

    switch(u->op->type)
    {
        case MINUS:
            lox_object tmp = im_results.top();
            im_results.pop();
            tmp.num = -tmp.num;
            im_results.push(tmp);
            break;
        case BANG:

    }
}




