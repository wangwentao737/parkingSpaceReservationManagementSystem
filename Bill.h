#ifndef BILL_H
#define BILL_H

class Bill
{
public:
    char billId[30];      // 账单编号
    char spaceId[20];     // 车位编号
    char plateNumber[20]; // 车牌号
    char inTime[20];      // 进场时间
    char outTime[20];     // 离场时间
    double hours;         // 停车时长
    double fee;           // 停车费用

    void display();                       // 显示账单信息
    double calculateFee();                // 计算停车费用
    bool isSameSpaceId(char id[]);        // 判断车位编号是否相同
    bool isSamePlateNumber(char plate[]); // 判断车牌号是否相同
};

#endif