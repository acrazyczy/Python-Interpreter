//
// Created by crazy_cloud on 2019/12/3.
//

#ifndef CODE_NAME_SPACE_H
#define CODE_NAME_SPACE_H

#include <algorithm>
#include <string>
#include <map>
#include "Python3BaseVisitor.h"
#include "Dynamic_Type.h"

class name_space
{
private:
	static std::map<std::string , dtype> static_var_sys;
	static std::map<std::string , Python3Parser::FuncdefContext*> static_func_sys;

	std::map<std::string , dtype> var_sys;
	std::map<std::string , Python3Parser::FuncdefContext*> func_sys;
public:
	static bool is_global_block;

	name_space(){}

	dtype &operator[](const std::string &var_name);//If the variable doesn't exist, then create it.
	void remove(const std::string &var_name);

	Python3Parser::FuncdefContext *operator()(const std::string &func_name) const;//If the function doesn't exist, then return nullptr;
	void create(const std::pair<std::string , Python3Parser::FuncdefContext*> &x);

	~name_space(){}
};

#endif //CODE_NAME_SPACE_H
