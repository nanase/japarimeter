#ifndef __BMP280_MACROS_H
#define __BMP280_MACROS_H

#define BMP280_MAX_PRESSURE (1100 * 25600)
#define BMP280_MIN_PRESSURE (300 * 25600)

#define BMP280_MAX_TEMPERATURE (85 * 100)
#define BMP280_MIN_TEMPERATURE (-40 * 100)

#define BMP280_MAX_HUMIDITY (100 * 1024)
#define BMP280_MIN_HUMIDITY (0)

#define fixedPressureToHectoPa(pressure) ((pressure) / 25600.0)
#define fixedTemperatureToTemperature(temperature) ((temperature) / 100.0)
#define fixedHumidityToHumidity(humidity) ((humidity) / 1024.0)

#define validFixedPressure(pressure) (((pressure) <= (BMP280_MAX_PRESSURE)) && ((pressure) >= (BMP280_MIN_PRESSURE)))
#define validFixedTemperature(temperature) \
  ((temperature) <= BMP280_MAX_TEMPERATURE && (temperature) >= BMP280_MIN_TEMPERATURE)
#define validFixedHumidity(humidity) ((humidity) <= BMP280_MAX_HUMIDITY && (humidity) >= BMP280_MIN_HUMIDITY)

#endif
