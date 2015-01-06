#include "parser.hpp"
using namespace std;

int nodeCounter=1;

void Parser::generateCode(const char *outFileName){
	ofstream fout;
	fout.open(outFileName);

	fout<<"graph G{nodesep=2;ranksep=1;K=1.5;maxiter=10000;"
		<<"ordering=out;splines=false; label=\""<<diagram_.name_
		<<"\"; node[fontsize=14, fontname=\"Consolas\"];"<<endl
		<<"edge[fontsize=14, fontname=\"Consolas\"];"<<endl;
	
	for(map<string,Entity>::iterator it=entTbl_.table_.begin();
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

	fout<<nodeName.str()<<"[shape=box, label=\""<<name_<<"\""
		<<(weak_?",peripheries=2":"")<<"];"<<endl;

	for(size_t i=0; i<attr_.size(); ++i)
		attr_[i].printDot(fout,node_no_);

	return;
}

void Attribute::printDot(ofstream &fout, int parent){
	sstream nodeName("node_");
	sstream parName("node_");
	
	node_no_=nodeCounter++;
	nodeName<<node_no_;
	parName<<parent;

	bool underline = false;
	bool composite = false;
	fout<<nodeName.str()<<"[";
	for(size_t i=0; i<type_.size(); ++i){
		switch(type_[i]){
			case _MULTI:
				fout<<"peripheries=2,";
				break;
			case _COMPOSITE: 
				composite = true;
				break;
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

	if(composite)
		for(size_t i=0; i<attr_.size(); ++i)
			attr_[i].printDot(fout,node_no_);
	
	return;
}

void Relation::printDot(ofstream &fout){
	sstream nodeName("node_");
	nodeName<<node_no_;

	fout<<nodeName.str()<<"[shape=diamond,regular=1,"<<(weak_?"peripheries=2,":"")
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
	string n(ent_);
	nodeName<<entTbl_.table_[n].node_no_;

	fout<<nodeName.str()<<"--"<<parName.str();
	if(weak_){
		if(complete_){
			if(!normal_){
				if(many_)
					fout<<"[style=dashed, penwidth=4, label=\"N\"];"<<endl;
				else
					fout<<"[style=dashed, penwidth=4, label=\"1\"];"<<endl;
			}
			else fout<<"[style=dashed, penwidth=4];"<<endl;
		}
		else{// fout<<"[style=dashed];"<<endl;
			if(!normal_){
				if(many_)
					fout<<"[style=dashed,label=\"N\"];"<<endl;
				else
					fout<<"[style=dashed,label=\"1\"];"<<endl;
			}
			else fout<<"[style=dashed];"<<endl;
		}
	}
	else{
		if(complete_){
			if(!normal_){
				if(many_)
					fout<<"[penwidth=4, label=\"N\"];"<<endl;
				else
					fout<<"[penwidth=4, label=\"1\"];"<<endl;
			}
			else fout<<"[penwidth=4];"<<endl;
		}
		else{// fout<<";"<<endl;
			if(!normal_){
				if(many_)
					fout<<"[label=\"N\"];"<<endl;
				else
					fout<<"[label=\"1\"];"<<endl;
			}
			else fout<<";"<<endl;
		}
	}
	return;
}
		 

