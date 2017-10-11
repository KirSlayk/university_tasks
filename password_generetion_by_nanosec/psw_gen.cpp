#include "psw_gen.h"

namespace NPswGen
{
	const std::string PswGen::Gen() const {
		// our new password in finish
		std::string psw = "";
		for (int i = 0; i < this->length_; ++i) {
			// get regular byte for our password
			auto c_char = this->get_new_byte();
			// check byte (A-Za-z0-9)
			if (false == isalpha(c_char) &&
				false == isdigit(c_char)) {
				--i;
				continue;
			}
			// add new byte to password
			psw += c_char;
		}
		return psw;
	}

	const char PswGen::get_new_byte() const {
		char c_char = 0;
		for (size_t i = 0; i < 8; ++i) {
			// std::chrono::high_resolution_clock:nanoseconds
			auto c_time = nano_time::now();
			// convert std::nanoseconds to integer
			auto nano_s = std::chrono::duration_cast<std::chrono::nanoseconds>(c_time.time_since_epoch()).count();
			// sleep for more randomize password
			std::this_thread::sleep_for(std::chrono::nanoseconds(rand() % 7 + 1));
			// add bit to out byte
			c_char |= ((nano_s & 0x0001) << i);
		}
		return c_char;
	}
}