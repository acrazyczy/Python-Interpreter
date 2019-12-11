//
// Created by crazy_cloud on 2019/12/3.
//

#include "Name_Space.h"

bool name_space::is_global_block = 1;

std::map<std::string , dtype> name_space::static_var_sys;
std::map<std::string , Python3Parser::FuncdefContext*> name_space::static_func_sys;
std::map<Python3Parser::FuncdefContext* , std::vector<std::pair<std::string , dtype> > > name_space::func_table;
std::stack<std::vector<std::string> > name_space::crt;

dtype &name_space::operator[](const std::string &var_name)
{
	std::map<std::string , dtype>::iterator it = static_var_sys.find(var_name);
	if (it == static_var_sys.end())
		if (is_global_block) it = static_var_sys.insert(std::make_pair(var_name , dtype())).first , crt.top().push_back(var_name);
		else
		{
			it = var_sys.find(var_name);
			if (it == var_sys.end()) it = var_sys.insert(std::make_pair(var_name , dtype())).first , crt.top().push_back(var_name);
		}
	return it -> second;
}

void name_space::remove(const std::string &name)
{
	if (is_global_block)
		if (operator()(name) == nullptr) static_var_sys.erase(name);
		else static_func_sys.erase(name);
	else
		if (operator()(name) == nullptr) var_sys.erase(name);
		else func_sys.erase(name);
}

Python3Parser::FuncdefContext *name_space::operator()(const std::string &func_name) const
{
	std::map<std::string , Python3Parser::FuncdefContext*>::const_iterator it = static_func_sys.find(func_name);
	if (it == static_func_sys.end())
		if (!is_global_block)
		{
			it = func_sys.find(func_name);
			if (it == func_sys.end()) return nullptr;
		}else return nullptr;
	return it == static_func_sys.end() ? nullptr : it -> second;
}

void name_space::create(const std::pair<std::string , Python3Parser::FuncdefContext*> &x)
{
	is_global_block ? static_func_sys.insert(x) : func_sys.insert(x);
	func_table.insert(std::make_pair(x.second , std::vector< std::pair<std::string , dtype> >()));
}

std::vector<std::pair<std::string , dtype> > &name_space::getarglist(Python3Parser::FuncdefContext* ptr) const
{
	return func_table[ptr];
}