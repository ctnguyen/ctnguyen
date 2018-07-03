/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/

#include <boost/program_options.hpp>
//#include <boost/format.hpp>
#include <iostream>
#include <string>

#include <tgbot/tgbot.h>

namespace po = boost::program_options;
using namespace TgBot;

int main(int argc, char *argv[]) 
{
    std::string tokenStr;
    std::string messageStr;
    std::string botNameStr;
    
    po::options_description desc("Test telegram bot options");
    desc.add_options()
        ("help,h"  , "produce help message")
        ("token,t" ,po::value<std::string>(&tokenStr), "Token of the bot")
        ("message,m", po::value<std::string>(&messageStr), "Message to test")
        ;

    if(argc<2)
    {
        std::cout << desc << std::endl;
        return 1;
    }

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) /// Do not execute program if user request help option
    {
        std::cout << desc << std::endl;
        return 1;
    }
    
    
    const std::string logStr = (boost::format("Token [%1%] Message [%2%]") % tokenStr % messageStr ).str();
    std::cout<< logStr<<std::endl;

    
    TgBot::Bot bot(tokenStr);
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi! from C++");
    });

    
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    
    return 0;
}
