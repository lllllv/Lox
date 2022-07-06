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
class Variable_Expr;
class Assignment_Expr;
class Logical_Expr;
class Call_Expr;
class Get_Expr;
class Set_Expr;
class This_Expr;
class Super_Expr;

class Stmt;
class Expression_Stmt;
class Print_Stmt;
class Var_Stmt;
class Block_Stmt;
class If_Stmt;
class While_Stmt;
class Function_Stmt;
class Return_Stmt;
class Class_Stmt;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void Visit_Literal_Expr(Literal_Expr*) = 0;
    virtual void Visit_Unary_Expr(Unary_Expr*) = 0;
    virtual void Visit_Binary_Expr(Binary_Expr*) = 0;
    virtual void Visit_Grouping_Expr(Grouping_Expr*) = 0;
    virtual void Visit_Variable_Expr(Variable_Expr*) = 0;
    virtual void Visit_Assignment_Expr(Assignment_Expr*) = 0;
    virtual void Visit_Logical_Expr(Logical_Expr*) = 0;
    virtual void Visit_Call_Expr(Call_Expr*) = 0;
    virtual void Visit_Get_Expr(Get_Expr*) = 0;
    virtual void Visit_Set_Expr(Set_Expr*) = 0;
    virtual void Visit_This_Expr(This_Expr*) = 0;
    virtual void Visit_Super_Expr(Super_Expr*) = 0;

    virtual void Visit_Expression_Stmt(Expression_Stmt*) = 0;
    virtual void Visit_Print_Stmt(Print_Stmt*) = 0;
    virtual void Visit_Var_Stmt(Var_Stmt*) = 0;
    virtual void Visit_Block_Stmt(Block_Stmt*) = 0;
    virtual void Visit_If_Stmt(If_Stmt*) = 0;
    virtual void Visit_While_Stmt(While_Stmt*) = 0;
    virtual void Visit_Function_Stmt(Function_Stmt*) = 0;
    virtual void Visit_Return_Stmt(Return_Stmt*) = 0;
    virtual void Visit_Class_Stmt(Class_Stmt*) = 0;
};







#endif //LOX_VISITOR_H
