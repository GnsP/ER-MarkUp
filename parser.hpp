
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


#ifndef ER_MARKUP_PARSER_HPP_
#define ER_MARKUP_PARSER_HPP_

#include "includes.hpp"
#include "lexer.hpp"
#include "structure.hpp"
#include "symbolTable.hpp"

extern EntityTable entTbl_;

class Parser{
	public:
		Parser(char *prog):lex_(prog),prog_(prog){}
		
		void parse(){
			check = lex_.next(t);
			if(!check){
				error("Empty source file");
				return;
			}
			if(t.type_ == KEYWORD){
				if(t.token_.kw_ == DIAGRAM ){
					check = lex_.next(t);
					if(!check) error("Incomplete Description of ER Diagram");
					if(t.type_ == NAME){
						strcpy(diagram_.name_, t.token_.name_);
						check = lex_.next(t);
						if(!check) error("Incomplete Description of ER Diagram");
						if(t.type_ != OPERATOR && t.token_.op_ != SEMICOLON)
							error("Expected SEMICOLON at the end of statement");
					}
					else error("Invalid naming of the ER Diagram");
					check = lex_.next(t);
					if(!check)error("No entities or relationships described");
				}
				else{
					strcpy(diagram_.name_,"--UNNAMED--");
				}
			}
			else error("Invalid syntax");
			DEBUG(cout<<t.type_<<" "<<t.token_.kw_<<endl;)
			if(t.type_ == KEYWORD && t.token_.kw_ == BEGIN){
				check = lex_.next(t);
				if(!check)error("No description of the Diagram found");
				while(t.type_ == KEYWORD
				  && (t.token_.kw_ == ENT || t.token_.kw_ == RELN 
				  ||  t.token_.kw_ == END)){

					if(t.token_.kw_ == ENT) parseEnt();
					else if(t.token_.kw_ == RELN) parseReln();
					else if(t.token_.kw_ == END) break;
					else error("Invalid syntax");

					check = lex_.next(t);
					if(!check) error("expected END here");
				}
			}
			else error("expected BEGIN here");
		}

		void generateCode(const char *outFileName);

	private:
		Tokenizer lex_;
		ER_Diagram diagram_;
		//EntityTable entTbl_;
		char *prog_;

		Token t;
		bool check;

		void parseEnt();
		void parseEntAttr(Entity &ent);
		void parseAttr(Attribute &a);
		void parseAttrAttr(Attribute &a);

		void parseReln();
		void parseEdges(Relation &rel, bool from);
		void parseEdge(Edge &ed);
};

#endif
