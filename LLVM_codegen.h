#ifndef LOX_LLVM_CODEGEN_H
#define LOX_LLVM_CODEGEN_H

#include <fstream>
#include <iostream>

#include "Codegen_visitor.h"

#include "scanner.h"
#include "parser.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

using namespace std;
using namespace llvm;

class LLVM_codegen : public Codegen_visitor
{
private:
    unique_ptr<LLVMContext> TheContext;
    unique_ptr<Module> TheModule;
    unique_ptr<IRBuilder<>> builder;
    Function* current_func;

public:
    LLVM_codegen();
    void run_code(string code);

    llvm::Value* Visit_Literal_Expr(shared_ptr<Literal_Expr>) override;
    llvm::Value* Visit_Unary_Expr(shared_ptr<Unary_Expr>) override;
    llvm::Value* Visit_Binary_Expr(shared_ptr<Binary_Expr>) override;
    llvm::Value* Visit_Grouping_Expr(shared_ptr<Grouping_Expr>) override;

    void Visit_Expression_Stmt(shared_ptr<Expression_Stmt>) override;
    void Visit_Print_Stmt(shared_ptr<Print_Stmt>) override;
};


#endif //LOX_LLVM_CODEGEN_H
