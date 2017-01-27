#ifndef ANALYTICS_API
#define ANALYTICS_API

#include <string>
#include <vector>

/**
 *  \class AnalyticsAPI
 *
 *  \brief Process the message and trigger an alert
 *
 */

class AnalyticsAPI
{
public:
    
    /// Process a single data element
    virtual void process(const double& crValue) const = 0;
};

#endif /* ANALYTICS_API */