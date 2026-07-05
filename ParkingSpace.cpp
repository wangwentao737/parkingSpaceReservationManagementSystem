#include "ParkingSpace.h"
#include "Validator.h"
#include <iostream>
#include <cstring>

void ParkingSpace::input()
{
	std::cout << "请输入车位编号：";
	safeInput(this->spaceId, 20);

	std::cout << "请输入车位区域：";
	safeInput(this->location, 20);

	std::cout << "请输入车位类型：";
	safeInput(this->type, 20);
	while (!Validator::checkSpaceType(this->type))
	{
		std::cout << "输入有误，请重新输入车位类型：";
		safeInput(this->type, 20);
	}

	std::cout << "请输入车位状态：";
	safeInput(this->status, 20);
	while (!Validator::checkSpaceStatus(this->status))
	{
		std::cout << "输入有误，请重新输入车位状态：";
		safeInput(this->status, 20);
	}
}

void ParkingSpace::display()
{
	std::cout << "车位编号:" << spaceId << std::endl;
	std::cout << "车位区域:" << location << std::endl;
	std::cout << "车位类型:" << type << std::endl;
	std::cout << "车位状态:" << status << std::endl;
}

void ParkingSpace::modify()
{
	char num[2];
	do
	{
		this->display();
		std::cout << "请检测输入的信息是否有误，无误输入0，如需更改输入对应数字进行修改(1:车位编号，2:车位区域，3:车位类型，4:车位状态)：";
		safeInput(num, 2);
		if (strcmp(num, "1") == 0)
		{
			std::cout << "请输入你要修改的车位编号";
			safeInput(this->spaceId, 20);
		}
		else if (strcmp(num, "2") == 0)
		{
			std::cout << "请输入你要修改的车位区域";
			safeInput(this->location, 20);
		}
		else if (strcmp(num, "3") == 0)
		{
			std::cout << "请输入你要修改的车位类型";
			safeInput(this->type, 20);
			while (!Validator::checkSpaceType(this->type))
			{
				std::cout << "输入有误，请重新输入车位类型：";
				safeInput(this->type, 20);
			}
		}
		else if (strcmp(num, "4") == 0)
		{
			std::cout << "请输入你要修改的车位状态";
			safeInput(this->status, 20);
			while (!Validator::checkSpaceType(this->status))
			{
				std::cout << "输入有误，请重新输入车位状态：";
				safeInput(this->status, 20);
			}
		}
		else if (strcmp(num, "0") == 0)
			break;
	} while (true);
}

bool ParkingSpace::isFree()
{
	return strcmp(status, "空闲") == 0;
}

bool ParkingSpace::isSameId(char id[])
{
	return strcmp(id, spaceId) == 0;
}
