/*
    C++11, OPZKS2.cpp
    Purpose: 	gen rand password;

    @author Kirill Slaykovskiy ИУ8-91
    @version 1.0 14/09/17 
*/
#include "headers.h"
#include "psw_gen.h"

// help function for info
void help(){
	using std::cout; 
	using std::endl;
	cout<<"OPTIONS"<<endl;
	cout<<"\tMUST BE:"<<endl;
	cout<<"\t\t-l"<<endl;
	cout<<"\t\t\tpassword length (DEFAULT VALUE = "<<NPswGen::default_length<<")"<<endl;
	cout<<endl;
	cout<<"\tEXAMPLE:"<<endl;
	cout<<"\t\t./program -l \'13\'"<<endl;
	exit(1);
}


int main(int argc, char *argv[]) {
	// flag for getopt function
	int flag = 0,
		psw_len = NPswGen::default_length;

	while (-1 != (flag = getopt(argc,argv,"l:?"))){
		switch (flag){
			case 'l': psw_len = atoi(optarg); break;
			case '?': help(); break;
        }
	}
	// length of password must be > 0
	if (psw_len <= 0) {
		std::cout<<"Error: password length must be > 0"<<std::endl;;
		exit(1);
	}
	std::cout<<"start generate password with length = "<<psw_len<<std::endl;
	// create object worker for generate password
	auto psw_gen_worker = std::make_shared<NPswGen::PswGen>(psw_len);
	// generate password
	auto psw_str = psw_gen_worker->Gen();
	// print password
	std::cout<<"new password = "<<psw_str<<std::endl;
	return 0;
}