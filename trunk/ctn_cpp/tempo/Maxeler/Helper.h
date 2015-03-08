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
	typedef std::bitset<7>  Binary7;  // 7 bits operation
	typedef std::bitset<24> Binary24; // 24 bits operational data
	typedef std::bitset<32> Binary32; // 32 bits for integers

	struct Instruction
	{
		bool binop;
		Binary7 operation;
		Binary24 optdata;
	};

	// to change if machine dependance size of int
	typedef int Int32;

	inline Int32 convertHexStringToInt32(const std::string& hexstr)
	{
		//http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
		std::stringstream ss ; ss << std::hex << hexstr;
		unsigned int unsigned_number ; ss >> unsigned_number;
		return static_cast<Int32>(unsigned_number);
	}

	inline std::string convertInt32ToHexString(const Int32& int_number)
	{
		std::stringstream ss; ss << std::hex << int_number;		
		return ss.str();
	}
	
	inline Int32 convertBinary32ToInt32(const Binary32& bin_number)
	{
		//http://stackoverflow.com/questions/27378163/convert-bitseta-to-signed-int-with-a32
		return static_cast<Int32>(bin_number.to_ulong());
	}

	inline Binary32 convertInt32ToBinary32(const Int32& int_number)
	{
		Binary32 bin_number(int_number);
		return bin_number;
	}

	inline Int32 convertBinary7ToInt32(const Binary7& Binary7)
	{
		Binary32 bin32;
		for (size_t i = 0; i < 7; ++i) bin32[i] = Binary7[i];
		return convertBinary32ToInt32(bin32);
	}

	inline Int32 convertBinary24ToInt32(const Binary24& Binary24)
	{
		Binary32 bin32;
		for (size_t i = 0; i < 24; ++i) bin32[i] = Binary24[i];
		return convertBinary32ToInt32(bin32);
	}
	
	inline Instruction decode(const Int32& int32)
	{
		Instruction instruction;
		Binary32 binary32 = convertInt32ToBinary32(int32);
		for (size_t i = 0; i < 24; ++i){ instruction.optdata[i] = binary32[i]; }
		for (size_t i = 24; i < 31; ++i){ instruction.operation[i] = binary32[i]; }
		instruction.binop = binary32[31];
		return instruction;
	}
}

#endif /* HELPER_H */
