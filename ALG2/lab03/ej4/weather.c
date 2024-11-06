/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include <stdlib.h>
#include "weather.h"

static const int AMOUNT_OF_WEATHER_VARS = 6;

Weather weather_from_file(FILE *file)
{
	Weather weather;

	// hace dos cosas, asigna a los atributos de weather y suma +1 dependiendo de cuantos datos va encontrando
	int res = fscanf(file, EXPECTED_WEATHER_FILE_FORMAT, &weather._average_temp, &weather._max_temp, &weather._min_temp, &weather._pressure, &weather._moisture, &weather._rainfall);
	if (res != AMOUNT_OF_WEATHER_VARS)
	{
		fprintf(stderr, "Invalid weather data\n");
		exit(EXIT_FAILURE);
	}
	return weather;
}

void weather_to_file(FILE *file, Weather weather)
{
	fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp,
			weather._max_temp, weather._min_temp, weather._pressure, weather._moisture, weather._rainfall);
}
