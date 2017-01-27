#ifndef SYSTEM_API_H
#define SYSTEM_API_H

#include <string>
#include <vector>

/**
 *  \class SystemAPI
 *
 *  \brief Simulate a datafeeder
 *
 */

class SystemAPI
{
public:

    /// Load full data from csv file into mData //TO IMPLEMENT
    void init(const std::string& crCSVFilePath);

    /// Check if the datafeed is ended
    bool isEnd() const;

    /// Get the current data point
    double getCurrentValue() const;

private:

    /// Member data allowing to simulate the realtime feed
    mutable size_t mCurrentPos; //* question
    std::vector<double> mData;
    
};

#endif /* SYSTEM_API_H */