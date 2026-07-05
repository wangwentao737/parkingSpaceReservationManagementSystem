#include "ParkingSystem.h"

void ParkingSystem::menu()
{
    loadAll();
    std::cout << "欢迎使用车位预约管理系统" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.车位管理 2.预约、进场与离场管理 3.查询 4.统计 5.黑名单管理 0.退出)：";

        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            parkingManageMenu();
        else if (strcmp(check, "2") == 0)
            reservationMenu();
        else if (strcmp(check, "3") == 0)
            queryMenu();
        else if (strcmp(check, "4") == 0)
            statisticsMenu();
        else if (strcmp(check, "5") == 0)
            blaclListMenu();
    } while (strcmp(check, "0") != 0);

    saveAll();
}

//-----------------------------------

void ParkingSystem::parkingManageMenu()
{
    std::cout << "请输入管理员密码：";
    char passpord[20];
    safeInput(passpord, 20);
    if (strcmp(passpord, "ujs") != 0)
    {
        std::cout << "密码错误" << std::endl;
        return;
    }

    std::cout << "您已进入车位管理菜单" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.添加车位 2.修改车位 3.删除车位 0.返回)：";

        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            addParkingSpace();
        else if (strcmp(check, "2") == 0)
            modifyParkingSpace();
        else if (strcmp(check, "3") == 0)
            deleteParkingSpace();

    } while (strcmp(check, "0") != 0);
}

void ParkingSystem::addParkingSpace()
{
    parkingList.addSpace();
}

void ParkingSystem::deleteParkingSpace()
{
    std::cout << "请输入需要删除的车位编号：";
    char sId[20];

    safeInput(sId, 20);
    if (parkingList.findSpace(sId) == nullptr)
    {
        std::cout << "该车位不存在" << std::endl;
        return;
    }

    parkingList.deleteSpace(sId);
}

void ParkingSystem::modifyParkingSpace()
{
    std::cout << "请输入需要修改的车位编号：";
    char sId[20];

    safeInput(sId, 20);
    if (parkingList.findSpace(sId) == nullptr)
    {
        std::cout << "该车位不存在" << std::endl;
        return;
    }

    parkingList.modifySpace(sId);
}

//-----------------------------------

void ParkingSystem::reservationMenu()
{
    std::cout << "您已进入预约、进场与离场管理菜单" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.预约车位 2.有预约进场 3.临时进场 4.取消预约 5.离场结算 6.特殊进场(仅由管理员操作) 0.返回)：";

        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            reserveSpace();
        else if (strcmp(check, "2") == 0)
            enterWithReservation();
        else if (strcmp(check, "3") == 0)
            temporaryEnter();
        else if (strcmp(check, "4") == 0)
            deleteParkingSpace();
        else if (strcmp(check, "5") == 0)
            leaveAndPay();
        else if (strcmp(check, "6") == 0)
            specilaEnter();
    } while (strcmp(check, "0") != 0);
}

