#ifndef LOX_INTERPRETER_H
#define LOX_INTERPRETER_H
#include <stack>
#include <exception>
#include "AST.h"
#include "visitor.h"
#include "lox_object.h"
#include "lox_callable.h"
#include "interpreter_exceptions.h"
#include "environment.h"
#include "native_functions.h"
#include "lox_class.h"

using namespace std;



class interpreter : public Visitor{
private:
    unordered_map<shared_ptr<Expr>, int> locals;

    static bool is_truthy(const lox_object&);
    static bool is_equal(const lox_object&, const lox_object&);

    void Visit_Literal_Expr(shared_ptr<Literal_Expr> l) override;
    void Visit_Grouping_Expr(shared_ptr<Grouping_Expr> g) override;
    void Visit_Unary_Expr(shared_ptr<Unary_Expr> u) override;
    void Visit_Binary_Expr(shared_ptr<Binary_Expr> b) override;
    void Visit_Variable_Expr(shared_ptr<Variable_Expr>) override;
    void Visit_Assignment_Expr(shared_ptr<Assignment_Expr>) override;
    void Visit_Logical_Expr(shared_ptr<Logical_Expr>) override;
    void Visit_Call_Expr(shared_ptr<Call_Expr>) override;
    void Visit_Get_Expr(shared_ptr<Get_Expr>) override;
    void Visit_Set_Expr(shared_ptr<Set_Expr>) override;
    void Visit_This_Expr(shared_ptr<This_Expr>) override;
    void Visit_Super_Expr(shared_ptr<Super_Expr>) override;

    void Visit_Expression_Stmt(shared_ptr<Expression_Stmt>) override;
    void Visit_Print_Stmt(shared_ptr<Print_Stmt>) override;
    void Visit_Var_Stmt(shared_ptr<Var_Stmt>) override;
    void Visit_Block_Stmt(shared_ptr<Block_Stmt>) override;
    void Visit_If_Stmt(shared_ptr<If_Stmt>) override;
    void Visit_While_Stmt(shared_ptr<While_Stmt>) override;
    void Visit_Function_Stmt(shared_ptr<Function_Stmt>) override;
    void Visit_Return_Stmt(shared_ptr<Return_Stmt>) override;
    void Visit_Class_Stmt(shared_ptr<Class_Stmt>) override;

    shared_ptr<lox_object> lookup_variable(const shared_ptr<Token>& name, const shared_ptr<Expr>& expr);
public:
    stack<shared_ptr<lox_object>> im_results;
    void _evaluate(const shared_ptr<Expr>& exp);
    bool _evaluate_cond(const shared_ptr<Expr>& expr);
    void _execute(const shared_ptr<Stmt>& stmt);
    void _execute_Block(const shared_ptr<vector<shared_ptr<Stmt>>>& stmts, shared_ptr<environment> new_env);
    static void _print_lox_object(const shared_ptr<lox_object>&);

    shared_ptr<environment> env, globals;
    ~interpreter() override = default;
    interpreter();
    void eval(const shared_ptr<Expr>& exp);
    void interpret(const vector<shared_ptr<Stmt>>& stmts);
    void resolve(const shared_ptr<Expr>& expr, int depth);
};


#endif //LOX_INTERPRETER_H
