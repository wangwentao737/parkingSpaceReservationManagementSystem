#ifndef RESERVATION_H
#define RESERVATION_H

class Reservation
{
public:
    char reservationId[20]; // 预约编号
    char spaceId[20];       // 车位编号
    char ownerName[20];     // 车主姓名
    char plateNumber[20];   // 车牌号
    char phone[20];         // 手机号
    char startTime[20];     // 预约开始时间
    char endTime[20];       // 预约结束时间
    char status[20];        // 有效 / 已使用 / 已取消 / 已过期
    char actualInTime[20];  // 实际进场时间
    
    Reservation();
    void input();                         // 输入预约信息
    void display();                       // 显示预约信息
    bool isValid();                       // 判断预约是否有效
    bool isUsed();                        // 判断预约是否已使用
    bool isCanceled();                    // 判断预约是否已取消
    bool isExpired();                     // 判断预约是否已过期
    bool isInTimeRange(char now[]);       // 判断指定时间是否在预约时间段内
    bool isOverEndTime(char now[]);       // 判断指定时间是否超过预约结束时间
    bool isTimeConflict(char start[], char end[]); // 判断时间段是否与本预约冲突
    bool isSameReservationId(char id[]);  // 判断预约编号是否相同
    bool isSameSpaceId(char id[]);        // 判断车位编号是否相同
    bool isSamePlateNumber(char plate[]); // 判断车牌号是否相同
};

#endif
