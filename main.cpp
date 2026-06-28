#include "TimeTool.h"
#include <iostream>
int main()
{
    char a[30] = {};
    TimeTool::generateTimeStamp(a);
    std::cout << a << std::endl;
    TimeTool::getCurrentTime(a);
    std::cout << a << std::endl;
    std::cout << TimeTool::calculateHours((char *)"1782642575", (char *)"1782647575") << std::endl;
    std::cout << TimeTool::isBeforeOneHour((char *)"1782642575", (char *)"1782647575") << std::endl;
    return 0;
}