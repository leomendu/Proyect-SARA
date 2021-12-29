All files for ESP32 firmware development using esp-idf extension for Visual Studio Code.

Here you can find four C files: main, mqtt, uart and wifi. These are all the files containing functions and variables used in the S.A.R.A. Proyect.

# main
main file has the core program functions, such as motor activation and configuration variables.

# mqtt
mqtt file has the mqtt handling functions, all the mqtt events and string processing for device configuration are handled here. When adding configurations, this file has to be modified.

# uart
uart file has all the communications functions using the UART, for communicating with other devices via cable.

# wifi
wifi file has all the configurations for wifi connecting, as well as smart config functions using ESP Touch. If at any given moment you need to give device IP with SSID and password, this is the file that has to be modified.
