# RP2040-Zero-liquid-temperature-sensor
Simple program and PS script to allow monitoring of liquid temps in liquid cooling PCs

## Usage

1. Make sure that your liquid cooling loop has a temp probe installed. For my project I used this [Phobya G1/4" Inline Temperature Sensor](https://www.amazon.com/,Phobya-Inline-Temperature-Sensor-Nickel/dp/B00414VYEC), but any will be fine.

2. Buy yourself a [RP2040 Zero](https://www.adafruit.com/product/3500). This is a board I used, but feel free to use a different one and change the code as needed. **RP2040 Zero** is very cool as it can natively output serial data via USB, and it can be seen in Windows as COM device.

3. Solder/Connect a 10k Ohm resistor between pin **GPIO26** and **3.3V** and your thermal sensor to **GPIO26** and **GND**.
![IMG_0486_preview](https://github.com/user-attachments/assets/95b9640a-4baf-4881-8fc1-284d32e93717)

4. Flash [rp2040_temp_sensor.ino](src/rp2040_temp_sensor.ino) into your board.

5. Connect temp probe from your liquid cooling loop into your board. You remembered to add it to your loop, right? :)

## Reading the output from the **RP2040 Zero**
You can use the tool [PuTTY]([www.putty.org](https://www.chiark.greenend.org.uk/~sgtatham/putty/) to read the output. On PuTTY, switch the connection type to `Serial`, set the `Serial Line` to your COM port (COM3, for instance), and verify that the speed is `9600`.  
When you click open, it should be reading out values.

## Control PC fans using temp sensor - PowerShell
1. I use tool called [Fan Control](https://github.com/Rem0o/FanControl.Releases). It's a great free tool that accepts file as mock "sensor". We can log our liquid temp into file and **Fan Control** will control our fans using this file. Download the tool and create new custom sensor.
2. Launch Windows Scheduler and create new Task:
- basic: administrator privileges + launch regardless of logged in user
- trigger: on user login
- actions: launch program - powershell, arguments: -command &{path-to\Trinket-M0-liquid-temperature-sensor\src\WatchLiquidTemp.ps1 -filePath 'path-to\FanControl\LiquidTemp.sensor' -com COM5} (change COM5 to whatever is seen by your system)
3. Save your task and restart system. After reboot your custom sensor should display values from liquid temp sensor.
  
## Control PC fans using temp sensor - FanControl Plugin
1. I use tool called [Fan Control](https://github.com/Rem0o/FanControl.Releases). Download latest plugin DLL from [Releases](https://github.com/Naata/Trinket-M0-liquid-temperature-sensor/releases). Use instructions from [FanControl Wiki](https://github.com/Rem0o/FanControl.Releases/wiki/Plugins#requirements).
2. Set environment variable SENSOR_COM_PORT to whichever com port your trinket is connected to
2. Works! :)

