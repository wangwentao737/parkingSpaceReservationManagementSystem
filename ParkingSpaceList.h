#ifndef PARKINGSPACELIST_H
#define PARKINGSPACELIST_H
#include "ParkingSpace.h"
#include "ReservationList.h"
class ParkingSpaceNode
{
public:
    ParkingSpace data;
    ParkingSpaceNode *next;
    ParkingSpaceNode()
    {
        next = nullptr;
    }
};
class ParkingSpaceList
{
private:
    ParkingSpaceNode *head;
    int length;

public:
    ParkingSpaceList();
    void addSpace();                                                                                                 // 添加车位
    void deleteSpace(char spaceId[]);                                                                                // 删除车位
    void modifySpace(char spaceId[]);                                                                                // 修改车位
    ParkingSpace *findSpace(char spaceId[]);                                                                         // 查找车位
    void displayAll();                                                                                               // 显示全部车位
    void displayFreeByType(char type[]);                                                                             // 按类型显示空闲车位
    ParkingSpace *findFreeSpace(char type[]);                                                                        // 查找指定类型的空闲车位
    ParkingSpace *findAvailableSpaceByTime(char type[], ReservationList &reservationList, char start[], char end[]); // 查找指定类型且预约时间段可用的车位
    void changeStatus(char spaceId[], char status[]);
    double UsageRate();
    void loadFromFile(); // 从文件读取车位数据
    void saveToFile();   // 保存车位数据到文件
    ~ParkingSpaceList();
};
#endif