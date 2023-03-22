#include "LLVM_codegen.h"

LLVM_codegen::LLVM_codegen()
{
    TheContext = make_unique<LLVMContext>();
    TheModule = make_unique<Module>("module", *TheContext);
    builder = make_unique<IRBuilder<>>(*TheContext);

    ifstream f1("a.txt", std::ios::binary | std::ios::ate);
    if (!f1)
    {
        cout << "Cannot open file" << endl;
        exit(255);
    }

    int len = f1.tellg();
    f1.seekg(ios::beg);
    string code(len, 0);
    f1.read(&code[0], len);
    run_code(code);

    f1.close();
    current_func = nullptr;
}

void LLVM_codegen::run_code(string code)
{
    scanner s(code);

    auto tokens = s.scan_Tokens();
    cout << "*****************Scanner*****************" << endl;
	cout << tokens.size() << " tokens." << endl;
	for (const auto& i : tokens)
		cout << i->to_string() << endl;
    cout << endl;
    cout << "*****************Parser*****************" << endl;
    parser p(std::move(tokens));
    auto stmts = p.parse_stmt();

    /*//AST_Printer printer;
    //printer.print(stmts);
    cout << endl;
    cout << "*****************Interpreter*****************" << endl;*/


    FunctionType* func_type = FunctionType::get(builder->getInt32Ty(), false);
    Function* main_func = Function::Create(func_type, GlobalVariable::ExternalLinkage, "main", *TheModule);
    current_func = main_func;
    BasicBlock* BB = BasicBlock::Create(*TheContext, "entry", main_func);
    builder->SetInsertPoint(BB);



    for(auto& stmt : stmts)
    {
        stmt->codegen(this);
    }


    builder->CreateRet(builder->getInt32(0));

    TheModule->print(llvm::errs(), nullptr);

}

llvm::Value *LLVM_codegen::Visit_Literal_Expr(shared_ptr<Literal_Expr> expr)
{

    switch(expr->t->type)
    {
        case NUMBER:
            return ConstantFP::get(Type::getDoubleTy(*TheContext),expr->t->it.val);
        case STRING:
        {
            Constant *str_const = ConstantDataArray::getString(*TheContext, expr->t->it.str);
            return new GlobalVariable(*TheModule, str_const->getType(), true, GlobalVariable::PrivateLinkage, str_const, "str");
        }
        case NIL:
        {
            Constant *str_const = ConstantDataArray::getString(*TheContext, "nil");
            return new GlobalVariable(*TheModule, str_const->getType(), true, GlobalVariable::PrivateLinkage, str_const, "str");
        }
        case TRUE:
        {
            return ConstantInt::get(Type::getInt1Ty(*TheContext), 1);
        }
        case FALSE:
        {
            return ConstantInt::get(Type::getInt1Ty(*TheContext), 0);
        }
        default:
            cout << "Unexpected Literal value!" << endl;
            exit(255);
    }
}

void LLVM_codegen::Visit_Expression_Stmt(shared_ptr<Expression_Stmt> stmt)
{

    stmt->expr->codegen(this);
}

void LLVM_codegen::Visit_Print_Stmt(shared_ptr<Print_Stmt> stmt)
{

    Value* v = stmt->expr->codegen(this);



    vector<Value*> args;

    if(auto* i = dyn_cast<ConstantFP>(v))
    {
        Constant* pattern = ConstantDataArray::getString(*TheContext, "%lf\n", false);
        auto* pattern_ptr = new GlobalVariable(*TheModule, pattern->getType(), true, GlobalVariable::PrivateLinkage, pattern, "pattern_ptr");
        args.push_back(pattern_ptr);
        args.push_back(i);
    }
    else if(auto* str_ptr = dyn_cast<GlobalVariable>(v))
    {
        Constant* pattern = ConstantDataArray::getString(*TheContext, "%s\n");
        auto* pattern_ptr = new GlobalVariable(*TheModule, pattern->getType(), true, GlobalVariable::PrivateLinkage, pattern, "pattern_ptr");
        args.push_back(pattern_ptr);
        args.push_back(str_ptr);
    }
    else if(auto* bool_val = dyn_cast<ConstantInt>(v))
    {
        Constant* pattern;
        GlobalVariable* ptr;
        if(bool_val->isOne())
            pattern = ConstantDataArray::getString(*TheContext, "true", true);
        else
            pattern = ConstantDataArray::getString(*TheContext, "false", true);

        ptr = new GlobalVariable(*TheModule, pattern->getType(), true, GlobalVariable::PrivateLinkage, pattern, "boolean_ptr");
        args.push_back(ptr);
    }
    else
    {
        auto* tmp = v->getType();
        if(tmp == Type::getInt32Ty(*TheContext))
        {
            cout << "jklajldf" << endl;

        }

        //Value* d = builder->CreateUIToFP(v, Type::getDoubleTy(*TheContext));
        Constant* pattern = ConstantDataArray::getString(*TheContext, "%dhhhh\n");
        auto* pattern_ptr = new GlobalVariable(*TheModule, pattern->getType(), true, GlobalVariable::PrivateLinkage, pattern, "pattern_ptr");
        args.push_back(pattern_ptr);
        args.push_back(v);

        cout << "match failed" << v << endl;
    }

    FunctionType* printf_type = FunctionType::get(builder->getInt32Ty(), builder->getInt8PtrTy(), true);
    FunctionCallee callee = TheModule->getOrInsertFunction("printf", printf_type);
    builder->CreateCall(callee, args);
}