void ParkingSystem::reserveSpace()
{
    std::cout << "请选择车位类型(输入数字即可，1.普通 2.充电 3.无障碍)：";
    char ttype[20];
    while (true)
    {
        safeInput(ttype, 20);
        if (std::strcmp(ttype, "1") == 0 || std::strcmp(ttype, "2") == 0 || std::strcmp(ttype, "3") == 0)
            break;
        std::cout << "输入有误，请重新输入！" << std::endl;
        std::cout << "请选择车位类型(输入数字即可，1.普通 2.充电 3.无障碍)：";
    }

    if (std::strcmp(ttype, "1") == 0)
        std::strcpy(ttype, "普通");
    else if (std::strcmp(ttype, "2") == 0)
        std::strcpy(ttype, "充电");
    else if (std::strcmp(ttype, "3") == 0)
        std::strcpy(ttype, "无障碍");

    Reservation add;

    add.input();
    if (blackList.findBlackPlateNumber(add.plateNumber))
    {
        std::cout << "该车牌已进入系统黑名单，无法预约，请联系管理员" << std::endl;
        return;
    }

    std::cout << "请检测输入的信息是否有误，无误输入0，如需更改输入对应数字进行修改(1.车主姓名 2.车牌号 3.手机号 4.预约开始时间 5.预约结束时间)";
    add.display();

    char check[10];
    safeInput(check, 10);

    while (std::strcmp(check, "0") != 0)
    {
        if (std::strcmp(check, "1") == 0)
        {
            std::cout << "请输入车主姓名：";
            safeInput(add.ownerName, 20);
        }
        else if (std::strcmp(check, "2") == 0)
        {
            std::cout << "请输入车牌号(字母请大写，不要添加空格，新能源车主正常填写完整车牌)：";
            safeInput(add.plateNumber, 20);
            while (!Validator::checkPlateNumber(add.plateNumber))
            {
                std::cout << "输入车牌号有误，请重新输入：";
                safeInput(add.plateNumber, 20);
            }
            if (blackList.findBlackPlateNumber(add.plateNumber))
            {
                std::cout << "该车牌已进入系统黑名单，无法预约，请联系管理员" << std::endl;
                return;
            }
        }
        else if (std::strcmp(check, "3") == 0)
        {
            std::cout << "请输入手机号：";
            safeInput(add.phone, 20);
            while (!Validator::checkPhone(add.phone))
            {
                std::cout << "输入手机号有误，请重新输入：";
                safeInput(add.phone, 20);
            }
        }
        else if (std::strcmp(check, "4") == 0)
        {
            std::cout << "请输入预约开始时间(格式为YYYY-MM-DD HH:MM)：";
            char time[20];
            char nowTime[20];

            safeInput(time, 20);
            TimeTool::standardToStamp(add.startTime, time);
            TimeTool::generateTimeStamp(nowTime);

            while ((!TimeTool::checkTimeFormat(time)) ||
                   (!TimeTool::isEndAfterStart(nowTime, add.startTime)) ||
                   (!TimeTool::isEndAfterStart(add.startTime, add.endTime)))
            {
                std::cout << "输入预约开始时间有误，请重新输入：";
                safeInput(time, 20);
                TimeTool::standardToStamp(add.startTime, time);
                TimeTool::generateTimeStamp(nowTime);
            }
        }
        else if (std::strcmp(check, "5") == 0)
        {
            std::cout << "请输入预约结束时间(格式为YYYY-MM-DD HH:MM)：";
            char time[20];

            safeInput(time, 20);
            TimeTool::standardToStamp(add.endTime, time);

            while ((!TimeTool::checkTimeFormat(time)) || (!TimeTool::isEndAfterStart(add.startTime, add.endTime)))
            {
                std::cout << "输入预约结束时间有误，请重新输入：";
                safeInput(time, 20);
                TimeTool::standardToStamp(add.endTime, time);
            }
        }
        else
        {
            std::cout << "输入有误，请重新输入！" << std::endl;
        }

        std::cout << "请检测输入的信息是否有误，无误输入0，如需更改输入对应数字进行修改(1.车主姓名 2.车牌号 3.手机号 4.预约开始时间 5.预约结束时间)";
        add.display();
        safeInput(check, 10);
    }

    ParkingSpace *reservationSpace = parkingList.findAvailableSpaceByTime(ttype, reservationList, add.startTime, add.endTime);
    if (reservationSpace == nullptr)
    {
        std::cout << "该类型车位在该预约时间段暂无可用车位，无法预约。" << std::endl;
        return;
    }

    char reserId[20] = "Y";
    char reserStamp[20];
    TimeTool::generateTimeStamp(reserStamp);
    strcat(reserId, reserStamp);
    strcpy(add.reservationId, reserId);
    std::strcpy(add.spaceId, reservationSpace->spaceId);
    std::strcpy(add.status, "有效");
    parkingList.changeStatus(add.spaceId, (char *)"已预约");
    reservationList.addReservation(add);

    std::cout << "预约成功！预约编号为：" << add.reservationId << "，车位编号为：" << add.spaceId << std::endl;
}

