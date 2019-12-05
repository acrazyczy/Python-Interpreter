#include "Evalvisitor.h"

antlrcpp::Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx)
{
	crt.push(std::vector<std::string>());
	antlrcpp::Any ret = visitChildren(ctx);
	for (std::string x: crt.top()) name_space().remove(x);
	return crt.pop() , ret;
}

antlrcpp::Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx)
{
	name_space &nsp = stack_workspace.top();
	nsp.create(std::make_pair(ctx -> NAME() -> getText() , ctx)) , crt.top().push_back(ctx -> NAME() -> getText());
	return nullptr;
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx)
{
	antlrcpp::Any tmp = visitTestlist(ctx -> testlist().back());
	std::vector<dtype> ret;
	if (tmp.is<dtype>()) ret.push_back(tmp.as<dtype>());
	else if (tmp.is<std::vector<dtype> >()) ret = tmp.as<std::vector<dtype> >();
	else return nullptr;
	name_space &nsp = stack_workspace.top();
	if (ctx -> augassign() != nullptr)
	{
		for (int i = 0 , tot = (int)ret.size();i < tot;++ i)
		{
			dtype &var = nsp[ctx -> testlist()[0] -> test()[i] -> or_test() -> and_test()[0] -> not_test()[0] -> comparison() -> arith_expr()[0] -> term()[0] -> factor()[0] -> atom_expr() -> atom() -> NAME() -> getText()];
			switch (ctx -> augassign() -> getText()[0])
			{
				case '+':var += ret[i];break;
				case '-':var -= ret[i];break;
				case '*':var *= ret[i];break;
				case '/':
				{
					ctx -> augassign() -> getText().length() == 1 ? var /= ret[i] : (var /= ret[i]).to_int();
					break;
				}
				case '%':var %= ret[i];break;
			}
			ret[i] = var;
		}
	}
	else for (int i = (int)ctx -> testlist().size() - 2;i >= 0;-- i)
		for (int j = 0 , tot = (int)ret.size(); j< tot;++ j)
			nsp[ctx -> testlist()[i] -> test()[j] -> or_test() -> and_test()[0] -> not_test()[0] -> comparison() -> arith_expr()[0] -> term()[0] -> factor()[0] -> atom_expr() -> atom() -> NAME() -> getText()] = ret[j];
	return ret;
}

antlrcpp::Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx)
{
	if (loop_cnt) return BREAK_SIGN();
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx)
{
	if (loop_cnt) return CONTINUE_SIGN();
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx)
{
	std::vector<dtype> ret;
	if (ctx -> testlist() != nullptr) ret = visitTestlist(ctx -> testlist()).as<std::vector<dtype> >();
	return RETURN_SIGN(ret);
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx)
{
	for (int i = 0 , tot = (int)ctx -> test().size();i < tot;++ i)
		if ((bool)visitTest(ctx -> test()[i]).as<dtype>())
			return visitSuite(ctx -> suite()[i]);
	if (ctx -> ELSE() != nullptr) return visitSuite(ctx -> suite().back());
	return nullptr;
}


antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx)
{
	antlrcpp::Any ret;
	++ loop_cnt;
	while ((bool)visitTest(ctx -> test()).as<dtype>())
	{
		ret = visitSuite(ctx -> suite());
		if (ret.is<BREAK_SIGN>())
		{
			ret = nullptr;
			break;
		}
		if (ret.is<CONTINUE_SIGN>()) ret = nullptr;
		if (ret.is<RETURN_SIGN>()) break;
	}
	return -- loop_cnt , ret;
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx)
{
	crt.push(std::vector<std::string>());
	antlrcpp::Any ret;
	if (ctx -> simple_stmt() != nullptr) ret = visitSimple_stmt(ctx -> simple_stmt());
	else for (int i = 0 , tot = (int)ctx -> stmt().size();i < tot;++ i)
	{
		ret = visitStmt(ctx -> stmt()[i]);
		if (ret.is<BREAK_SIGN>() || ret.is<CONTINUE_SIGN>() || ret.is<RETURN_SIGN>()) break;
	}
	name_space &nsp = stack_workspace.top();
	for (std::string x: crt.top()) nsp.remove(x);
	return crt.pop() , ret;
}

