#include "calculator.h"

Calculator::Calculator(){}

double Calculator::CalcMaterialWeight(double area, double expence)
{
    return area * expence;
}

double Calculator::CalcMaterialCost(double area, double expence, double price)
{
    _primeCost += CalcMaterialWeight(area, expence) * price;
    return CalcMaterialWeight(area, expence) * price;
}

double Calculator::GetPrimeCost()
{
    return _primeCost;
}

double Calculator::GetTotalCost(double koeff)
{
    return _primeCost * koeff;
}
