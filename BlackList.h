#ifndef BLACKLIST_H
#define BLACKLIST_H

class BlackNode
{
public:
    char plateNumber[20];
    BlackNode *next;
    BlackNode();
};

class BlackList
{
private:
    BlackNode *head;
    int length;

public:
    BlackList();
    void addToBlackList(char number[]);         // 将车牌加入黑名单
    void deleteBlackPlateNumber(char number[]); // 将车牌从黑名单删除
    bool findBlackPlateNumber(char number[]);   // 该车牌是否在黑名单中
    void displayBlackList();                    // 显示所有黑名单车牌
    void loadFromFile();
    void saveToFile();
    ~BlackList();
};

#endif
