
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


#ifndef ER_MARKUP_STRUCTURE_HPP_
#define ER_MARKUP_STRUCTURE_HPP_

#include "includes.hpp"
using namespace std;

enum AttrType { _NONE_ = 5543, _MULTI, _COMPOSITE, _KEY, _DERIVED};

struct Attribute{
	char name_[100];
	vector<AttrType> type_;
	vector<Attribute> attr_;

	int node_no_;
	void printDot(ofstream &fout, int parent);

	Attribute():node_no_(nodeCounter++){}
	void destruct(){
		vector<AttrType>().swap(type_);
		vector<Attribute>().swap(attr_);
	}
};

struct Entity{
	char name_[100];
	bool weak_;
	vector<Attribute> attr_;
	
	int node_no_;
	void printDot(ofstream &fout);

	Entity():node_no_(nodeCounter++){}
};

struct Edge{
	char ent_[100];
	bool weak_;
	bool complete_;
	bool normal_;
	bool many_;
	
	void printDot(ofstream &fout, int parent);
};

struct Relation{
	char name_[100];
	bool weak_;
	vector<Edge> from_;
	vector<Edge> to_;
	
	int node_no_;
	void printDot(ofstream &fout);
	
	Relation():node_no_(nodeCounter++){weak_=false;}
};

struct ER_Diagram{
	char name_[100];
	vector<Relation> graph_;
};

#endif
