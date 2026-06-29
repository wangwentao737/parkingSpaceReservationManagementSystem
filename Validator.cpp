#include "Validator.h"
#include <iostream>
#include <cstring>
#include <cctype>
bool Validator::checkPlateNumber(char plate[])
{ // 车牌号7位或8位 第一位合法简称 第二位大写字母，新能源车牌多一位
    int len = std::strlen(plate);
    if (len < 8)
        return false;

    unsigned char first = static_cast<unsigned char>(plate[0]);
    if (first <= 127)
        return false;

    int provinceBytes = 2;
    if (len >= 3)
    {
        unsigned char second = static_cast<unsigned char>(plate[1]);
        unsigned char third = static_cast<unsigned char>(plate[2]);
        if ((first & 0xF0) == 0xE0 && (second & 0xC0) == 0x80 && (third & 0xC0) == 0x80)
            provinceBytes = 3;
    }

    if (len <= provinceBytes)
        return false;

    const char *legalProvince[] = {
        "京", "津", "沪", "渝", "冀", "豫", "云", "辽", "黑", "湘",
        "皖", "鲁", "新", "苏", "浙", "赣", "鄂", "桂", "甘", "晋",
        "蒙", "陕", "吉", "闽", "贵", "粤", "青", "藏", "川", "宁",
        "琼", "港", "澳", "台"};

    bool isLegalProvince = false;
    for (int i = 0; i < 33; i++)
    {
        if (std::strlen(legalProvince[i]) == provinceBytes &&
            std::strncmp(plate, legalProvince[i], provinceBytes) == 0)
        {
            isLegalProvince = true;
            break;
        }
    }
    if (!isLegalProvince)
        return false;

    if (!(plate[provinceBytes] >= 'A' && plate[provinceBytes] <= 'Z'))
        return false;

    int restLen = len - provinceBytes - 1;
    if (!(restLen == 5 || restLen == 6))
        return false;

    for (int i = provinceBytes + 1; i < len; i++)
    {
        unsigned char ch = static_cast<unsigned char>(plate[i]);
        if (!std::isdigit(ch) && !(ch >= 'A' && ch <= 'Z'))
            return false;
    }

    return true;
}
bool Validator::checkPhone(char phone[])
{
    int len = std::strlen(phone);
    if (len != 11)
        return false;
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(phone[i]))
        {
            return false;
        }
    }
    return true;
}
bool Validator::checkSpaceType(char type[])
{
    if (strcmp(type, "普通") == 0 || strcmp(type, "充电") == 0 || strcmp(type, "无障碍") == 0)
        return true;
    return false;
}
bool Validator::checkSpaceStatus(char status[])
{
    if (strcmp(status, "空闲") == 0 || strcmp(status, "已预约") == 0 ||
        strcmp(status, "已占用") == 0 || strcmp(status, "维修中") == 0)
        return true;
    return false;
}

void safeInput(char arr[], int maxChar)
{
    while (true)
    {
        std::cin.getline(arr, maxChar);

        if (!std::cin.fail())
            break;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "输入过长，最多只能输入" << maxChar - 1 << "个字符，请重新输入：";
    }
}