antlrcpp::Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx)
{
	return visitOr_test(ctx -> or_test());
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx)
{
	if ((int)ctx -> and_test().size() == 1) return visitAnd_test(ctx -> and_test()[0]);
	dtype ret = visitAnd_test(ctx -> and_test()[0]).as<dtype>();
	for (int i = 1 , tot = (int)ctx -> and_test().size();i < tot;++ i) ret |= visitAnd_test(ctx -> and_test()[i]).as<dtype>();
	return ret;
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx)
{
	if ((int)ctx -> not_test().size() == 1) return visitNot_test(ctx -> not_test()[0]);
	dtype ret = visitNot_test(ctx -> not_test()[0]).as<dtype>();
	for (int i = 1 , tot = (int)ctx -> not_test().size();i < tot;++ i) ret &= visitNot_test(ctx -> not_test()[i]).as<dtype>();
	return ret;
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx)
{
	if (ctx -> not_test() == nullptr) return visitComparison(ctx -> comparison());
	return !visitNot_test(ctx -> not_test()).as<dtype>();
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx)
{
	if ((int)ctx -> comp_op().empty()) return visitArith_expr(ctx -> arith_expr()[0]);
	dtype ret(true);
	for (int i = 0 , tot = (int)ctx -> comp_op().size();i < tot;++ i)
	{
		dtype x = visitArith_expr(ctx -> arith_expr()[i]).as<dtype>() , y = visitArith_expr(ctx -> arith_expr()[i + 1]).as<dtype>();
		switch (ctx -> comp_op()[i] -> getText()[0])
		{
			case '<':
				ret &= ctx -> comp_op()[i] -> getText().length() == 1 ? x < y : x <= y;
				break;
			case '>':
				ret &= ctx -> comp_op()[i] -> getText().length() == 1 ? x > y : x >= y;
				break;
			case '=':
				ret &= x == y;
				break;
			case '!':
				ret &= x != y;
				break;
		}
	}
 	return ret;
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx)
{
	if ((int)ctx -> term().size() == 1) return visitTerm(ctx -> term()[0]);
	dtype ret = visitTerm(ctx -> term()[0]).as<dtype>();
	for (int i = 0 , tot = (int)ctx -> addorsub_op().size();i < tot;++ i)
		ctx -> addorsub_op()[i] -> getText()[0] == '+' ? ret += visitTerm(ctx -> term()[i + 1]).as<dtype>() : ret -= visitTerm(ctx -> term()[i + 1]).as<dtype>();
	return ret;
}

antlrcpp::Any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx)
{
	if ((int)ctx -> factor().size() == 1) return visitFactor(ctx -> factor()[0]);
	dtype ret = visitFactor(ctx -> factor()[0]).as<dtype>();
	for (int i = 0 , tot = (int)ctx -> muldivmod_op().size();i < tot;++ i)
		switch (ctx -> muldivmod_op()[i] -> getText()[0])
		{
			case '*' : ret *= visitFactor(ctx -> factor()[i + 1]).as<dtype>();break;
			case '/' :
				ctx -> muldivmod_op()[i] -> getText().length() == 1 ?
					ret /= visitFactor(ctx -> factor()[i + 1]).as<dtype>().to_float()
				:
					(ret /= visitFactor(ctx -> factor()[i + 1]).as<dtype>()).to_int();
				break;
			case '%' : ret %= visitFactor(ctx -> factor()[i + 1]).as<dtype>();break;
		}
	return ret;
}

