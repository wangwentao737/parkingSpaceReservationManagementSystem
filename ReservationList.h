#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

#include "Reservation.h"

class ReservationNode
{
public:
    Reservation data;
    ReservationNode *next;

    ReservationNode();
};

class ReservationList
{
private:
    ReservationNode *head;
    int length;

public:
    ReservationList();
    void addReservation(Reservation &reservation);
    void cancelReservation(char reservationId[]);                    // 根据预约编号取消 等find
    Reservation *findReservation(char reservationId[]);              // 按预约编号查找，无返回nullptr
    void displayBySpaceId(char spaceId[]);                           // 按车位打印信息
    void displayByPlateNumber(char plateNumber[]);                   // 按车牌号打印信息
    bool hasFutureReservation(char spaceId[]);                       // 判断某个车位后面是否还有有效预约
    bool isSpaceAvailable(char spaceId[], char start[], char end[]); // 判断某个车位在给定预约时间段内是否可用
    void checkExpiredReservations();                                 // 扫描链表，把已经超过结束时间但状态仍是 有效 的预约改成 已过期
    void loadFromFile();
    void saveToFile();
    ~ReservationList();
};

#endif
