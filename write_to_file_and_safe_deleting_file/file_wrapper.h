#ifndef OPZKS_FILE_WRAPPER_H_
#define OPZKS_FILE_WRAPPER_H_

#include "headers.h"

namespace NFileWrapper
{
	typedef std::shared_ptr<std::ofstream> smart_ofstream;
	// for generate random bytes array
	using random_bytes_engine = std::independent_bits_engine<std::default_random_engine, CHAR_BIT, unsigned char>;

	// base class
	class FileWrapper
	{
	public:
		virtual ~FileWrapper() {}
		static const bool DeleteFile(const std::string path);
		static const bool DeleteDir(const std::string path);
	};

	class OutputFileWrapper : public FileWrapper
	{
	public:
		OutputFileWrapper() : output_(smart_ofstream()),
						file_path_(std::string()),
						num_of_erase_(0),
						type_run_(0)
						{}
		OutputFileWrapper(const std::string file_path
					, int num_of_erase = 0
					, int type_run = 0) :	output_(smart_ofstream(new std::ofstream(file_path, std::ios::binary | std::ios::trunc))),
											file_path_(file_path),
											num_of_erase_(num_of_erase),
											type_run_(type_run)
											{}
		const bool SafeFileNInsert();


		inline void close() {
			this->output_->close();
		}

		inline void open(const std::string path) {
			if (false == this->output_->is_open()) {
				this->output_->open(path, std::ios::binary | std::ios::trunc);
			}
		}

	private:
		smart_ofstream output_;
		std::string file_path_;
		int num_of_erase_;
		int type_run_;

		const bool RandInsert();
		const bool ZeroInsert();
	};
}

#endif // OPZKS_FILE_WRAPPER_H_