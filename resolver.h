#ifndef LOX_RESOLVER_H
#define LOX_RESOLVER_H
#include <vector>
#include <unordered_map>
#include <string>
#include "visitor.h"
#include "interpreter.h"

class resolver : public Visitor
{
private:
    enum function_type {
        NONE_FUNCTION,
        FUNCTION,
        METHOD,
        INITIALIZER
    };

    enum class_type {
        NONE_CLASS_TYPE,
        CLASS_TYPE,
        SUBCLASS_TYPE
    };

    // Works kind like 'flag'. When entering corresponding scope, set the 'flag' to
    // right value and when exiting the scope, restore the previous state.
    // In 'resolve_function' and  'Visit_Class_Stmt'.
    function_type current_function;
    class_type current_class;


    interpreter& inter;
    vector<unordered_map<string, bool>> scopes;

    void begin_scope();
    void end_scope();
    void declare(const shared_ptr<Token>& name);
    void define(const shared_ptr<Token>& name);
public:
    explicit resolver(interpreter& i);
    void resolve(vector<shared_ptr<Stmt>>& stmts);
    void resolve(const shared_ptr<Stmt>& stmt);
    void resolve(const shared_ptr<Expr>& expr);
    void resolve_local(const shared_ptr<Expr>& expr, const shared_ptr<Token>& name);
    void resolve_function(const shared_ptr<Function_Stmt>& function, function_type type);



    void Visit_Block_Stmt(shared_ptr<Block_Stmt>) override;
    void Visit_Var_Stmt(shared_ptr<Var_Stmt>) override;
    void Visit_Function_Stmt(shared_ptr<Function_Stmt>) override;
    void Visit_Expression_Stmt(shared_ptr<Expression_Stmt>) override;
    void Visit_If_Stmt(shared_ptr<If_Stmt>) override;
    void Visit_Print_Stmt(shared_ptr<Print_Stmt>) override;
    void Visit_Return_Stmt(shared_ptr<Return_Stmt>) override;
    void Visit_While_Stmt(shared_ptr<While_Stmt>) override;
    void Visit_Class_Stmt(shared_ptr<Class_Stmt>) override;


    void Visit_Variable_Expr(shared_ptr<Variable_Expr>) override;
    void Visit_Assignment_Expr(shared_ptr<Assignment_Expr>) override;
    void Visit_Binary_Expr(shared_ptr<Binary_Expr>) override;
    void Visit_Call_Expr(shared_ptr<Call_Expr>) override;
    void Visit_Grouping_Expr(shared_ptr<Grouping_Expr>) override;
    void Visit_Literal_Expr(shared_ptr<Literal_Expr>) override;
    void Visit_Logical_Expr(shared_ptr<Logical_Expr>) override;
    void Visit_Unary_Expr(shared_ptr<Unary_Expr>) override;
    void Visit_Get_Expr(shared_ptr<Get_Expr>) override;
    void Visit_Set_Expr(shared_ptr<Set_Expr>) override;
    void Visit_This_Expr(shared_ptr<This_Expr>) override;
    void Visit_Super_Expr(shared_ptr<Super_Expr>) override;

    static void report(int line, const string& where, const string& msg);
    static void error(const Token& t, const string& msg);
};


#endif //LOX_RESOLVER_H
