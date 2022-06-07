//
// Created by lvxia on 2022/6/1.
//

#include "AST.h"


void Literal_Expr::accept(Visitor *v) {
    v->Visit_Literal_Expr(this);
}

void Unary_Expr::accept(Visitor *v) {
    v->Visit_Unary_Expr(this);
}

void Binary_Expr::accept(Visitor *v) {
    v->Visit_Binary_Expr(this);
}

void Grouping_Expr::accept(Visitor *v) {
    v->Visit_Grouping_Expr(this);
}

/*void Expr::accept(Visitor *v) {
    v->Visit_Expr(this);
}*/

