#include "parser.hpp"
using namespace std;

const char *KEYWORDS[18]={"ENT", "WEAK", "ATTR", "KEY", "DERIVED", "MULTI", 
						"COMPOSITE", "RELN", "ONE", "MANY", "FROM", "TO",
						"PARTIAL", "TOTAL", "DIAGRAM",
						"BEGIN", "END", "CONNECT" }; 	// TOTAL is the string
														// for keyword COMPLETE

EntityTable entTbl_;
int line_no = 0;
int col_no = 0;
void error(const char *msg){
	cout<<"ERROR at ("<<line_no<<","<<col_no<<") : "<<msg<<endl;
	exit(0);
}