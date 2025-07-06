# Hardware

To start off, you will need the following hardware:

- A **microcontroller** programmable using C++. This can be an Arduino, Seeeduino or similar. 
- **Lego Mindstorms NXT or EV3 modules**. All motors are compatible, but for the sensors only the distance, touch and colour/light work. 
- **RJ12 off-centre sockets or Lego Mindstorms cables** you are willing to strip
- **2 10kOhm resistors**
- **Wires**

When using the motors, it is advised to also use an **L298 motor driver** with a seperate **9V battery**. <br>
The reason for this is that the motors draw a current of more than 0.9A when one locks up (gets stuck). This much current can fry most microcontrollers. <br>
Also: don't power your microcontroller in 2 ways at the same time (like with the battery and a PC connection), as this could also fry it.
