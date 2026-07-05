#include "BlackList.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <cstring>
BlackNode::BlackNode() : next(nullptr) { strcpy(plateNumber, ""); }

BlackList::BlackList() : head(nullptr), length(0) {}

void BlackList::addToBlackList(char number[])
{
    if (!Validator::checkPlateNumber(number))
    {
         std::cout << "车牌号输入有误" << std::endl;
        return;
    }

    if (findBlackPlateNumber(number))
    {
        std::cout << "该车牌已在黑名单中" << std::endl;
        return;
    }

    BlackNode *node = new BlackNode();
    std::strcpy(node->plateNumber, number);

    if (head == nullptr)
        head = node;
    else
    {
        BlackNode *tail = head;
        while (tail->next != nullptr)
            tail = tail->next;

        tail->next = node;
    }

    length++;
    std::cout << "加入黑名单成功" << std::endl;
}

void BlackList::deleteBlackPlateNumber(char number[])
{
    BlackNode *previous = nullptr;
    BlackNode *current = head;

    while (current != nullptr)
    {
        if (std::strcmp(current->plateNumber, number) == 0)
        {
            if (previous == nullptr)
                head = current->next;
            else
                previous->next = current->next;

            delete current;
            length--;
            std::cout << "移出黑名单成功" << std::endl;
            return;
        }

        previous = current;
        current = current->next;
    }

    std::cout << "未找到该黑名单车牌" << std::endl;
}

bool BlackList::findBlackPlateNumber(char number[])
{
    BlackNode *current = head;
    while (current != nullptr)
    {
        if (std::strcmp(current->plateNumber, number) == 0)
            return true;

        current = current->next;
    }

    return false;
}

void BlackList::displayBlackList()
{
    if (head == nullptr)
    {
        std::cout << "暂无黑名单车牌" << std::endl;
        return;
    }

    BlackNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->plateNumber << std::endl;
        current = current->next;
    }
}

void BlackList::loadFromFile()
{
    std::ifstream inFile("blacklist.dat", std::ios::binary);
    if (!inFile)
        return;

    BlackNode *current = head;
    while (current != nullptr)
    {
        BlackNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    length = 0;

    int count = 0;
    inFile.read((char *)(&count), sizeof(count));
    if (!inFile || count < 0)
        return;

    BlackNode *tail = nullptr;
    for (int i = 0; i < count; i++)
    {
        BlackNode *node = new BlackNode();
        inFile.read((char *)(node->plateNumber), sizeof(node->plateNumber));
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

void BlackList::saveToFile()
{
    std::ofstream outFile("blacklist.dat", std::ios::binary);
    if (!outFile)
    {
        std::cout << "黑名单数据保存失败" << std::endl;
       return;
    }

    outFile.write((char *)(&length), sizeof(length));

    BlackNode *current = head;
    while (current != nullptr)
    {
        outFile.write((char *)(current->plateNumber), sizeof(current->plateNumber));
        current = current->next;
    }
}

BlackList::~BlackList()
{
    BlackNode *now = head;
    while (now != nullptr)
    {
        BlackNode *next = now->next;
        delete now;
        now = next;
    }
}
