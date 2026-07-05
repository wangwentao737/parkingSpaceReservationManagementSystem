#include "ReservationList.h"
#include "ParkingSpaceList.h"
#include "TimeTool.h"
#include "Validator.h"
#include <fstream>
#include <iostream>
#include <cstring>

ReservationNode::ReservationNode() : next(nullptr) {}

ReservationList::ReservationList() : head(nullptr), length(0) {}

void ReservationList::addReservation(Reservation &reservation)
{
    ReservationNode *node = new ReservationNode;
    node->data = reservation;

    if (head == nullptr)
        head = node;
    else
    {
        ReservationNode *p = head;
        while (p->next != nullptr)
            p = p->next;

        p->next = node;
    }
    length++;
}

void ReservationList::cancelReservation(char reservationId[])
{
    ReservationNode *search = head;
    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);

    while (search != nullptr)
    {
        if (search->data.isSameReservationId(reservationId))
        {
            if (!TimeTool::isBeforeOneHour(nowTime, search->data.startTime))
            {
                std::cout << "距离预约时间小于一小时，无法取消" << std::endl;
                return;
            }

            std::strcpy(search->data.status, "已取消");
            std::cout << "取消成功" << std::endl;
            return;
        }

        search = search->next;
    }

    std::cout << "该预约编号无效" << std::endl;
}

Reservation *ReservationList::findReservation(char reservationId[])
{
    ReservationNode *search = head;
    while (search != nullptr)
    {
        if (search->data.isSameReservationId(reservationId))
            return &search->data;

        search = search->next;
    }

    return nullptr;
}

void ReservationList::displayBySpaceId(char spaceId[])
{
    ReservationNode *search = head;
    bool found = false;

    while (search != nullptr)
    {
        if (search->data.isSameSpaceId(spaceId))
        {
            found = true;
            search->data.display();
            std::cout << "-------------------------------------" << std::endl;
        }

        search = search->next;
    }

    if (!found)
        std::cout << "未找到该车位的预约记录" << std::endl;
}

void ReservationList::displayByPlateNumber(char plateNumber[])
{
    ReservationNode *search = head;
    bool found = false;

    while (search != nullptr)
    {
        if (search->data.isSamePlateNumber(plateNumber))
        {
            found = true;
            search->data.display();
            std::cout << "-------------------------------------" << std::endl;
        }

        search = search->next;
    }

    if (!found)
        std::cout << "未找到该车牌号的预约记录" << std::endl;
}

bool ReservationList::hasFutureReservation(char spaceId[])
{
    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);

    ReservationNode *search = head;
    while (search != nullptr)
    {
        if (search->data.isSameSpaceId(spaceId) &&
            search->data.isValid() &&
            TimeTool::isEndAfterStart(nowTime, search->data.startTime))
            return true;

        search = search->next;
    }

    return false;
}

bool ReservationList::isSpaceAvailable(char spaceId[], char start[], char end[])
{
    if (!TimeTool::isEndAfterStart(start, end))
        return false;

    ReservationNode *search = head;
    while (search != nullptr)
    {
        if (search->data.isSameSpaceId(spaceId) && search->data.isTimeConflict(start, end))
            return false;

        search = search->next;
    }

    return true;
}

void ReservationList::checkExpiredReservations()
{
    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);

    ReservationNode *search = head;
    while (search != nullptr)
    {
        if (search->data.isValid() && search->data.isOverEndTime(nowTime))
            std::strcpy(search->data.status, "已过期");

        search = search->next;
    }
}

void ReservationList::loadFromFile()
{
    std::ifstream inFile("reservations.dat", std::ios::binary);
    if (!inFile)
        return;

    ReservationNode *now = head;
    // 清空原链表
    while (now != nullptr)
    {
        ReservationNode *next = now->next;
        delete now;
        now = next;
    }
    head = nullptr;
    length = 0;

    int count = 0;
    inFile.read((char *)(&count), sizeof(count));

    if (!inFile || count < 0)
        return;

    ReservationNode *tail = nullptr;
    for (int i = 0; i < count; i++)
    {
        ReservationNode *node = new ReservationNode();
        inFile.read((char *)(&node->data), sizeof(Reservation));

        if (!inFile)
        {
            delete node;
            break;
        }

        if (head == nullptr)
            head = node;
        else
            tail->next = node;

        tail = node;
        length++;
    }
}

void ReservationList::saveToFile()
{
    std::ofstream outFile("reservations.dat", std::ios::binary);
    if (!outFile)
    {
        std::cout << "数据保存失败" << std::endl;
        return;
    }

    outFile.write((char *)(&length), sizeof(length));

    ReservationNode *now = head;
    while (now != nullptr)
    {
        outFile.write((char *)(&now->data), sizeof(Reservation));
        now = now->next;
    }
}

ReservationList::~ReservationList()
{
    ReservationNode *now = head;
    while (now != nullptr)
    {
        ReservationNode *next = now->next;
        delete now;
        now = next;
    }
}
