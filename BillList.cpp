#include "BillList.h"
#include <fstream>
#include <iostream>

#include "BillList.h"
#include "Bill.h"
#include "TimeTool.h"
#include <iostream>
#include <cstring>
BillList::BillList()
{
    length = 0;
    head = nullptr;
}

void BillList::addBill(Bill bill)
{
    if (head == nullptr)
    {
        head->data = bill;
        head->next = nullptr;
        head->data.fee = bill.Bill::calculateFee();
    }
    else
    {
        BillNode *tem = nullptr;
        tem->next = head;
        tem->data = bill;
        head = tem;
        head->data.fee = bill.Bill::calculateFee();
    }
}

void BillList::displayAll()
{
    if (head == nullptr)
    {
        std::cout << "暂无数据,请先输入数据" << std::endl;
    }
    else
    {
        BillNode *tem = head;
        while (tem != nullptr)
        {
            tem->data.display();
            tem = tem->next;
        }
    }
}

void BillList::displayByPlateNumber(char plateNumber[])
{
    BillNode *tem = head;
    while (tem != nullptr)
    {
        if (strcpy(tem->data.plateNumber, plateNumber) == 0)
        {
            tem->data.display();
            return;
        }
    }
    std::cout << "没有车位信息，请检查车牌号是否正确" << std::endl;
}

void BillList::displayBySpaceId(char spaceId[])
{
    BillNode *tem = head;
    while (tem != nullptr)
    {
        if (strcpy(tem->data.plateNumber, spaceId) == 0)
        {
            tem->data.display();
            return;
        }
    }
    std::cout << "没有车位信息，请检查车位编号是否正确" << std::endl;
}

double BillList::countDailyIncome(char date[])
{
    char st[30], en[30];
    strcpy(st, date);
    strcpy(en, date);
    strcat(st, " 00:00");
    strcat(en, " 23:59");
    long long stime = TimeTool::charArrayToLongLong(st);
    long long etime = TimeTool::charArrayToLongLong(en);
    double result = .0;
    BillNode *node = head;
    while (node != nullptr)
    {
        long long tem = TimeTool::charArrayToLongLong(node->data.billId);
        if (tem > stime && tem < etime)
        {
            result += node->data.fee;
        }
    }
    return result;
}

double BillList::countMonthlyIncome(char month[])
{
    char st[30], en[30];
    strcpy(st, month);
    strcpy(en, month);
    if ((strcmp(month, "1") == 0 || strcmp(month, "3") == 0 || strcmp(month, "5") == 0 || strcmp(month, "7") == 0 || strcmp(month, "8") == 0 || strcmp(month, "10") == 0) || strcmp(month, "12") == 0)
    {
        strcat(st, "-1 00:00");
        strcat(en, "-30 23:59");
    }
    if (strcmp(month, "4") == 0 || strcmp(month, "6") == 0 || strcmp(month, "9") == 0 || strcmp(month, "11") == 0)
    {
        strcat(st, "-1 00:00");
        strcat(en, "-29 23:59");
    }
    if (strcmp(month, "2") == 0)
    {
        strcat(st, "-1 00:00");
        strcat(en, "-27 23:59");
    }
    long long stime = TimeTool::charArrayToLongLong(st);
    long long etime = TimeTool::charArrayToLongLong(en);
    double result = .0;
    BillNode *node = head;
    while (node != nullptr)
    {
        long long tem = TimeTool::charArrayToLongLong(node->data.billId);
        if (tem > stime && tem < etime)
        {
            result += node->data.fee;
        }
    }
    return result;
}

BillList::~BillList()
{
    BillNode *node1 = head;
    BillNode *node2 = head;

    while (node1 != nullptr)
    {
        node2 = node2->next;
        delete node1;
        node1 = node2;
    }
}

void BillList::loadFromFile()
{
    std::ifstream inFile("bill.dat", std::ios::binary);
    if (!inFile)
        return;

    BillNode *now = head;
    // 清空原链表
    while (now != nullptr)
    {
        BillNode *next = now->next;
        delete now;
        now = next;
    }
    head = nullptr;
    length = 0;

    int count = 0;
    inFile.read((char *)(&count), sizeof(count));

    if (!inFile || count < 0)
        return;

    BillNode *tail = nullptr;
    for (int i = 0; i < count; i++)
    {
        BillNode *node = new BillNode();
        inFile.read((char *)(&node->data), sizeof(Bill));

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

void BillList::saveToFile()
{
    std::ofstream outFile("bill.dat", std::ios::binary);
    if (!outFile)
    {
        std::cout << "黑名单数据保存失败" << std::endl;
        return;
    }

    outFile.write((char *)(&length), sizeof(length));

    BillNode *now = head;
    while (now != nullptr)
    {
        outFile.write((char *)(&now->data), sizeof(Bill));
        now = now->next;
    }
}