#include "array_helpers.h"
#include "weather.h"
#include <math.h>

float minTempMin(WeatherTable a)
{
    float minTemp = INFINITY;
    for (unsigned int year = 0u; year < YEARS; ++year)
    {
        for (month_t month = january; month <= december; ++month)
        {
            for (unsigned int day = 0u; day < DAYS; ++day)
            {
                float aux = a[year][month][day]._min_temp;
                if (aux < minTemp)
                {
                    minTemp = aux;
                }
            }
        }
    }
    return minTemp;
}

void maxTempEveryYear(WeatherTable a, int output[YEARS])
{

    for (unsigned int year = 0u; year < YEARS; ++year)
    {
        float maxTemp = -INFINITY;
        for (month_t month = january; month <= december; ++month)
        {
            for (unsigned int day = 0u; day < DAYS; ++day)
            {
                float aux = a[year][month][day]._max_temp;
                if (aux > maxTemp)
                {
                    maxTemp = aux;
                }
            }
        }
        output[year] = maxTemp;
    }
}

void monthOfMostRainfall(WeatherTable a, unsigned int output[YEARS][MONTHS])
{
    for (unsigned int year = 0u; year < YEARS; ++year)
    {
        for (month_t month = january; month <= december; ++month)
        {
            float maxRainfall = -INFINITY;
            for (unsigned int day = 0u; day < DAYS; ++day)
            {
                unsigned int aux = a[year][month][day]._rainfall;
                if (aux > maxRainfall)
                {
                    maxRainfall = aux;
                }
            }
            output[year][month] = maxRainfall;
        }
    }
}