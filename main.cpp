
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

int main(int argc, char *argv[]){
	streampos size;
	char *program;

	if(argc !=3){
		cout<<"Usage : erdcc <source file name> <out file name>"<<endl;
	}

	ifstream file (argv[1], ios::in|ios::ate);
	if (file.is_open()){
		size = file.tellg();
		program = new char [size];
		file.seekg (0, ios::beg);
		file.read (program, size);
		file.close();
		
		Parser compiler(program);
		compiler.parse();
		compiler.generateCode(argv[2]);

		delete [] program;
	}
	else cout << "Unable to open source file"<<endl;
	return 0;
}
