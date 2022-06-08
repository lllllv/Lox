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
            cout << "Unexpected Literal value!" << endl;
            exit(255);
    }
}

void interpreter::Visit_Grouping_Expr(Grouping_Expr *g) {
    _evaluate(g->exp);
}

void interpreter::_evaluate(Expr *exp) {
    exp->accept(this);
}

void interpreter::Visit_Unary_Expr(Unary_Expr *u) {
    _evaluate(u->operand);

    switch(u->op->type)
    {
        case MINUS:
        {
            lox_object tmp = im_results.top();
            im_results.pop();
            tmp.num = -tmp.num;
            im_results.push(tmp);
            break;
        }
        case BANG:
        {
            lox_object tmp = im_results.top();
            im_results.pop();
            im_results.push(lox_object(is_truthy(tmp)));
            break;
        }
        default:
            cout << "Unexpected Unary operator type!" << endl;
            exit(255);
    }
}

bool interpreter::is_truthy(const lox_object & l) {
    if(l.type == NIL)
        return false;
    if(l.type == TRUE)
        return true;
    if(l.type == FALSE)
        return false;
    return true;
}

bool interpreter::is_equal(const lox_object &l1, const lox_object &l2) {
    if(l1.type == NIL && l2.type == NIL)
        return true;
    else if(l1.type == NIL || l2.type == NIL)
        return false;

    if(l1.type != l2.type)
        return false;

    if(l1.type == NUMBER)
        return l1.num == l2.num;
    else if(l1.type == STRING)
        return l1.str == l2.str;
    else
        return l1.boolean == l2.boolean;
}

void interpreter::Visit_Binary_Expr(Binary_Expr *b) {
    _evaluate(b->lhs);
    _evaluate(b->rhs);

    lox_object rhs = im_results.top();
    im_results.pop();
    lox_object lhs = im_results.top();
    im_results.pop();

    switch(b->op->type)
    {
        case PLUS:
            if(lhs.type == NUMBER && rhs.type == NUMBER)
                im_results.push(lox_object((double)(lhs.num + rhs.num)));
            if(lhs.type == STRING && rhs.type == STRING)
                im_results.push(lox_object(lhs.str + rhs.str));
            break;
        case MINUS:
            im_results.push(lox_object((double)(lhs.num - rhs.num)));
            break;
        case STAR:
            im_results.push(lox_object((double)(lhs.num * rhs.num)));
            break;
        case SLASH:
            im_results.push(lox_object((double)(lhs.num / rhs.num)));
            break;


        case GREATER:
            im_results.push(lox_object(lhs.num > rhs.num));
            break;
        case GREATER_EQUAL:
            im_results.push(lox_object(lhs.num >= rhs.num));
            break;
        case LESS:
            im_results.push(lox_object(lhs.num < rhs.num));
            break;
        case LESS_EQUAL:
            im_results.push(lox_object(lhs.num <= rhs.num));
            break;

        case EQUAL_EQUAL:
            im_results.push(lox_object(is_equal(lhs, rhs)));
            break;
        case BANG_EQUAL:
            im_results.push(lox_object(!is_equal(lhs, rhs)));
            break;

    }
}

interpreter::interpreter(Expr *exp) : expr(exp) {

}

void interpreter::print(const lox_object& l) {


    switch(l.type)
    {
        case NUMBER:
            cout << l.num;
            break;
        case STRING:
            cout << l.str;
            break;
        case NIL:
            cout << "nil";
            break;
        case TRUE:
            cout << "true";
            break;
        case FALSE:
            cout << "false";
            break;

        default:
            cout << "Unknown result!";
            break;
    }
}

void interpreter::eval() {
    _evaluate(this->expr);
    lox_object res = im_results.top();
    im_results.pop();
    print(res);
}

void interpreter::Visit_Expression(Expression *) {

}

void interpreter::Visit_Print(Print *) {

}
