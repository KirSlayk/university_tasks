#include "file_wrapper.h"

namespace NFileWrapper
{
	const bool OutputFileWrapper::SafeFileNInsert() {
		// insert n times
		for (int i = 0; i < this->num_of_erase_; ++i) {
			// open file if it was not opened
			this->open(this->file_path_);
			// check insert type and call function
			auto bool_res = 0 == this->type_run_ ? this->ZeroInsert() : this->RandInsert();
			// if insert function faild -> notification
			if (false == bool_res) {
				perror("Error insert data to file");
			}
			// disk reset
			this->close();
		}
		return true;
	}

	const bool OutputFileWrapper::RandInsert() {
		try {
			random_bytes_engine rbe;
	   		std::vector<char> data(1000);
	    	// generate random array with length 1000
	    	std::generate(begin(data), end(data), std::ref(rbe));
			// print data to file
			this->output_->write(&data[0], data.size());
			std::cout<<"Rand insert is success"<<std::endl;
		}
		catch (...) {
			perror("Error: RandInsert function faild");
			return false;
		}
		return true;
	}

	const bool OutputFileWrapper::ZeroInsert() {
		try {
	   		// create array with zero values
	   		std::vector<char> data(1000);
			// print data to file
			this->output_->write(&data[0], data.size());
			std::cout<<"Zero insert is success"<<std::endl;
		}
		catch (...) {
			perror("Error: ZeroInsert function faild");
			return false;
		}
		return true;
	}

	const bool FileWrapper::DeleteFile(const std::string path) {
		// check file_path on exist
		struct stat buffer;   
		if (0 == stat(path.c_str(), &buffer)) {
			// if path is exist -> remove it
			if (0 != remove(&path[0])) {
				perror("Error deleting file");
				return false;
			}
			else {
				std::cout<<"File with path "<<path<<" was removed"<<std::endl;
			}
		}
		else {
			perror("DeleteFile not such file");
			return false;
		}
		return true;
	}
	
	const bool FileWrapper::DeleteDir(const std::string path) {
		struct stat buffer; 
		// check file_path on exist
		stat(path.c_str(), &buffer);
		// if path is path to dir
		if (0 != S_ISDIR(buffer.st_mode)) {
			const char *command = &("rm -rf " + path)[0];
			// safe remove dir end embeds 
			system(command);
			std::cout<<"Dir with path "<<path<<" was removed"<<std::endl;
		}
		else {
			perror("DeleteDir not such dir");
			return false;
		}
		return true;
	}

}