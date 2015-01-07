#include "parser.hpp"
using namespace std;

bool isAttrTag(KeyWord k){
	return  k==MULTI || k==KEY || k==DERIVED || k==COMPOSITE;
}

bool isRelnTag(KeyWord k){
	return k==PARTIAL || k==COMPLETE || k==ONE || k==MANY || k==WEAK;
}


void Parser::parseEnt(){
	Entity ent_;
	
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(t.type_==NAME)strcpy(ent_.name_, t.token_.name_);
	else error("Invalid naming of the Entity");

	
	if(entTbl_.table_.count(ent_.name_)!=0)
	error("entity with same name already defined");
	
	ent_.weak_ = false;
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(t.type_== KEYWORD && t.token_.kw_ == WEAK ){
		ent_.weak_ = true;
		check = lex_.next(t);
		if(!check) error("incomplete description of ER Diagram");
	}

	if(t.type_ == OPERATOR && t.token_.op_ == LCURL){
		parseEntAttr(ent_);
	}
	else if(t.type_ == OPERATOR && t.token_.op_ == SEMICOLON);
	else error("expected SEMICOLON(;) or a list of Attributes");

	entTbl_.insert(ent_.name_, ent_);
//	entTbl_.table_.insert(make_pair<const char*, Entity>(ent_.name_, ent_));
	DEBUG(cout<<"DEBUG::"<<ent_.name_<<" inserted"<<endl;)
	return;
}
	
void Parser::parseEntAttr(Entity &ent){
	Attribute a;
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");

	if(t.type_==KEYWORD && t.token_.kw_==ATTR){
		while(t.type_==KEYWORD && t.token_.kw_==ATTR){
			parseAttr(a);
			ent.attr_.push_back(a);
			a.destruct();
			check = lex_.next(t);
			if(!check) error("incomplete description of ER Diagram");
		}
		if(t.type_==OPERATOR && t.token_.op_==RCURL) return;
		else error("expected RCURL(}) here");
	}
	else if(t.type_==OPERATOR && t.token_.op_==RCURL) return;
	else error("expected RCURL(}) or a list of Attributes");

	return;
}

void Parser::parseAttr(Attribute &a){
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	
	if(t.type_==NAME) strcpy(a.name_, t.token_.name_);
	else error("Invalid naming of attribute");

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");

	bool composite = false;
	if(t.type_==KEYWORD && isAttrTag(t.token_.kw_)){
		while(t.type_==KEYWORD && isAttrTag(t.token_.kw_)){
			switch(t.token_.kw_){
				case MULTI:
					a.type_.push_back(_MULTI);
					break;
				case KEY:
					a.type_.push_back(_KEY);
					break;
				case DERIVED:
					a.type_.push_back(_DERIVED);
					break;
				case COMPOSITE:
					composite=true;
					a.type_.push_back(_COMPOSITE);
					break;
				default: break;
			}
			check = lex_.next(t);
			if(!check) error("incomplete description of ER Diagram");
		}
		if(composite){
			if(t.type_==OPERATOR && t.token_.op_==LCURL) parseAttrAttr(a);
			else error("expected list of Attributes for composite Attribute");
		}
		else if(t.type_==OPERATOR && t.token_.op_==SEMICOLON) return;
		else error("expected SEMICOLON(;) here");
	}
	else if(t.type_==OPERATOR && t.token_.op_==SEMICOLON) return;
	else error("expected SEMICOLON(;) or a list of Attribute tags");

	return;
}

void Parser::parseAttrAttr(Attribute &ent){
	Attribute a;
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");

	if(t.type_==KEYWORD && t.token_.kw_==ATTR){
		while(t.type_==KEYWORD && t.token_.kw_==ATTR){
			parseAttr(a);
			ent.attr_.push_back(a);
			a.destruct();
			check = lex_.next(t);
			if(!check) error("incomplete description of ER Diagram");
		}
		if(t.type_==OPERATOR && t.token_.op_==RCURL) return;
		else error("expected RCURL(}) here");
	}
	else if(t.type_==OPERATOR && t.token_.op_==RCURL) return;
	else error("expected RCURL(}) or a list of Attributes");

	return;
}

void Parser::parseReln(){
	Relation rel;

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(t.type_==NAME) strcpy(rel.name_, t.token_.name_);
	else error("Invalid naming of Relationship");

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(t.type_==KEYWORD && t.token_.kw_==WEAK){
		rel.weak_=true;
		check = lex_.next(t);
		if(!check) error("incomplete description of ER Diagram");
	}

	if(!(t.type_==KEYWORD && t.token_.kw_==FROM))
		error("expect keyword FROM here");
	
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(!(t.type_==OPERATOR && t.token_.op_==LCURL))
		error("expected LCURL({) here");

	parseEdges(rel, true);

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(!(t.type_==KEYWORD && t.token_.kw_==TO))
		error("expect keyword FROM here");
	
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(!(t.type_==OPERATOR && t.token_.op_==LCURL))
		error("expected LCURL({) here");
	
	parseEdges(rel, false);
	
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	if(!(t.type_==OPERATOR && t.token_.op_==SEMICOLON))
		error("expected SEMICOLON(;) here");

	diagram_.graph_.push_back(rel);
	return;
}

void Parser::parseEdges(Relation &rel, bool from){	
	Edge ed;

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");

	if(t.type_==KEYWORD && t.token_.kw_==CONNECT){
		while(t.type_==KEYWORD && t.token_.kw_==CONNECT){
			parseEdge(ed);
			if(from) rel.from_.push_back(ed);
			else rel.to_.push_back(ed);

			check = lex_.next(t);
			if(!check) error("incomplete description of ER Diagram");
		}
		if(t.type_==OPERATOR && t.token_.op_==RCURL) return;
		else error("expected RCURL(}) here");
	}
	else error("at least one connection required here");
	return;
}

void Parser::parseEdge(Edge &ed){
	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");
	
	if(t.type_==NAME) strcpy(ed.ent_, t.token_.name_);
	else error("Invalid name");

	check = lex_.next(t);
	if(!check) error("incomplete description of ER Diagram");

	ed.normal_=true;
	ed.weak_=false;
	ed.complete_=false;
	ed.many_=false;

	if(t.type_==KEYWORD && isRelnTag(t.token_.kw_)){
		while(t.type_==KEYWORD && isRelnTag(t.token_.kw_)){
			switch(t.token_.kw_){
				case WEAK:
					ed.weak_=true;
					break;
				case PARTIAL:
					ed.complete_=false;
					break;
				case COMPLETE:
					ed.complete_=true;
					break;
				case ONE:
					ed.normal_=false;
					ed.many_=false;
					break;
				case MANY:
					ed.normal_=false;
					ed.many_=true;
					break;
				default: break;
			}
			check = lex_.next(t);
			if(!check) error("incomplete description of ER Diagram");
		}
		if(t.type_==OPERATOR && t.token_.op_==SEMICOLON) return;
		else error("expected SEMICOLON(;) here");
	}
	else if(t.type_==OPERATOR && t.token_.op_==SEMICOLON) return;
	else error("expected SEMICOLON(;) or a list of Attribute tags");

	return;
}

