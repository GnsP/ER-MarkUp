#ifndef ER_MARKUP_SYMBOL_TABLE_HPP_
#define ER_MARKUP_SYMBOL_TABLE_HPP_

#include "includes.hpp"
#include "structure.hpp"

class EntityTable{
	public:
		map<const char *, Entity> table_;
};

#endif
