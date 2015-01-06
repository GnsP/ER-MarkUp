#ifndef ER_MARKUP_SYMBOL_TABLE_HPP_
#define ER_MARKUP_SYMBOL_TABLE_HPP_

#include "includes.hpp"
#include "structure.hpp"

class EntityTable{
	public:
		map<string, Entity> table_;

		inline void insert(const char *name, Entity ent){
			string n(name);
			table_.insert(make_pair<string,Entity>(n,ent));
		}
};

#endif