void ParkingSystem::enterWithReservation()
{
    reservationList.checkExpiredReservations();

    std::cout << "请输入预约编号:";
    char id[20];
    safeInput(id, 20);
    Reservation *node = reservationList.findReservation(id);
    if (node == nullptr)
    {
        std::cout << "预约编号无效" << std::endl;
        return;
    }

    if (!node->isValid())
    {
        std::cout << "该预约" << node->status << std::endl;
        return;
    }

    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);
    if (!node->isInTimeRange(nowTime))
    {
        if (TimeTool::charArrayToLongLong(nowTime) < TimeTool::charArrayToLongLong(node->startTime))
            std::cout << "未到预约开始时间，暂不能进场" << std::endl;
        else
        {
            std::strcpy(node->status, "已过期");
            std::cout << "预约已超过结束时间，无法进场" << std::endl;
        }
        return;
    }

    // 防止预约后车位被管理员删除
    ParkingSpace *space = parkingList.findSpace(node->spaceId);
    if (space == nullptr)
    {
        std::cout << "预约对应车位不存在，不能入场" << std::endl;
        return;
    }

    if (std::strcmp(space->status, "已占用") == 0 || std::strcmp(space->status, "超时占用") == 0)
    {
        std::cout << "预约车位当前被占用，不能入场，请管理员手动安排其他空闲车位。" << std::endl;
        return;
    }

    if (std::strcmp(space->status, "空闲") != 0 && std::strcmp(space->status, "已预约") != 0)
    {
        std::cout << "预约车位当前状态为" << space->status << "，不能入场，请管理员手动安排其他空闲车位。" << std::endl;
        return;
    }

    std::cout << "预约编号有效，欢迎进入！" << std::endl;
    std::strcpy(node->status, "已使用");
    parkingList.changeStatus(node->spaceId, (char *)"已占用");
    std::strcpy(node->actualInTime, nowTime);
}

void ParkingSystem::temporaryEnter()
{

    std::cout << "请选择车位类型(输入数字即可，1.普通 2.充电 3.无障碍)：";
    char ttype[20];
    while (true)
    {
        safeInput(ttype, 20);
        if (std::strcmp(ttype, "1") == 0 || std::strcmp(ttype, "2") == 0 || std::strcmp(ttype, "3") == 0)
            break;
        std::cout << "输入有误，请重新输入！" << std::endl;
        std::cout << "请选择车位类型(输入数字即可，1.普通 2.充电 3.无障碍)：";
    }

    if (std::strcmp(ttype, "1") == 0)
        std::strcpy(ttype, "普通");
    else if (std::strcmp(ttype, "2") == 0)
        std::strcpy(ttype, "充电");
    else if (std::strcmp(ttype, "3") == 0)
        std::strcpy(ttype, "无障碍");

    Reservation add;

    add.input();

    if (blackList.findBlackPlateNumber(add.plateNumber))
    {
        std::cout << "该车牌已进入系统黑名单，无法预约，请联系管理员" << std::endl;
        return;
    }

    std::cout << "请检测输入的信息是否有误，无误输入0，如需更改输入对应数字进行修改(1.车主姓名 2.车牌号 3.手机号 4.预约开始时间 5.预约结束时间)";
    add.display();

    char check[10];
    safeInput(check, 10);

    while (std::strcmp(check, "0") != 0)
    {
        if (std::strcmp(check, "1") == 0)
        {
            std::cout << "请输入车主姓名：";
            safeInput(add.ownerName, 20);
        }
        else if (std::strcmp(check, "2") == 0)
        {
            std::cout << "请输入车牌号(字母请大写，不要添加空格，新能源车主正常填写完整车牌)：";
            safeInput(add.plateNumber, 20);
            while (!Validator::checkPlateNumber(add.plateNumber))
            {
                std::cout << "输入车牌号有误，请重新输入：";
                safeInput(add.plateNumber, 20);
            }

            if (blackList.findBlackPlateNumber(add.plateNumber))
            {
                std::cout << "该车牌已进入系统黑名单，无法预约，请联系管理员" << std::endl;
                return;
            }
        }
        else if (std::strcmp(check, "3") == 0)
        {
            std::cout << "请输入手机号：";
            safeInput(add.phone, 20);
            while (!Validator::checkPhone(add.phone))
            {
                std::cout << "输入手机号有误，请重新输入：";
                safeInput(add.phone, 20);
            }
        }
        else if (std::strcmp(check, "4") == 0)
        {
            std::cout << "请输入预约开始时间(格式为YYYY-MM-DD HH:MM)：";
            char time[20];
            char nowTime[20];

            safeInput(time, 20);
            TimeTool::standardToStamp(add.startTime, time);
            TimeTool::generateTimeStamp(nowTime);

            while ((!TimeTool::checkTimeFormat(time)) || (!TimeTool::isEndAfterStart(nowTime, add.startTime)))
            {
                std::cout << "输入预约开始时间有误，请重新输入：";
                safeInput(time, 20);
                TimeTool::standardToStamp(add.startTime, time);
            }
        }
        else if (std::strcmp(check, "5") == 0)
        {
            std::cout << "请输入预约结束时间(格式为YYYY-MM-DD HH:MM)：";
            char time[20];

            safeInput(time, 20);
            TimeTool::standardToStamp(add.endTime, time);

            while ((!TimeTool::checkTimeFormat(time)) || (!TimeTool::isEndAfterStart(add.startTime, add.endTime)))
            {
                std::cout << "输入预约结束时间有误，请重新输入：";
                safeInput(time, 20);
                TimeTool::standardToStamp(add.endTime, time);
            }
        }

        std::cout << "请检测输入的信息是否有误，无误输入0，如需更改输入对应数字进行修改(1.车主姓名 2.车牌号 3.手机号 4.预约开始时间 5.预约结束时间)";
        add.display();
        safeInput(check, 10);
    }

    ParkingSpace *reservationSpace = parkingList.findAvailableSpaceByTime(ttype, reservationList, add.startTime, add.endTime);
    if (reservationSpace == nullptr)
    {
        std::cout << "该类型车位在该时间段暂无可用车位，无法临时进场。" << std::endl;
        return;
    }

    char nowTimeStamp[20];
    TimeTool::generateTimeStamp(nowTimeStamp);
    strcpy(add.reservationId, "Y");
    std::strcat(add.reservationId, nowTimeStamp);
    std::strcpy(add.spaceId, reservationSpace->spaceId);
    std::strcpy(add.status, "已使用");
    parkingList.changeStatus(add.spaceId, (char *)"已占用");
    TimeTool::generateTimeStamp(add.actualInTime);
    reservationList.addReservation(add);
}

