#include <iostream>
#include "antlr4-runtime.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Evalvisitor.h"

using namespace antlr4;
//todo: regenerating files in directory named "generated" is dangerous.
//	if you really need to regenerate,please ask TA for help.
int main(int argc, const char* argv[])
{
	//todo:please don't modify the code below the construction of ifs if you want to use visitor mode
//	std::ifstream in("/mnt/d/Academy/OIACM/Code/Homework/Compiler/python/Python_Assignment-master/src/test_program.py");
//	std::cin.rdbuf(in.rdbuf());
	ANTLRInputStream input(std::cin);
	Python3Lexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	tokens.fill();
	Python3Parser parser(&tokens);
	tree::ParseTree* tree = parser.file_input();
	EvalVisitor visitor;
	visitor.visit(tree);
	return 0;
}