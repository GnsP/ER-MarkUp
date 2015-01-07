
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