void ParkingSystem::cancelReservation()
{
    reservationList.checkExpiredReservations();

    std::cout << "请输入预约编号:";
    char id[20];
    safeInput(id, 20);
    Reservation *node = reservationList.findReservation(id);
    if (node == nullptr)
    {
        std::cout << "预约编号无效" << std::endl;
        return;
    }

    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);
    if (!TimeTool::isBeforeOneHour(nowTime, node->startTime))
    {
        std::cout << "当前时间距预约开始时间小于1小时，无法取消预约" << std::endl;
        return;
    }
    strcmp(node->status, "已取消");
}

void ParkingSystem::specilaEnter()
{
    std::cout << "请输入管理员密码：";
    char passpord[20];
    safeInput(passpord, 20);
    if (strcmp(passpord, "ujs") != 0)
    {
        std::cout << "密码错误" << std::endl;
        return;
    }

    std::cout << "请输入预约编号:";
    char id[20];
    safeInput(id, 20);
    Reservation *node = reservationList.findReservation(id);
    if (node == nullptr)
    {
        std::cout << "预约编号无效" << std::endl;
        return;
    }
    strcpy(node->status, "已取消");
    std::cout << "原预约编号已取消，请按下述操作临时进场" << std::endl;
    temporaryEnter();
}

void ParkingSystem::leaveAndPay()
{
    char id[20];
    std::cout << "请输入预约编号：";
    Reservation *node = nullptr;
    do
    {
        safeInput(id, 20);
        node = reservationList.findReservation(id);
        if (node == nullptr)
            std::cout << "预约编号编号有误，请重新输入：" << std::endl;

    } while (node == nullptr);

    Bill addTolist;
    char nowTime[20];
    TimeTool::generateTimeStamp(nowTime);
    strcpy(addTolist.billId, nowTime);
    strcpy(addTolist.spaceId, node->spaceId);
    strcpy(addTolist.plateNumber, node->plateNumber);
    strcpy(addTolist.inTime, node->startTime);
    strcpy(addTolist.outTime, nowTime);

    if (strcmp(nowTime, node->endTime) > 0)
        blackList.addToBlackList(node->plateNumber);

    billList.addBill(addTolist);
}

//-----------------------------------

void ParkingSystem::queryMenu()
{
    std::cout << "请输入管理员密码：";
    char passpord[20];
    safeInput(passpord, 20);
    if (strcmp(passpord, "ujs") != 0)
    {
        std::cout << "密码错误" << std::endl;
        return;
    }

    std::cout << "您已进入查询菜单" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.查询空闲车位 2.查询车位历史 3.查询车牌历史 4.查询所有车位情况 0.返回)：";
        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            queryFreeSpaces();
        else if (strcmp(check, "2") == 0)
            querySpaceHistory();
        else if (strcmp(check, "3") == 0)
            queryPlateHistory();
        else if (strcmp(check, "4") == 0)
            parkingList.displayAll();

    } while (strcmp(check, "0") != 0);
}

void ParkingSystem::queryFreeSpaces()
{
    char check[20];
    do
    {
        std::cout << "请输入需要查询的车位类型：";
        safeInput(check, 20);
        if (!Validator::checkSpaceType(check))
        {
            std::cout << "输入有误，";
            return;
        }

    } while (!Validator::checkSpaceType(check));

    parkingList.displayFreeByType(check);
}

