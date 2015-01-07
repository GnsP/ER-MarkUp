
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


#ifndef I_SSTREAM_HPP_
#define I_SSTREAM_HPP_

class sstream{
	public:
		char str_[20];
		sstream(const char *s){
			strcpy(str_,s);
		}
		void operator<<(int x){
			int pos=strlen(str_);
			while(x){
				str_[pos]='0'+x%10;
				x/=10;
				pos++;
			}
			str_[pos]='\0';
		}
		char *str(){
			return str_;
		}
};
#endif
