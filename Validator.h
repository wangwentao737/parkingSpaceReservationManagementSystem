#ifndef VALIDATOR_H
#define VALIDATOR_H

class Validator
{
public:
    static bool checkPlateNumber(char plate[]);
    static bool checkPhone(char phone[]);
    static bool checkSpaceType(char type[]);
    static bool checkSpaceStatus(char status[]);
};

void safeInput(char in[], int maxChar);
#endif
