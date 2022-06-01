//
// Created by lvxia on 2022/6/1.
//

#ifndef LOX_VISITOR_H
#define LOX_VISITOR_H

class Expr;
class Literal_Expr;
class Unary_Expr;
class Binary_Expr;
class Grouping_Expr;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void Visit_Literal_Expr(Literal_Expr* l) = 0;
    virtual void Visit_Unary_Expr(Unary_Expr* u) = 0;
    virtual void Visit_Binary_Expr(Binary_Expr* b) = 0;
    virtual void Visit_Grouping_Expr(Grouping_Expr* g) = 0;
};


#endif //LOX_VISITOR_H
