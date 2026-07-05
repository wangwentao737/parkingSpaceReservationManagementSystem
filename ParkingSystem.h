#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "ParkingSpaceList.h"
#include "ReservationList.h"
#include "BillList.h"
#include "BlackList.h"
#include "Validator.h"
#include "TimeTool.h"
#include <iostream>
#include <iomanip>
#include <cstring>

class ParkingSystem
{
private:
    ParkingSpaceList parkingList;
    ReservationList reservationList;
    BlackList blackList;
    BillList billList;

public:
    void menu();              // 主菜单
    void parkingManageMenu(); // 车位管理菜单
    void reservationMenu();   // 预约菜单
    void queryMenu();         // 查询菜单
    void statisticsMenu();    // 统计菜单
    void blaclListMenu();     // 黑名单管理菜单

    void addParkingSpace();    // 添加车位
    void deleteParkingSpace(); // 删除车位
    void modifyParkingSpace(); // 修改车位

    void reserveSpace();         // 预约车位
    void enterWithReservation(); // 有预约进场
    void temporaryEnter();       // 临时进场
    void specilaEnter();         // 特殊进场(由于前车未离场导致后车无法进入，由管理员取消之前的预约后再进行临时进场)
    void leaveAndPay();          // 离场结算
    void cancelReservation();    // 取消预约

    void queryFreeSpaces();   // 查询空闲车位
    void querySpaceHistory(); // 查询车位历史
    void queryPlateHistory(); // 查询车牌历史

    void addPlateToBlackList();
    void deletePlateFromBlackList();
    void displayAllBlackPlate();

    void countUsageRate(); // 统计使用率
    void countIncome();    // 统计收入

    void loadAll(); // 读取全部文件
    void saveAll(); // 保存全部文件
};

#endif