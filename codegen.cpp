#include "parser.hpp"
using namespace std;

int nodeCounter=1;

void Parser::generateCode(const char *outFileName){
	ofstream fout;
	fout.open(outFileName);

	fout<<"graph G{ nodesep=0.5; ordering=out; splines=ortho; label=\""
		<<diagram_.name_<<endl
		<<"\"; node[fontsize=14, fontname=\"Consolas\"];"<<endl
		<<"edge[fontsize=14, fontname=\"Consolas\"];"<<endl;
	
	for(map<const char *,Entity>::iterator it=entTbl_.table_.begin();
		it!=entTbl_.table_.end(); ++it)
		it->second.printDot(fout);

	for(size_t i=0; i<diagram_.graph_.size(); ++i)
		diagram_.graph_[i].printDot(fout);

	fout<<"}";
	return;
}

void Entity::printDot(ofstream &fout){
	sstream nodeName("node_");
	nodeName<<node_no_;

	fout<<nodeName.str()<<"[shpae=box, label=\""<<name_<<"\""
		<<(weak_?",peripheries=2":"")<<"];"<<endl;

	for(size_t i=0; i<attr_.size(); ++i)
		attr_[i].printDot(fout,node_no_);

	return;
}

void Attribute::printDot(ofstream &fout, int parent){
	sstream nodeName("node_");
	sstream parName("node_");

	nodeName<<node_no_;
	parName<<parent;

	bool underline = false;
	fout<<nodeName.str()<<"[";
	for(size_t i=0; i<type_.size(); ++i){
		switch(type_[i]){
			case _MULTI:
				fout<<"peripheries=2,";
				break;
			case _COMPOSITE: break;
			case _KEY:
				underline = true;
				break;
			case _DERIVED:
				fout<<"style=dashed,";
				break;
			default:
				break;
		}
	}
	fout<<"label="<<(underline?"<<u>":"\"")<<name_<<(underline?"</u>>":"\"")
		<<"];"<<endl;

	fout<<nodeName.str()<<"--"<<parName.str()<<";"<<endl;

	for(size_t i=0; i<attr_.size(); ++i)
		attr_[i].printDot(fout,node_no_);
	
	return;
}

void Relation::printDot(ofstream &fout){
	sstream nodeName("node_");
	nodeName<<node_no_;

	fout<<nodeName.str()<<"[shape=diamond,"<<(weak_?"peripheries=2,":"")
		<<"label=\""<<name_<<"\"];"<<endl;

	for(size_t i=0; i<from_.size(); ++i)
		from_[i].printDot(fout, node_no_);

	for(size_t i=0; i<to_.size(); ++i)
		to_[i].printDot(fout, node_no_);

	return;
}

void Edge::printDot(ofstream &fout, int parent){
	sstream parName("node_");
	sstream nodeName("node_");

	parName<<parent;
	nodeName<<entTbl_.table_[ent_].node_no_;

	fout<<nodeName.str()<<"--"<<parName.str();
	if(weak_){
		if(complete_){
			if(!normal_){
				if(many_)
					fout<<"[style=dashed, penwidth=4, label=\"MANY\"];"<<endl;
				else
					fout<<"[style=dashed, penwidth=4, label=\"ONE\"];"<<endl;
			}
			else fout<<"[style=dashed, penwidth=4];"<<endl;
		}
		else fout<<"[style=dashed];"<<endl;
	}
	else fout<<";"<<endl;
	return;
}
		 

