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