antlrcpp::Any EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx)
{
	if (ctx->atom_expr() == nullptr)
		return ctx->MINUS() == nullptr ? + visitFactor(ctx->factor()).as<dtype>() : - visitFactor(ctx->factor()).as<dtype>();
	return visitAtom_expr(ctx->atom_expr());
}

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx)
{
	if (ctx -> trailer() == nullptr) return visitAtom(ctx -> atom());
	else if (ctx -> atom() -> NAME() -> getText() == std::string("print"))
	{
		if (ctx -> trailer() -> arglist() != nullptr)
			for (int i = 0 , tot = (int)ctx -> trailer() -> arglist() -> argument().size();i < tot;++ i)
			{
				if (i) std::cout << " ";
				std::cout << visitTest(ctx -> trailer() -> arglist() -> argument()[i] -> test()[0]).as<dtype>();
			}
		std::cout << std::endl;
		return nullptr;
	}
	else if (ctx -> atom() -> NAME() -> getText() == std::string("int"))
	{
		if (ctx -> trailer() -> arglist() == nullptr) return dtype(integer(std::string("0")));
		else return visitTest(ctx -> trailer() -> arglist() -> argument()[0] -> test()[0]).as<dtype>().to_int();
	}
	else if (ctx -> atom() -> NAME() -> getText() == std::string("float"))
	{
		if (ctx -> trailer() -> arglist() == nullptr) return dtype((double)0.);
		else return visitTest(ctx -> trailer() -> arglist() -> argument()[0] -> test()[0]).as<dtype>().to_float();
	}
	else if (ctx -> atom() -> NAME() -> getText() == std::string("str"))
	{
		if (ctx -> trailer() -> arglist() == nullptr) return dtype(std::string("0"));
		else return visitTest(ctx -> trailer() -> arglist() -> argument()[0] -> test()[0]).as<dtype>().to_str();
	}
	else if (ctx -> atom() -> NAME() -> getText() == std::string("bool"))
	{
		if (ctx -> trailer() -> arglist() == nullptr) return dtype(false);
		else return visitTest(ctx -> trailer() -> arglist() -> argument()[0] -> test()[0]).as<dtype>().to_bool();
	}
	else
	{
		Python3Parser::FuncdefContext *func_node = visitAtom(ctx -> atom()).as<Python3Parser::FuncdefContext*>();
		bool was_global_block = name_space::is_global_block;
		stack_workspace.push(name_space());
		name_space &nsp = stack_workspace.top();name_space::is_global_block = 0;
		if (ctx -> trailer() -> arglist() != nullptr)
		{
			std::map<std::string , bool> ext;
			Python3Parser::TypedargslistContext *tdl_node = func_node -> parameters() -> typedargslist();
			for (int i = 0 , tot = (int)ctx -> trailer() -> arglist() -> argument().size();i < tot;++ i)
				if (ctx -> trailer() -> arglist() -> argument()[i] -> ASSIGN() == nullptr)
					nsp[tdl_node -> tfpdef()[i] -> NAME() -> getText()] = visitTest(ctx -> trailer() -> arglist() -> argument()[i] -> test()[0]).as<dtype>();
				else
				{
					std::string var_name = ctx -> trailer() -> arglist() -> argument()[i] -> test()[0] -> or_test() -> and_test()[0] -> not_test()[0] -> comparison() -> arith_expr()[0] -> term()[0] -> factor()[0] -> atom_expr() -> atom() -> NAME() -> getText();
					nsp[var_name] = visitTest(ctx -> trailer() -> arglist() -> argument()[i] -> test()[1]).as<dtype>();
					ext[var_name] = 1;
				}
			for (int tot = (int) tdl_node -> tfpdef().size() , i = tot - (int) tdl_node -> test().size() , j = 0;i < tot;++ i , ++ j)
			{
				std::string var_name = tdl_node -> tfpdef()[i] -> NAME() -> getText();
				if (!ext[var_name]) nsp[var_name] = visitTest(tdl_node -> test()[j]);
			}
		}
		antlrcpp::Any ret = visitSuite(func_node -> suite());
		if (!ret.is<RETURN_SIGN>()) ret = nullptr;
		else
		{
			std::vector<dtype> tmp = ret.as<RETURN_SIGN>().ret;
			if (tmp.empty()) ret = nullptr;
			else if ((int)tmp.size() == 1) ret = tmp.front();
			else ret = tmp;
		}
		return stack_workspace.pop() , name_space::is_global_block = was_global_block , ret;
	}
}

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx)
{
	if (ctx -> NAME() != nullptr)
	{
		name_space &nsp = stack_workspace.top();
		Python3Parser::FuncdefContext *ptr = nsp(ctx -> NAME() -> getText());
		if (ptr == nullptr) return nsp[ctx -> NAME() -> getText()];
		else return ptr;
	}
	else if (ctx -> NUMBER() != nullptr)
	{
		dtype ret(ctx -> NUMBER() -> getText());
		return ctx -> NUMBER() -> getText().find('.') == std::string::npos ? ret.to_int() : ret.to_float();
	}
	else if (!ctx -> STRING().empty())
	{
		dtype ret(std::string(""));
		for (int i = 0 , tot = (int)ctx -> STRING().size();i < tot;++ i)
		{
			std::string tmp = ctx -> STRING()[i] -> getText();
			tmp.erase(tmp.begin()) , tmp.pop_back() , ret += dtype(tmp);
		}
		return ret;
	}
	else if (ctx -> NONE() != nullptr) return dtype();
	else if (ctx -> test() != nullptr) return visitTest(ctx -> test()).as<dtype>();
	else return dtype(ctx -> TRUE() != nullptr);
}

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx)
{
	if ((int)ctx -> test().size() == 1) return visitTest(ctx -> test()[0]);
	std::vector<dtype> ret;
	for (int i = 0 , tot = (int)ctx -> test().size();i < tot;++ i) ret.push_back(visitTest(ctx -> test()[i]).as<dtype>());
	return ret;
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx)
{
	return visitChildren(ctx);
}