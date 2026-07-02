#include "TimeTool.h"
#include <ctime>
#include <cstdio>

long long TimeTool::charArrayToLongLong(char number[])
{
    if (number == nullptr || number[0] == '\0')
        return 0;
    long long result = 0;
    for (int i = 0; number[i] != '\0'; i++)
    {
        if (number[i] < '0' || number[i] > '9')
            return 0;
        int digit = number[i] - '0';
        result = result * 10 + digit;
    }
    return result;
}

void TimeTool::generateTimeStamp(char result[])
{
    time_t nowTime = time(nullptr);
    std::sprintf(result, "%lld", (long long)nowTime);
}

void TimeTool::getCurrentTime(char now[])
{
    time_t nowStampTime = time(nullptr);
    tm *nowTime = localtime(&nowStampTime);

    std::sprintf(now,
                 "%04d-%02d-%02d %02d:%02d",
                 nowTime->tm_year + 1900,
                 nowTime->tm_mon + 1,
                 nowTime->tm_mday,
                 nowTime->tm_hour,
                 nowTime->tm_min);
}

double TimeTool::calculateHours(char start[], char end[])
{
    long long startStamp = charArrayToLongLong(start);
    long long endStamp = charArrayToLongLong(end);
    return double(endStamp - startStamp) / 3600.0;
}

bool TimeTool::isBeforeOneHour(char now[], char start[])
{
    long long startStamp = charArrayToLongLong(now);
    long long endStamp = charArrayToLongLong(start);
    return (double(endStamp - startStamp) / 3600.0) > 1.0;
}

bool TimeTool::isEndAfterStart(char start[], char end[])
{
    return charArrayToLongLong(end) >= charArrayToLongLong(start);
}

bool TimeTool::checkTimeFormat(char time[])
{
    // 格式检查
    if (time == nullptr)
        return false;
    for (int i = 0; i < 16; i++)
        if (time[i] == '\0')
            return false;
    if (time[16] != '\0')
        return false;
    if (time[4] != '-' || time[7] != '-' || time[10] != ' ' || time[13] != ':')
        return false;
    for (int i = 0; i < 16; i++)
    {
        if (i == 4 || i == 7 || i == 10 || i == 13)
            continue;
        if (time[i] < '0' || time[i] > '9')
            return false;
    }
    // 时间是否严格合法
    int year = (time[0] - '0') * 1000 + (time[1] - '0') * 100 + (time[2] - '0') * 10 + (time[3] - '0');
    int month = (time[5] - '0') * 10 + (time[6] - '0');
    int day = (time[8] - '0') * 10 + (time[9] - '0');
    int hour = (time[11] - '0') * 10 + (time[12] - '0');
    int minute = (time[14] - '0') * 10 + (time[15] - '0');
    if (month < 1 || month > 12 || day < 1 || hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return false;
    // 还原成时间戳判断时间戳是否合法，同时检查转换后的年月日时分是否仍然等于原输入
    tm checkTime = {};
    checkTime.tm_year = year - 1900;
    checkTime.tm_mon = month - 1;
    checkTime.tm_mday = day;
    checkTime.tm_hour = hour;
    checkTime.tm_min = minute;
    checkTime.tm_sec = 0;
    checkTime.tm_isdst = -1;
    if (mktime(&checkTime) == (time_t)-1)
        return false;
    return checkTime.tm_year == year - 1900 &&
           checkTime.tm_mon == month - 1 &&
           checkTime.tm_mday == day &&
           checkTime.tm_hour == hour &&
           checkTime.tm_min == minute;
}

void TimeTool::standardToStamp(char destination[], char resource[])
{
    if (destination == nullptr)
        return;
    if (!checkTimeFormat(resource))
    {
        destination[0] = '\0';
        return;
    }
    int year = (resource[0] - '0') * 1000 + (resource[1] - '0') * 100 + (resource[2] - '0') * 10 + (resource[3] - '0');
    int month = (resource[5] - '0') * 10 + (resource[6] - '0');
    int day = (resource[8] - '0') * 10 + (resource[9] - '0');
    int hour = (resource[11] - '0') * 10 + (resource[12] - '0');
    int minute = (resource[14] - '0') * 10 + (resource[15] - '0');

    tm standardTime = {};
    standardTime.tm_year = year - 1900;
    standardTime.tm_mon = month - 1;
    standardTime.tm_mday = day;
    standardTime.tm_hour = hour;
    standardTime.tm_min = minute;
    standardTime.tm_sec = 0;
    standardTime.tm_isdst = -1;

    time_t stamp = mktime(&standardTime);
    std::sprintf(destination, "%lld", (long long)stamp);
}