llvm::Value *LLVM_codegen::Visit_Unary_Expr(shared_ptr<Unary_Expr> expr)
{
    Value* v = expr->operand->codegen(this);
    Value* result = nullptr;
    if(expr->op->type == MINUS) // -expr
    {
        Constant* zero = ConstantFP::get(Type::getDoubleTy(*TheContext), 0);
        result = builder->CreateMul(zero, v, "sub_result");
    }
    else if(expr->op->type == BANG) // !expr
    {
        result = builder->CreateNot(v, "bang_result");
    }

    return result;
}

llvm::Value *LLVM_codegen::Visit_Binary_Expr(shared_ptr<Binary_Expr> expr)
{
    Value* lhs = expr->lhs->codegen(this);
    Value* rhs = expr->rhs->codegen(this);
    Value* result = nullptr;
    switch(expr->op->type)
    {
        case PLUS:
        {
            result = builder->CreateFAdd(lhs, rhs, "add_result");
            break;
        }
        case MINUS:
        {
            result = builder->CreateFSub(lhs, rhs, "sub_result");
            break;
        }
        case STAR:
        {
            result = builder->CreateFMul(lhs, rhs, "mul_result");
            break;
        }
        case SLASH:
        {
            result = builder->CreateFDiv(lhs, rhs, "div_result");
            break;
        }

        case GREATER:
        {
            result = builder->CreateFCmpOGT(lhs, rhs, "GT_result");
            break;
        }
        case GREATER_EQUAL:
        {
            result = builder->CreateFCmpOGE(lhs, rhs, "GE_result");
            break;
        }
        case LESS:
        {
            result = builder->CreateFCmpOLT(lhs, rhs, "LT_result");
            break;
        }
        case LESS_EQUAL:
        {
            result = builder->CreateFCmpOLE(lhs, rhs, "LE_result");
            break;
        }
        case EQUAL_EQUAL:
        {
            if(isa<ConstantInt>(lhs) && isa<ConstantInt>(rhs))
            {
                auto cmp_result = builder->CreateAnd(lhs, rhs, "EE_result");

            } else if(isa<ConstantFP>(lhs) && isa<ConstantFP>(rhs))
            {
                result = builder->CreateFCmpOEQ(lhs, rhs, "EE_result");
            }
            else if(isa<GlobalVariable>(lhs) && isa<GlobalVariable>(rhs))
            {
                FunctionType* strcmp_type = FunctionType::get(builder->getInt32Ty(), {builder->getInt8PtrTy(), builder->getInt8PtrTy()},
                                                              false);
                FunctionCallee Callee = TheModule->getOrInsertFunction("strcmp", strcmp_type);
                Value* strcmp_result = builder->CreateCall(Callee, {lhs, rhs});


                result = strcmp_result;


                /*auto* cmpinst = builder->CreateICmpEQ(strcmp_result, builder->getInt32(0));
                BasicBlock* trueBB = BasicBlock::Create(*TheContext, "true_br", current_func);
                BasicBlock* falseBB = BasicBlock::Create(*TheContext, "false_br", current_func);
                BasicBlock* exitBB = BasicBlock::Create(*TheContext, "exit_br", current_func);
                builder->CreateCondBr(cmpinst, trueBB, falseBB);

                builder->SetInsertPoint(trueBB);
                result = builder->getInt1(true);
                builder->CreateBr(exitBB);

                builder->SetInsertPoint(falseBB);
                result = builder->getInt1(false);
                builder->CreateBr(exitBB);

                builder->SetInsertPoint(exitBB);*/


            }
            else
            {
                result = builder->getInt1(false);
            }
            break;
        }

        default:
            cout << "Binary Expr codegen error!";
    }

    return result;
}

llvm::Value *LLVM_codegen::Visit_Grouping_Expr(shared_ptr<Grouping_Expr> expr)
{
    return expr->exp->codegen(this);
}


