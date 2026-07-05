#include "ParkingSpaceList.h"
#include "Validator.h"
#include "ParkingSpace.h"
#include "ReservationList.h"
#include <iostream>
#include <fstream>
#include <cstring>
ParkingSpaceList::ParkingSpaceList() : head(nullptr), length(0) {};

void ParkingSpaceList::addSpace()
{
    ParkingSpaceNode *node = new ParkingSpaceNode();
    std::cout << "请输入你要增加的车位信息" << std::endl;
    node->data.input();

    if (head == nullptr)
        head = node;
    else
    {
        head->next = node;
        node = head;
    }

    length++;
}

void ParkingSpaceList::deleteSpace(char spaceId[])
{
    ParkingSpaceNode *previous = nullptr;
    ParkingSpaceNode *current = head;

    while (current != nullptr)
    {
        if (current->data.isSameId(spaceId))
        {
            if (previous == nullptr)
                head = current->next;
            else
                previous->next = current->next;

            delete current;
            length--;
            std::cout << "删除车位成功" << std::endl;
            return;
        }

        previous = current;
        current = current->next;
    }

    std::cout << "未找到该车位" << std::endl;
}

void ParkingSpaceList::modifySpace(char spaceId[])
{
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        if (node->data.isSameId(spaceId))
        {
            node->data.modify();
            return;
        }
        node = node->next;
    }
}

ParkingSpace *ParkingSpaceList::findSpace(char spaceId[])
{
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        if (node->data.isSameId(spaceId))
        {
            return &(node->data);
        }
        node = node->next;
    }
    return nullptr;
}

void ParkingSpaceList::displayAll()
{
    bool find = false;
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        find = true;
        node->data.display();
        std::cout << "-------------------------------------" << std::endl;
        node = node->next;
    }

    if (!find)
        std::cout << "暂无车位" << std::endl;
}

void ParkingSpaceList::displayFreeByType(char type[])
{
    bool find = false;
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        if (std::strcmp(node->data.type, type) == 0 && node->data.isFree())
        {
            node->data.display();
            find = true;
        }
        node = node->next;
    }

    if (!find)
        std::cout << "暂无该类型的空闲车位" << std::endl;
}

ParkingSpace *ParkingSpaceList::findFreeSpace(char type[])
{
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        if (std::strcmp(node->data.type, type) == 0 && node->data.isFree())
        {
            return &(node->data);
        }
        node = node->next;
    }
    return nullptr;
}

ParkingSpace *ParkingSpaceList::findAvailableSpaceByTime(char type[], ReservationList &reservationList, char start[], char end[])
{
    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        bool statusCanReserve = std::strcmp(node->data.status, "空闲") == 0 ||
                                std::strcmp(node->data.status, "已预约") == 0;
        if (std::strcmp(node->data.type, type) == 0 &&
            statusCanReserve &&
            reservationList.isSpaceAvailable(node->data.spaceId, start, end))
        {
            return &(node->data);
        }
        node = node->next;
    }
    return nullptr;
}

void ParkingSpaceList::changeStatus(char spaceId[], char status[])
{
    ParkingSpace *node = findSpace(spaceId);
    if (node == nullptr)
        return;
    strcpy(node->status, status);
}

double ParkingSpaceList::UsageRate()
{
    if (length == 0)
        return -1;

    double count = 0;

    ParkingSpaceNode *node = head;
    while (node != nullptr)
    {
        if (node->data.isFree())
            count++;
        node = node->next;
    }

    return count / (double)length;
}

void ParkingSpaceList::loadFromFile()
{
    std::ifstream inFile("parking_spaces.dat", std::ios::binary);
    if (!inFile)
        return;

    ParkingSpaceNode *now = head;
    while (now != nullptr)
    {
        ParkingSpaceNode *next = now->next;
        delete now;
        now = next;
    }
    head = nullptr;
    length = 0;

    int count = 0;
    inFile.read((char *)(&count), sizeof(count));
    if (!inFile || count < 0)
        return;

    ParkingSpaceNode *tail = nullptr;
    for (int i = 0; i < count; i++)
    {
        ParkingSpaceNode *node = new ParkingSpaceNode();
        inFile.read((char *)(&node->data), sizeof(ParkingSpace));
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

void ParkingSpaceList::saveToFile()
{
    std::ofstream outFile("parking_spaces.dat", std::ios::binary);
    if (!outFile)
    {
        std::cout << "车位数据保存失败" << std::endl;
        return;
    }

    outFile.write((char *)(&length), sizeof(length));

    ParkingSpaceNode *now = head;
    while (now != nullptr)
    {
        outFile.write((char *)(&now->data), sizeof(ParkingSpace));
        now = now->next;
    }
}

ParkingSpaceList::~ParkingSpaceList()
{
    ParkingSpaceNode *node1 = head;
    ParkingSpaceNode *node2 = head;

    while (node1 != nullptr)
    {
        node2 = node2->next;
        delete node1;
        node1 = node2;
    }
}