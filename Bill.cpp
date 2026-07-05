#include "Bill.h"
#include "Time.h"
#include <cstring>
#include "TimeTool.h"
#include <iostream>
#include <iomanip>

void Bill::display()
{
	std::cout << "账单编号：" << billId << std::endl;
	std::cout << "车位编号：" << spaceId << std::endl;
	std::cout << "车牌号：" << plateNumber << std::endl;

	char time[20];
	time_t stampTime = TimeTool::charArrayToLongLong(inTime);
	tm *nowTime = localtime(&stampTime);
	std::sprintf(time,
				 "%04d-%02d-%02d %02d:%02d",
				 nowTime->tm_year + 1900,
				 nowTime->tm_mon + 1,
				 nowTime->tm_mday,
				 nowTime->tm_hour,
				 nowTime->tm_min);

	std::cout << "进场时间：" << time << std::endl;

	stampTime = TimeTool::charArrayToLongLong(outTime);
	nowTime = localtime(&stampTime);
	std::sprintf(time,
				 "%04d-%02d-%02d %02d:%02d",
				 nowTime->tm_year + 1900,
				 nowTime->tm_mon + 1,
				 nowTime->tm_mday,
				 nowTime->tm_hour,
				 nowTime->tm_min);

	std::cout << "出场时间：" << time << std::endl;

	std::cout << "停车时长：" << std::fixed << std::setprecision(2) << hours << std::endl;
	std::cout << "费用：" << std::fixed << std::setprecision(2) << fee << std::endl;
}

bool Bill::isSameSpaceId(char id[])
{
	return strcmp(id, spaceId) == 0;
}

bool Bill::isSamePlateNumber(char plate[])
{
	return strcmp(plate, plateNumber) == 0;
}

double Bill::calculateFee()
{
	double h = TimeTool::calculateHours(inTime, outTime);
	double result = 5.0;
	if ((1.0 - h) >= 1e-9)
		return result;
	else
	{
		if ((h - int(h)) <= 1e-9)
			return result + (int(h) - 1) * 2.0;
		else
		{
			return result + int(h) * 2.0;
		}
	}
}