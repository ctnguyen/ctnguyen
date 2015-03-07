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
	
	int convertHexStringToInt(const std::string& hexstr)
	{
		//http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
		std::stringstream ss ; ss << std::hex << hexstr;
		unsigned int unsigned_number ; ss >> unsigned_number;
		return static_cast<int>(unsigned_number);
	}

	std::string convertIntToHexString(const int& int_number)
	{
		std::stringstream ss; ss << std::hex << int_number;		
		return ss.str();
	}

	
	typedef std::bitset<32> Binary32;

	int convertBinaryToInt(const Binary32& bin_number)
	{
		//http://stackoverflow.com/questions/27378163/convert-bitseta-to-signed-int-with-a32
		return static_cast<int>(bin_number.to_ulong());
	}

	Binary32 convertIntToBinary(const int& int_number)
	{
		Binary32 bin_number(int_number);
		return bin_number;
	}
}

#endif /* HELPER_H */