void ParkingSystem::querySpaceHistory()
{
    char check[20];
    std::cout << "请输入需要查询的车位编号：";
    safeInput(check, 20);
    if (parkingList.findSpace(check) == nullptr)
        std::cout << "该车位编号不存在" << std::endl;
    else
        reservationList.displayBySpaceId(check);
}

void ParkingSystem::queryPlateHistory()
{
    char check[20];
    std::cout << "请输入需要查询的车牌号：";
    safeInput(check, 20);

    if (!Validator::checkPlateNumber(check))
    {
        std::cout << "车牌号输入有误" << std::endl;
        return;
    }

    reservationList.displayByPlateNumber(check);
}

//-----------------------------------

void ParkingSystem::statisticsMenu()
{
    std::cout << "请输入管理员密码：";
    char passpord[20];
    safeInput(passpord, 20);
    if (strcmp(passpord, "ujs") != 0)
    {
        std::cout << "密码错误" << std::endl;
        return;
    }

    std::cout << "您已进入统计菜单" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.统计使用率 2.统计收入 0.返回)：";
        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            countUsageRate();
        else if (strcmp(check, "2") == 0)
            countIncome();

    } while (strcmp(check, "0") != 0);
}

void ParkingSystem::countUsageRate()
{
    double rate = parkingList.UsageRate();
    if (rate == -1)
        std::cout << "暂无车位" << std::endl;
    else if (rate == 0)
        std::cout << "当前占用率为0" << std::endl;
    else
    {
        rate *= 100;
        std::cout << "当前占用率为" << std::fixed << std::setprecision(2) << rate << "%" << std::endl;
    }
}

void ParkingSystem::countIncome()
{
    char check[20];
    std::cout << "请输入需要查询的月份或日期(例如2026-07 2026-07-01)：";
    safeInput(check, 20);
    char first[20];
    strcpy(first, check);
    strcat(first, "-01 00:00");
    strcat(check, " 00:00");
    if (TimeTool::checkTimeFormat(check))
        std::cout << "该日收入为：" << std::fixed << std::setprecision(2) << billList.countDailyIncome(check) << "元" << std::endl;
    else if (TimeTool::checkTimeFormat(first))
        std::cout << "该月收入为：" << std::fixed << std::setprecision(2) << billList.countMonthlyIncome(check) << "元" << std::endl;
    else
        std::cout << "输入有误!" << std::endl;
}

//-----------------------------------

void ParkingSystem::blaclListMenu()
{
    std::cout << "请输入管理员密码：";
    char passpord[20];
    safeInput(passpord, 20);
    if (strcmp(passpord, "ujs") != 0)
    {
        std::cout << "密码错误" << std::endl;
        return;
    }

    std::cout << "您已进入黑名单管理菜单" << std::endl;
    char check[10];
    do
    {
        std::cout << "请输入你需要的操作(1.添加黑名单 2.删除黑名单 3.显示黑名单列表 0.返回)：";
        safeInput(check, 10);
        if (strcmp(check, "1") == 0)
            addPlateToBlackList();
        else if (strcmp(check, "2") == 0)
            deletePlateFromBlackList();
        else if (strcmp(check, "3") == 0)
            displayAllBlackPlate();

    } while (strcmp(check, "0") != 0);
}

void ParkingSystem::addPlateToBlackList()
{
    char plate[20];
    std::cout << "请输入需要添加为黑名单的车牌号：";
    safeInput(plate, 20);
    blackList.addToBlackList(plate);
}

void ParkingSystem::deletePlateFromBlackList()
{
    char plate[20];
    std::cout << "请输入需要从黑名单中删除车牌号：" << std::endl;
    safeInput(plate, 20);

    if (!Validator::checkPlateNumber(plate))
    {
        std::cout << "车牌号输入有误" << std::endl;
        return;
    }

    blackList.deleteBlackPlateNumber(plate);
}

void ParkingSystem::displayAllBlackPlate()
{
    blackList.displayBlackList();
}

//-----------------------------------

void ParkingSystem::loadAll()
{
    parkingList.loadFromFile();
    reservationList.loadFromFile();
    blackList.loadFromFile();
    billList.loadFromFile();
}

void ParkingSystem::saveAll()
{
    parkingList.saveToFile();
    reservationList.saveToFile();
    blackList.saveToFile();
    billList.saveToFile();
}