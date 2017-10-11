/*
    C++11, OPZKS1.cpp
    Purpose: 	write to file rand data n times;
				delete file;

    @author Kirill Slaykovskiy ИУ8-91
    @version 1.0 14/09/17 
*/

#include "headers.h"
#include "file_wrapper.h"

// help function for info
void help(){
	using std::cout; 
	using std::endl;
	cout<<"OPTIONS"<<endl;
	cout<<"\tMUST BE:"<<endl;
	cout<<"\t\t-f"<<endl;
	cout<<"\t\t\tFilepath to input file or dir (absolute or relative)"<<endl;
	cout<<"\t\t-c"<<endl;
	cout<<"\t\t\tNumber of erasures (DEFAULT VALUE = 0)"<<endl;
	cout<<"\t\t-t"<<endl;
	cout<<"\t\t\tType run: zero-type (0) or random-type (1) (DEFAULT VALUE = 0)"<<endl;
	cout<<endl;
	cout<<"\tEXAMPLE:"<<endl;
	cout<<"\t\t./program -f \'filepath\' -c \'some_number\' -t \'1\'"<<endl;
	exit(1);
}


int main(int argc, char *argv[]) {
	// flag for getopt function
	// num_of_erase is circles count
	// type_run can be 0 (zero-type) or 1 (rand-type)
	int flag = 0,
	 	num_of_erase = 0;
	unsigned int type_run = 0;

	std::string file_path = "";

	while (-1 != (flag = getopt(argc,argv,"f:c:t:?"))){
		switch (flag){
			case 'f': file_path = optarg; break;
			case 'c': num_of_erase = atoi(optarg); break;
			case 't': type_run = atoi(optarg); break;
			case '?': help(); break;
        }
	}
	// check type_run
	if (0 != type_run && 
		1 != type_run) {
		type_run = 0;
	}
	std::string type_run_str = 0 == type_run ? "zero-type" : "rand-type";
	std::cout<<"file_path = "<<file_path<<"\ncircles = "<<num_of_erase<<"\ntype_run = "<<type_run_str<<std::endl;
	
	// check file_path (exist or not)
	struct stat buffer;   
	if (0 != stat(file_path.c_str(), &buffer) &&
		0 == S_ISDIR(buffer.st_mode)) {
		perror("Error");
		help();
	}

	// file_path is path to dir or not
	auto is_dir = S_ISDIR(buffer.st_mode);
	// if file_path is path to file
	if (false == is_dir) {
		auto output = std::make_shared<NFileWrapper::OutputFileWrapper>(file_path, num_of_erase, type_run);
		// insert n times some info to file
		output->SafeFileNInsert();
		// safe delete file
		NFileWrapper::FileWrapper::DeleteFile(file_path);
	}
	else {
		// safe delete dir and embeds
		NFileWrapper::FileWrapper::DeleteDir(file_path);
	}
	return 0;
}