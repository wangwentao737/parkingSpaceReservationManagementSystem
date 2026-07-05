#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H

class ParkingSpace
{
public:
	char spaceId[20];
	char location[20];
	char type[20];
	char status[20]; // 状态：空闲/已预约/已占用/维修中

	void input();			  // 输入车位信息
	void display();			  // 显示车位信息
	void modify();			  // 修改车位信息
	bool isFree();			  // 判断车位是否空闲
	bool isSameId(char id[]); // 判断车位编号是否相同
};

#endif
