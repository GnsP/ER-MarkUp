#include "lexer.hpp"
using namespace std;

Operator strToOp(const char *str){
	switch(str[0]){
		case '{': return LCURL;
		case '}': return RCURL;
		case ';': return SEMICOLON;
		case '-': return HYPHEN;
		case '=': return EQUAL;
		default:  return _ERROR;
	}
}

KeyWord strToKey(const char *str){
	for(int i=0; i<18; i++)
		if(strcmp(KEYWORDS[i],str)==0) return ENT+(KeyWord)i;
	return ERROR;
}
/*	if(strcmp(str,"ENT") == 0) return ENT;
	else if(strcmp(str, "ATTR")) return ATTR;
	else if(strcmp(str, "WEAK")) return WEAK;
	else if(strcmp(str, "MULTI")) return MULTI;
	else if(strcmp(str, "COMPOSITE")) return COMPOSITE;
	else if(strcmp(str, "KEY")) return KEY;
	else if(strcmp(str, "DERIVED")) return DERIVED;
	else if(strcmp(str, "RELN")) return RELN;
	else if(strcmp(str, "ONE")) return ONE;
	else if(strcmp(str, "MANY")) return MANY;
	else return ERROR;
}*/

void Token::makeToken(TokenType type, const char *str){
	type_ = type;
	switch(type_){
		case KEYWORD:
			token_.kw_ = strToKey(str);
			break;
		case NAME:
			strcpy(token_.name_, str);
			break;
		case OPERATOR:
			token_.op_ = strToOp(str);
			break;
		default:
			error("Token does not match any known type");
			break;
	}
	return;
}

inline void readChar(char* &tmp, char* &prog, bool read=true){
	if(*prog == '\n' || *prog == '\r'){
		line_no++;
		col_no = 0;
		if(*prog == '\r') prog++;
	}
	else col_no++;
	if(read)*tmp++ = *prog++;
	else prog++;
}

bool Tokenizer::getNextToken(){
	char *temp;
	temp = token_;
	type_ = _NONE;
	*temp = '\0';

	if(!*prog_) return false;
	while(isspace(*prog_)) readChar(temp, prog_, false);

	if(*prog_ == '#'){
		while(*prog_ != '\n') readChar(temp, prog_, false);
		readChar(temp, prog_, false);
	}
	else if(isOp(*prog_)){
		readChar(temp, prog_);
		type_ = OPERATOR;
	}
	else if(*prog_ == '\"'){
		readChar(temp, prog_, false);
		while(*prog_ != '\"') readChar(temp, prog_);
		readChar(temp, prog_, false);
		type_ = NAME;
	}
	else if(isalpha(*prog_)){
		while(isalpha(*prog_)||*prog_=='_')
			readChar(temp, prog_);
		if(isKey(token_)) type_ = KEYWORD;
		else type_ = NAME;
	}
	else{
		error("type of the token could not be resolved");
		return false;
	}
	*temp = '\0';
	return true;
}
