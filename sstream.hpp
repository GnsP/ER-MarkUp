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
