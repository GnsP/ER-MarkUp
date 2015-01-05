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
