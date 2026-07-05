#include "Reservation.h"
#include "Validator.h"
#include "TimeTool.h"
#include <iostream>
#include <cstring>
#include <ctime>

Reservation::Reservation()
{
    std::memset(reservationId, 0, sizeof(reservationId));
    std::memset(spaceId, 0, sizeof(spaceId));
    std::memset(ownerName, 0, sizeof(ownerName));
    std::memset(plateNumber, 0, sizeof(plateNumber));
    std::memset(phone, 0, sizeof(phone));
    std::memset(startTime, 0, sizeof(startTime));
    std::memset(endTime, 0, sizeof(endTime));
    std::memset(status, 0, sizeof(status));
    std::memset(actualInTime, 0, sizeof(actualInTime));
    TimeTool::generateTimeStamp(reservationId);
}

void Reservation::input()
{
    std::cout << "请输入车主姓名：";
    safeInput(this->ownerName, 20);

    std::cout << "请输入车牌号(字母请大写，不要添加空格，新能源车主正常填写完整车牌)：";
    safeInput(this->plateNumber, 20);
    while (!Validator::checkPlateNumber(this->plateNumber))
    {
        std::cout << "输入车牌号有误，请重新输入：";
        safeInput(this->plateNumber, 20);
    }

    std::cout << "请输入手机号：";
    safeInput(this->phone, 20);
    while (!Validator::checkPhone(this->phone))
    {
        std::cout << "输入手机号有误，请重新输入：";
        safeInput(this->phone, 20);
    }

    char time[20];
    std::cout << "请输入预约开始时间(格式为YYYY-MM-DD HH:MM)：";
    safeInput(time, 20);
    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);
    TimeTool::standardToStamp(this->startTime, time);

    while ((!TimeTool::checkTimeFormat(time)) || (!TimeTool::isEndAfterStart(nowTime, this->startTime)))
    {
        std::cout << "输入预约开始时间有误，请重新输入：";
        TimeTool::generateTimeStamp(nowTime);
        safeInput(time, 20);
        TimeTool::standardToStamp(this->startTime, time);
    }

    std::cout << "请输入预约结束时间(格式为YYYY-MM-DD HH:MM)：";
    safeInput(time, 20);
    TimeTool::standardToStamp(this->endTime, time);
    while ((!TimeTool::checkTimeFormat(time)) || !(TimeTool::isEndAfterStart(this->startTime, this->endTime)))
    {
        std::cout << "输入预约结束时间有误，请重新输入：";
        safeInput(time, 20);
        TimeTool::standardToStamp(this->endTime, time);
    }
}

void Reservation::display()
{
    std::cout << "预约编号：" << reservationId << std::endl;
    std::cout << "车位编号：" << spaceId << std::endl;
    std::cout << "车主姓名：" << ownerName << std::endl;
    std::cout << "车牌号：" << plateNumber << std::endl;
    std::cout << "手机号：" << phone << std::endl;
    char time[20];
    time_t stampTime = TimeTool::charArrayToLongLong(startTime);
    tm *nowTime = localtime(&stampTime);
    std::sprintf(time,
                 "%04d-%02d-%02d %02d:%02d",
                 nowTime->tm_year + 1900,
                 nowTime->tm_mon + 1,
                 nowTime->tm_mday,
                 nowTime->tm_hour,
                 nowTime->tm_min);

    std::cout << "预约开始时间：" << time << std::endl;

    stampTime = TimeTool::charArrayToLongLong(endTime);
    nowTime = localtime(&stampTime);
    std::sprintf(time,
                 "%04d-%02d-%02d %02d:%02d",
                 nowTime->tm_year + 1900,
                 nowTime->tm_mon + 1,
                 nowTime->tm_mday,
                 nowTime->tm_hour,
                 nowTime->tm_min);

    std::cout << "预约结束时间：" << time << std::endl;
}

bool Reservation::isValid()
{
    return std::strcmp(status, "有效") == 0;
}

bool Reservation::isUsed()
{
    return std::strcmp(status, "已使用") == 0;
}

bool Reservation::isCanceled()
{
    return std::strcmp(status, "已取消") == 0;
}

bool Reservation::isExpired()
{
    return std::strcmp(status, "已过期") == 0;
}

bool Reservation::isInTimeRange(char now[])
{
    long long nowStamp = TimeTool::charArrayToLongLong(now);
    long long startStamp = TimeTool::charArrayToLongLong(startTime);
    long long endStamp = TimeTool::charArrayToLongLong(endTime);

    if (nowStamp == 0 || startStamp == 0 || endStamp == 0)
        return false;

    return nowStamp >= startStamp && nowStamp <= endStamp;
}

bool Reservation::isOverEndTime(char now[])
{
    long long nowStamp = TimeTool::charArrayToLongLong(now);
    long long endStamp = TimeTool::charArrayToLongLong(endTime);

    if (nowStamp == 0 || endStamp == 0)
        return false;

    return nowStamp > endStamp;
}

bool Reservation::isTimeConflict(char start[], char end[])
{
    if (!isValid())
        return false;

    long long startStamp = TimeTool::charArrayToLongLong(start);
    long long endStamp = TimeTool::charArrayToLongLong(end);
    long long myStartStamp = TimeTool::charArrayToLongLong(startTime);
    long long myEndStamp = TimeTool::charArrayToLongLong(endTime);

    if (startStamp == 0 || endStamp == 0 || myStartStamp == 0 || myEndStamp == 0)
        return false;

    return startStamp < myEndStamp && endStamp > myStartStamp;
}

bool Reservation::isSameReservationId(char id[])
{
    return std::strcmp(id, reservationId) == 0;
}

bool Reservation::isSameSpaceId(char id[])
{
    return std::strcmp(id, spaceId) == 0;
}

bool Reservation::isSamePlateNumber(char plate[])
{
    return std::strcmp(plate, plateNumber) == 0;
}
