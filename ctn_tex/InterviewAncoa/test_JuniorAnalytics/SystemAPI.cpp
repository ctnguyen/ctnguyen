#include <fstream>
#include <sstream>
#include <string>
#include "SystemAPI.hpp"

void SystemAPI::init(const std::string& crCSVFilePath)
{
    mCurrentPos=0;
    /// To reimplement
    std::ifstream fileStream;
    fileStream.open(crCSVFilePath);
    
    std::string line;
    while(std::getline(fileStream,line))
    {
        std::istringstream strStream(line);
        double x;
        strStream>>x;
        mData.push_back(x);
    }

    fileStream.close();
}

bool SystemAPI::isEnd() const
{
    return (mCurrentPos>=mData.size());
}

double SystemAPI::getCurrentValue() const
{   
    return mData[mCurrentPos++];//* question
}
