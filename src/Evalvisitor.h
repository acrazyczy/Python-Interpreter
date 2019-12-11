#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include "Python3BaseVisitor.h"
#include <algorithm>
#include <stack>
#include <map>
#include "Name_Space.h"

class EvalVisitor: public Python3BaseVisitor {
private:

	class BREAK_SIGN{};

	class CONTINUE_SIGN{};

	class RETURN_SIGN
	{
	public:
		antlrcpp::Any ret_val;

		RETURN_SIGN(const antlrcpp::Any ret_val_){ret_val = ret_val_;}
	};

	std::stack<name_space> stack_workspace;

	int loop_cnt = 0;

//todo:override all methods of Python3BaseVisitor
public:

	virtual antlrcpp::Any visitFile_input(Python3Parser::File_inputContext *ctx) override;

	virtual antlrcpp::Any visitFuncdef(Python3Parser::FuncdefContext *ctx) override;

	virtual antlrcpp::Any visitParameters(Python3Parser::ParametersContext *ctx) override;

	virtual antlrcpp::Any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override;

	virtual antlrcpp::Any visitTfpdef(Python3Parser::TfpdefContext *ctx) override;

	virtual antlrcpp::Any visitStmt(Python3Parser::StmtContext *ctx) override;

	virtual antlrcpp::Any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override;

	virtual antlrcpp::Any visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) override;

	virtual antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override;

	virtual antlrcpp::Any visitAugassign(Python3Parser::AugassignContext *ctx) override;

	virtual antlrcpp::Any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override;

	virtual antlrcpp::Any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override;

	virtual antlrcpp::Any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override;

	virtual antlrcpp::Any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override;

	virtual antlrcpp::Any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override;

	virtual antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override;

	virtual antlrcpp::Any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override;

	virtual antlrcpp::Any visitSuite(Python3Parser::SuiteContext *ctx) override;

	virtual antlrcpp::Any visitTest(Python3Parser::TestContext *ctx) override;

	virtual antlrcpp::Any visitOr_test(Python3Parser::Or_testContext *ctx) override;

	virtual antlrcpp::Any visitAnd_test(Python3Parser::And_testContext *ctx) override;

	virtual antlrcpp::Any visitNot_test(Python3Parser::Not_testContext *ctx) override;

	virtual antlrcpp::Any visitComparison(Python3Parser::ComparisonContext *ctx) override;

	virtual antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext *ctx) override;

	virtual antlrcpp::Any visitArith_expr(Python3Parser::Arith_exprContext *ctx) override;

	virtual antlrcpp::Any visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) override;

	virtual antlrcpp::Any visitTerm(Python3Parser::TermContext *ctx) override;

	virtual antlrcpp::Any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) override;

	virtual antlrcpp::Any visitFactor(Python3Parser::FactorContext *ctx) override;

	virtual antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override;

	virtual antlrcpp::Any visitTrailer(Python3Parser::TrailerContext *ctx) override;

	virtual antlrcpp::Any visitAtom(Python3Parser::AtomContext *ctx) override;

	virtual antlrcpp::Any visitTestlist(Python3Parser::TestlistContext *ctx) override;

	virtual antlrcpp::Any visitArglist(Python3Parser::ArglistContext *ctx) override;

	virtual antlrcpp::Any visitArgument(Python3Parser::ArgumentContext *ctx) override;
};


#endif //PYTHON_INTERPRETER_EVALVISITOR_H
