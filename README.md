# Bus-Stand
Smart temperature and presence controlled bus stop fan mini model

This project is an Arduino based smart fan system designed for bus stops. The fan activates only when the ambient temperature exceeds a set threshold and a person is detected under the bus shelter, improving comfort while reducing unnecessary energy use.
How It Works

A temperature sensor continuously measures ambient temperature

A PIR motion sensor detects whether someone is standing under the bus stop

The fan turns on only if both conditions are met:

Temperature is above 27°C

Motion is detected. 

When motion stops, the fan remains on for 20 seconds before turning off. If the temperature drops below the threshold, the fan shuts off immediately

Why This Matters

Traditional outdoor fans often run continuously, wasting energy even when no one is present. This system reduces power consumption while still prioritizing rider comfort during hot weather.

Hardware Used

Arduino Uno (or compatible)

PIR motion sensor

Analog temperature sensor (TMP36 or similar)

Servo motor (represents fan control)

External power supply

Key Features

Dual condition activation using temperature and motion

Automatic shutdown delay to avoid rapid on off cycling

Immediate safety shutoff when temperature drops

Serial debugging for real time monitoring

Possible Improvements

Replace servo with a relay for real fan control

Add humidity sensing for better comfort modeling

Solar power integration for outdoor deployment

Data logging for usage and energy analysis
