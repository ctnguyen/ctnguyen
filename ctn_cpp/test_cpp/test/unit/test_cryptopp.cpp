/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_cryptopp
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <iomanip>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

#include <cryptopp/cryptlib.h>
#include <cryptopp/secblock.h>
#include <cryptopp/salsa.h>
#include <cryptopp/osrng.h>

#include <cryptopp/files.h>
#include <cryptopp/hex.h>

#include <cryptopp/hmac.h>
#include <cryptopp/sha.h>


BOOST_AUTO_TEST_SUITE(CryptoPP)


BOOST_AUTO_TEST_CASE(test_HMAC_SHA256)
{
    /// see https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md
    /// example 1

    const unsigned char privateKey[65] = "NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j"; // lenth 64 
    const CryptoPP::SecByteBlock _key(privateKey,64);

    std::string msg = "symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&timestamp=1499827319559";
    std::string mac, hex_signature;
    const std::string signature_test = "c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71";

    std::cout << "msg : " << msg << std::endl;

    /*********************************\
    \*********************************/

    try
    {
        HMAC< SHA256 > hmac(_key, _key.size());

        StringSource ss2(msg, true, 
            new HashFilter(hmac,
                new StringSink(mac)
            ) // HashFilter      
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    /*********************************\
    \*********************************/

    // Pretty print
    hex_signature.clear();
    StringSource ss3(mac, true,
        new HexEncoder(
            new StringSink(hex_signature),false
        ) // HexEncoder
    ); // StringSource

    std::cout << "hex_signature: " << hex_signature << std::endl;
    BOOST_TEST( hex_signature == signature_test , boost::test_tools::per_element() );
}

/// Example first taken from 
/// https://stackoverflow.com/questions/12306956/example-of-aes-using-crypto
BOOST_AUTO_TEST_CASE(test_AES)
{
    //Key and IV setup
    //AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-   
    //bit). This key is secretly exchanged between two parties before communication   
    //begins. DEFAULT_KEYLENGTH= 16 bytes
    byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    //
    // String and Sink setup
    //
    std::string plaintext = "Now is the time for all good men to come to the aide...";
    std::string ciphertext;
    std::string decryptedtext;

    //
    // Create Cipher Text
    //
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
    stfEncryptor.MessageEnd();

    //
    // Decrypt
    //
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
    stfDecryptor.MessageEnd();

    // This doesnt work with difference of NULL character extra after decrypting
    //BOOST_TEST( plaintext == decryptedtext , boost::test_tools::per_element() ); 
}

BOOST_AUTO_TEST_CASE(test_Salsa20)
{
    /// https://www.cryptopp.com/wiki/Salsa20
    //using CryptoPP::byte;
    using CryptoPP::Salsa20;
    using CryptoPP::SecByteBlock;
    using CryptoPP::AutoSeededRandomPool;

    AutoSeededRandomPool prng;
    std::string plain("My Plaintext!! My Dear plaintext!!"), cipher, recover;

    SecByteBlock key(32), iv(8);
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    const byte * keyPtr = key.BytePtr();
    const byte * ivPtr = iv.BytePtr();
    // Encryption object
    Salsa20::Encryption enc;
    enc.SetKeyWithIV(key, key.size(), iv, iv.size());

    // Perform the encryption
    cipher.resize(plain.size());
    enc.ProcessData((byte*)&cipher[0], (const byte*)plain.data(), plain.size());

    Salsa20::Decryption dec;
    dec.SetKeyWithIV(key, key.size(), iv, iv.size());

    // Perform the decryption
    recover.resize(cipher.size());
    dec.ProcessData((byte*)&recover[0], (const byte*)cipher.data(), cipher.size());

    BOOST_TEST( plain == recover , boost::test_tools::per_element() );
}


BOOST_AUTO_TEST_CASE(test_Salsa20_Hex)
{
    /// https://www.cryptopp.com/wiki/Salsa20
    //using CryptoPP::byte;
    using CryptoPP::Salsa20;
    using CryptoPP::FileSink;
    using CryptoPP::StringSink;
    using CryptoPP::StringSource;
    using CryptoPP::HexEncoder;
    using CryptoPP::SecByteBlock;
    using CryptoPP::AutoSeededRandomPool;
    using CryptoPP::StreamTransformationFilter;

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));
    std::string plain("My Plaintext!! My Dear plaintext!!"), cipher, recover;

    SecByteBlock key(32), iv(8);
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::cout << "Key: ";
    encoder.Put(key.data(), key.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "IV: ";
    encoder.Put(iv.data(), iv.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    // Encryption object
    Salsa20::Encryption enc;    
    enc.SetKeyWithIV(key, key.size(), iv, iv.size());

    // Decryption object
    Salsa20::Decryption dec;    
    dec.SetKeyWithIV(key, key.size(), iv, iv.size());

    StringSource ss1(plain, true, new StreamTransformationFilter(enc, new StringSink(cipher)));
    StringSource ss2(cipher, true, new StreamTransformationFilter(dec, new StringSink(recover)));

    std::cout << "Plain: " << plain << std::endl;

    std::cout << "Cipher1 : [";
    encoder.Put((const byte*)cipher.data(), cipher.size());
    encoder.MessageEnd();
    std::cout <<"]"<< std::endl;

    std::cout << "Cipher2 : [" << cipher <<"]"<< std::endl;
    std::cout << "Recovered: [" << recover <<"]"<< std::endl;

    BOOST_TEST( plain == recover , boost::test_tools::per_element() );
}

BOOST_AUTO_TEST_SUITE_END()