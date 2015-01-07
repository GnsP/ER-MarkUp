
/**
	RIGHT TO USE, DISTRIBUTE AND MODIFY
	===================================

	Copyright (C) 2015 Ganesh Prasad Sahoo - All Rights Reserved

	You may use, distribute and modify this code under the Terms 
	of GNU GPL V3 License. You should have received a copy of the
	GNU GPL v3 License with this file. If not please write to
		
		sir.gnsp@gmail.com

	or visit 
	
		http://www.gnu.org/licenses/gpl.txt


*****************************************************************************
*/



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
