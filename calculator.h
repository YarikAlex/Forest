#pragma once


class Calculator
{
public:
    Calculator();
    double CalcMaterialWeight(double area, double expence);
    double CalcMaterialCost(double area, double expence, double price);
    double GetPrimeCost();
    double GetTotalCost(double koeff);
private:
    double _primeCost = 0;
};

