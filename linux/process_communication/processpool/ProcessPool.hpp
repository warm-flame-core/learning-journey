#ifndef __PROCESSPOOL_HPP__
#define __PROCESSPOOL_HPP__

#include <iostream>
#include <string>
#include <vector>

// 先描述
class Channel
{
public:
    Channel()
    {
    }
    ~Channel()
    {
    }

private:
    int _wfd;
    std::string _name;
};

// 再组织
class ChannelManager
{
public:
    ChannelManager()
    {
    }
    ~ChannelManager()
    {
    }

private:
    std::vector<Channel> _channels;
};
class ProcessPool
{
public:
    ProcessPool()
    {
    }
    ~ProcessPool()
    {
    }

private:
    ChannelManager _cm;
    int _process_num;
};

#endif
