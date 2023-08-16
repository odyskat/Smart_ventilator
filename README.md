# Smart_ventilator
## Abstract:
Smart ventilator designed on  window metal bar. Aims to reduce humidity by renewing the air inside a 10 m^3 room  with high humidity at a ~210 m^3/h rate. Needs less than 8 min to renew the air inside the room one time.
Uses a reed switch positioned in the window opening to know when the window is open, then it checks for humidity changes utilizing the shtc3 sensor, and if it reed increased humidity it stars the fans in full power mode until the humidity goes back to normal (previous) levels. When the window is closed, the device goes automatically back to sleep.
The device is powered by a Xiaomi 10000 mAh power bank with two USB A outputs at 5v and 1A, and the fan operates at 12 volts 0.1 A each. For converting the voltage it utilizes a 
variable boost converter set at 12V output. The converter includes a convenient micro USB-in port and connects to the power bank with a standard USB A to micro B cable.

## Device "skeleton":
The device is made from simple PLA or ABS plastic and optionally TPU for the gaskets, everything is 3d printed using simple ender printers. It includes a sensor stand in the back for fastening the sensor, a cable management bay, cable out holes **(which must be filled with standard silicon to achieve water resistance.)**, and screw joints which must be embedded with threaded inserts for plastic. It hangs from a top window metal bar. 
The battery sits outside the casing for easy access and recharging. In the future, a solar panel for battery charging will be added to make the system completely autonomous.


Renders of the device :

![Fan_module_with_Bathroom_window_and_fans_v3_2023-Aug-16_12-37-50PM-000_CustomizedView10508488103_jpg](https://github.com/odyskat/Smart_ventilator/assets/114591654/fc47e3b7-e825-4aae-a517-96fcdb0f5678)


![Fan_module_with_Bathroom_window_and_fans_v3_2023-Aug-16_12-38-32PM-000_CustomizedView15031821479_jpg](https://github.com/odyskat/Smart_ventilator/assets/114591654/2426c282-7def-4fcd-9d85-35ce70e9221f)

![Fan_module_with_Bathroom_window_and_fans_v3_2023-Aug-16_12-45-48PM-000_CustomizedView307875928_jpg](https://github.com/odyskat/Smart_ventilator/assets/114591654/703a993a-dd3a-4e27-a6ee-15a4fbae1763)

![Fan_module_with_Bathroom_window_and_fans_v3_2023-Aug-16_12-37-13PM-000_CustomizedView29614088936_jpg](https://github.com/odyskat/Smart_ventilator/assets/114591654/d999ad84-4bbd-4eb5-886f-008a53f8e83a)
## Electronics
### Materials:
1. Arduino nano
2. Adafruit shtc3 sensor
3. DC-DC step up converter
4. Xiaomi redmi power bank 10000 mAh
5. Reed switch
6. 4x Arctic f8 80 mm pst fans



### Wiring:

![Smart ventilator arduino nano wiring_bb](https://github.com/odyskat/Smart_ventilator/assets/114591654/3c27e3be-49cf-438b-ab2f-b38158155270)

![Smart ventilator arduino nano wiring_schem](https://github.com/odyskat/Smart_ventilator/assets/114591654/d03f0cbb-531e-458b-bf0d-97257c2a80df)



 
