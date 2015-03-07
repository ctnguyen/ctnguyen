/*!
 * Helper.h
 */
#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

namespace helper
{
	typedef bool binop;              // 1 bit  binop
	typedef std::bitset<7>  opt;     // 7 bits operation
	typedef std::bitset<24> optdata; // 24 bits operational data

	// to change if machine dependance size of int
	typedef int Int32;

	inline Int32 convertHexStringToInt(const std::string& hexstr)
	{
		//http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
		std::stringstream ss ; ss << std::hex << hexstr;
		unsigned int unsigned_number ; ss >> unsigned_number;
		return static_cast<Int32>(unsigned_number);
	}

	inline std::string convertIntToHexString(const Int32& int_number)
	{
		std::stringstream ss; ss << std::hex << int_number;		
		return ss.str();
	}

	
	typedef std::bitset<32> Binary32;

	inline Int32 convertBinaryToInt(const Binary32& bin_number)
	{
		//http://stackoverflow.com/questions/27378163/convert-bitseta-to-signed-int-with-a32
		return static_cast<Int32>(bin_number.to_ulong());
	}

	inline Binary32 convertIntToBinary(const Int32& int_number)
	{
		Binary32 bin_number(int_number);
		return bin_number;
	}
}

#endif /* HELPER_H */
