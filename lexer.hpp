
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


#ifndef ER_MARKUP_LEXER_HPP_
#define ER_MARKUP_LEXER_HPP_

#include "includes.hpp"
using namespace std;

enum TokenType { KEYWORD = 775, NAME, OPERATOR , _NONE};
enum Operator { LCURL = 1056, RCURL, SEMICOLON, HYPHEN, EQUAL , _ERROR};
enum KeyWord { 	ENT = 1123, WEAK, 
				ATTR, KEY, DERIVED, MULTI, COMPOSITE,
				RELN, ONE, MANY, FROM, TO, PARTIAL, COMPLETE, DIAGRAM,
				BEGIN, END, CONNECT, ERROR };

extern const char *KEYWORDS[18];

inline bool isKey(const char *str){
	for(int i=0; i<18; i++)
		if(strcmp(KEYWORDS[i],str)==0) return true;
	return false;
}

union TokenHolder{
	KeyWord kw_;
	Operator op_;
	char name_[100];
};

struct Token{
	TokenType type_;
	TokenHolder token_;

	Token(){}
	Token(TokenType type, const char *tok_str){
		makeToken(type,tok_str);
	}
	void makeToken(TokenType type, const char *tok_str);
};

class Tokenizer{
	public:
		Tokenizer(char *prog):prog_(prog){}
		
		inline bool next(Token &t){
			bool ret = getNextToken();
			DEBUG(cout<<token_<<endl;)
			if(ret) t.makeToken(type_,token_);
			return ret;
		}
		
		inline const char *getProgram(){
			return prog_;
		}

	private:
		char *prog_;
		char token_[100];
		TokenType type_;

		inline bool isOp(char ch){
			if(strchr("{};-=",ch)) return true;
			return false;
		}

		bool getNextToken();
};

#endif
