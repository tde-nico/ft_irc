#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#pragma once

#include "Client.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"


class Channel
{
    private:
            std::string                 nameChannel;
            std::string                 start_date;
            std::vector<Client *>       *users;    
            int                         currentFD;
            std::string                 hostname;
            std::string                 admin;

    public:
            Channel();
            std::string                 get_nameChannel(){return this->nameChannel;};
            std::string                 get_hostname(){return this->hostname;};
            std::vector<Client *>       *get_users(){return this->users;};
            std::string                 get_admin(){return this->admin;};
            int                         get_fd(){return this->currentFD;};
            std::string                 get_start_date(){return this->start_date;};
            
            void                        set_nameChannel(std::string str){this->nameChannel = str;};
            void                        set_start_date(std::string time){this->start_date = time;}; 
            void                        set_users(Client *new_user){this->users->push_back(new_user);};
            void                        set_currentFd(int fd){this->currentFD = fd;};
            void                        set_hostname(std::string str){this->hostname = str;};
            void                        set_admin(std::string str){this->admin = str;};
          //  void                        setNewChannel(Client *client, Channel *new_channel, std::string channel_name);
          //  void                        getwelcomeMessage();
          //  std::string		        get_time();
};




#endif