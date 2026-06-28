#ifndef TIMETOOL_H
#define TIMETOOL_H

const int timeStampLength = 20;
const int standardTimeLength = 20;

class TimeTool
{
public:
    static void generateTimeStamp(char result[]);                     // 生成时间戳，用于预约编号或账单编号
    static void getCurrentTime(char now[]);                           // 获取当前系统时间 返回标准格式`YYYY-MM-DD HH:MM`
    static double calculateHours(char start[], char end[]);           // 计算两个时间之间相差的小时数
    static bool isBeforeOneHour(char now[], char start[]);            // 判断当前时间是否早于预约开始前 1 小时  传入时间戳
    static bool isEndAfterStart(char start[], char end[]);            // 判断结束时间是否晚于开始时间  传入时间戳
    static void standardToStamp(char destination[], char resource[]); // 将标准时间转换成时间戳
    static bool checkTimeFormat(char time[]);                         // 检查时间格式是否为`YYYY-MM-DD HH:MM`(会检测时间是否合法)
    static long long charArrayToLongLong(char number[]);              // 将字符数组转换成long long
};

#endif
