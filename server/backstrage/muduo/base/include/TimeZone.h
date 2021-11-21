#ifndef MUDUO_BASE_TIMEZONE_H
#define MUDUO_BASE_TIMEZONE_H

#include "copyable.h"
#include <memory>
#include <time.h>

namespace muduo
{
    
class TimeZone : public muduo::copyable
{

public:
    explicit TimeZone(const char* zonefile);
    TimeZone(/* args */)=default;
    TimeZone(int eastOfUtc,const char* tzname);
    bool vaild() const
    {
        return static_cast<bool>(data_);
    }

    struct tm toLocalTime(time_t secondsSinceEpoch) const;
    time_t fromLocalTime(const struct tm&) const;

    static struct tm toUtcTime(time_t secondsSinceEpoch,bool yday = false);

    static time_t fromUtcTime(const struct tm&);

    static time_t fromUtcTime(int year,int month,int day,int hour,int minute,int seconds);

    struct Data;

private:
    std::shared_ptr<Data> data_;
    
};



} // namespace muduo


#endif