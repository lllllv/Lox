#ifndef LOX_VISITOR_H
#define LOX_VISITOR_H
#include <memory>

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

using namespace std;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void Visit_Literal_Expr(shared_ptr<Literal_Expr>) = 0;
    virtual void Visit_Unary_Expr(shared_ptr<Unary_Expr>) = 0;
    virtual void Visit_Binary_Expr(shared_ptr<Binary_Expr>) = 0;
    virtual void Visit_Grouping_Expr(shared_ptr<Grouping_Expr>) = 0;
    virtual void Visit_Variable_Expr(shared_ptr<Variable_Expr>) = 0;
    virtual void Visit_Assignment_Expr(shared_ptr<Assignment_Expr>) = 0;
    virtual void Visit_Logical_Expr(shared_ptr<Logical_Expr>) = 0;
    virtual void Visit_Call_Expr(shared_ptr<Call_Expr>) = 0;
    virtual void Visit_Get_Expr(shared_ptr<Get_Expr>) = 0;
    virtual void Visit_Set_Expr(shared_ptr<Set_Expr>) = 0;
    virtual void Visit_This_Expr(shared_ptr<This_Expr>) = 0;
    virtual void Visit_Super_Expr(shared_ptr<Super_Expr>) = 0;

    virtual void Visit_Expression_Stmt(shared_ptr<Expression_Stmt>) = 0;
    virtual void Visit_Print_Stmt(shared_ptr<Print_Stmt>) = 0;
    virtual void Visit_Var_Stmt(shared_ptr<Var_Stmt>) = 0;
    virtual void Visit_Block_Stmt(shared_ptr<Block_Stmt>) = 0;
    virtual void Visit_If_Stmt(shared_ptr<If_Stmt>) = 0;
    virtual void Visit_While_Stmt(shared_ptr<While_Stmt>) = 0;
    virtual void Visit_Function_Stmt(shared_ptr<Function_Stmt>) = 0;
    virtual void Visit_Return_Stmt(shared_ptr<Return_Stmt>) = 0;
    virtual void Visit_Class_Stmt(shared_ptr<Class_Stmt>) = 0;
};



#endif //LOX_VISITOR_H
