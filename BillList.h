#ifndef BILLLIST_H
#define BILLLIST_H

#include "Bill.h"
class BillNode
{
public:
    Bill data;
    BillNode *next;

    BillNode()
    {
        next = nullptr;
    }
};
class BillList
{
private:
    BillNode *head;
    int length;

public:
    BillList();
    void addBill(Bill bill);
    void displayAll();
    void displayByPlateNumber(char plateNumber[]);
    void displayBySpaceId(char spaceId[]);
    double countDailyIncome(char date[]);
    double countMonthlyIncome(char month[]);
    void loadFromFile();
    void saveToFile();
    ~BillList();
};
#endif
