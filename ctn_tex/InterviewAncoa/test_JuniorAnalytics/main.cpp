#include <iostream>
#include "SystemAPI.hpp"
#include "AnalyticsAPI.hpp"
#include "AbnormalTrade.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        std::cout<< "Please give the full path to data file "<<std::endl;
        std::cout <<argv[0] <<" full/path/to/my/Data.csv" <<std::endl;
        return 1;
    }

    /// Get data file path from the first argument
    const std::string dataFilePath(argv[1]);

    /// Simulation of data
    SystemAPI simu;
    simu.init(dataFilePath);

    AnalyticsAPI* pAnalytics = new AbnormalTrade();
    while(!simu.isEnd())
    {
        double currentValue = simu.getCurrentValue();//* question?

        pAnalytics->process(currentValue);
    }
    return 0;
}