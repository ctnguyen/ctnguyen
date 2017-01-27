#ifndef ABNORMAL_TRADE_H
#define ABNORMAL_TRADE_H

#include "AnalyticsAPI.hpp"

/**
 *  \class AbnormalTrade
 *
 *  \brief AbnormalTrade process trading price sequentially and trigger an alert when the price move is abnormal
 *
 */
class AbnormalTrade : public AnalyticsAPI
{
public:
        
    /// Process a single data element
    virtual void process(const double& crValue) const;



};


#endif /* ABNORMAL_TRADE_H */