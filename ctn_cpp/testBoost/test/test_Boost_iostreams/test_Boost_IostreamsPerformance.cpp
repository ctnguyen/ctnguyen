#define BOOST_TEST_MODULE test_Iostreams_Performance
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <cstddef> // NULL
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <boost/mpl/list.hpp>

BOOST_AUTO_TEST_SUITE(All_Types)

/// handle file name, size
struct FileConfig
{
    /// Initialize file name, and full path
    FileConfig(const std::string& crFileName="testFile.d", const size_t page_size=4000000)
    : mPageSize(page_size)
    , mNbPages(10)
    , mFileName(getFullPath(crFileName))
    {

    };

    const size_t mPageSize;// number of bytes per page
    size_t mNbPages;
    std::string mFileName;
    
    std::string getFullPath(const std::string& crFileName)
    {
        return crFileName;
    }
};

BOOST_FIXTURE_TEST_CASE(test_creatation_data_file, FileConfig)
{
    std::ofstream  myfile;
    myfile = std::ofstream (mFileName, std::ios::out | std::ios::binary);
    
    const clock_t beginTimePoint = clock();
    for(size_t iPage=0;iPage<mNbPages;++iPage)
    {
        for(size_t iByte=0;iByte<mPageSize;++iByte)
        {
            const char singleChar = 'z';
            myfile.write(&singleChar,1);
        }
    }
    const clock_t endTimePoint = clock(); double elapsed_secs = double(endTimePoint - beginTimePoint) / CLOCKS_PER_SEC;

    std::ostringstream msgLogStream; msgLogStream << "["<<mNbPages<<"] Pages of Size[" << mPageSize << "]  total length : " << mNbPages*mPageSize<< " bytes.  Elapsed Time "<< elapsed_secs<<"(s)";
    const std::string msgLog = msgLogStream.str();

    BOOST_TEST_MESSAGE(msgLog);
}

/// test trivial reading file pages
/// to see reading of first page does it take less time than reading last page
BOOST_AUTO_TEST_CASE(test_trivial_reading_file_pages)
{

}

/// Compare memory mapped file read/write compared to trivial read write
BOOST_AUTO_TEST_CASE(test_mmap_file_read_write)
{

}

BOOST_AUTO_TEST_SUITE_END()