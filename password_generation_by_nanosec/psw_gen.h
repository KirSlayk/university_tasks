#ifndef OPZKS2_PSWGEN_H_
#define OPZKS2_PSWGEN_H_

#include "headers.h"

namespace NPswGen
{
	typedef std::chrono::high_resolution_clock nano_time;
	static const int default_length = 16;
	class PswGen
	{
	public:
		PswGen() : 	length_(0)
					{}
		PswGen(unsigned int length) :	length_(length)
										{}
		// function for generation password
		const std::string Gen() const;
	private:
		// function for generation regular byte
		const char get_new_byte() const;
		unsigned int length_;
	};
}

#endif // OPZKS2_PSWGEN_H_