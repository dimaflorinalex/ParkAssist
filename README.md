# Park Assist based on Ultrasonic Sensors
## Dima Florin-Alexandru - Group 362
### Faculty of Mathematics and Computer Science, University of Bucharest

## **Introduction**

This project focuses on developing a Park Assist System using ultrasonic sensors to facilitate safe and accurate vehicle parking. The system utilizes multiple ultrasonic sensors to detect nearby obstacles, measure distances, and provide real-time feedback to the driver. By continuously monitoring the environment, the system helps prevent collisions, particularly in tight parking spaces.

The core of this project involves integrating ultrasonic sensors with a microcontroller to process distance data and trigger visual or audio alerts. This implementation showcases essential robotics principles, including sensor interfacing, signal processing, and decision-making algorithms, making it an ideal introduction to practical robotic applications in automotive systems.

## **Overview**

### **Features**
- Obstacle Detection: Uses ultrasonic sensors to detect obstacles within a defined range.
- Distance Measurement: Provides accurate real-time distance readings to nearby objects.
- Visual Alerts: Displays distance information through LCD display and proximity warnings through LED.
- Audio Feedback: Emits beeping sounds that increase in frequency as the vehicle approaches an obstacle.
- Toggle Audio Feedback: Enable or disable audio feedback by pressing the button.
- Multi-Sensor Integration: Supports multiple ultrasonic sensors for comprehensive environmental coverage.
- USART: Exposes information useful for debugging through USART.

### **Demo**
[![Video Demo](http://img.youtube.com/vi/Rr5viN0jYqA/0.jpg)](https://www.youtube.com/watch?v=Rr5viN0jYqA)

### **Block Diagram**
[![Block Diagram](https://i.ibb.co/Jxrh09D/Block-Diagram.png)](https://i.ibb.co/Jxrh09D/Block-Diagram.png)

## **Hardware Design**

### **Bill of Materials**  
| Component                  | Quantity | Description                                   |
|----------------------------|:--------:|-----------------------------------------------|
| Arduino Uno                |    1     | Microcontroller for managing system state     |
| LCD Display                |    1     | Display information like measured distances   |
| Potentiometer 10 K         |    1     | Controls the contrast of LCD                  |
| Speaker                    |    1     | Indicates distance through beeps frequency    |
| Pushbutton                 |    1     | Toggle metric - imperial distance on LCD      |
| Resistors (220 K)          |    3     | For components                                |
| Breadboard & Wires         |    1     | For circuit                                   |
| HC-SR04 Ultrasonic Sensor  |    2     | Measure distances                             |
| Red LED                    |    1     | Visual alert (proximity warning)              |
| Cable USB-A - USB-B        |    1     | Power, developing, debugging                  |

### Components Diagram
[![Components Diagram](https://i.ibb.co/3rVMYy4/Components-Diagram.png)](https://i.ibb.co/3rVMYy4/Components-Diagram.png)

### Electric Diagram
[![Electric Diagram](https://i.ibb.co/rQQjdmy/Electric-Diagram.png)](https://i.ibb.co/rQQjdmy/Electric-Diagram.png)

## **Software Design**  
- **IDE**: Visual Studio Code, PlatformIO
- **Libraries**: Arduino, LiquidCrystal, Wire
- **Planned Functionalities**:
 1. Real-Time Obstacle Detection: Continuously monitor the surroundings using ultrasonic sensors to detect obstacles within a specified range.
 2. Accurate Distance Calculation: Measure and display the precise distance to nearby objects, updating in real-time.
 3. Proximity Alerts:
 - Visual Feedback: LCD display to show distance and LED for proximity warnings.
 - Audio Alerts: Emit beeps or tones that increase in frequency as the vehicle approaches an obstacle.
 4. Toggle Audio Alerts: Button enables/disables audio feedback.
 5. Multi-Sensor Data Fusion: Integrate data from multiple ultrasonic sensors to cover a broader detection area, ensuring comprehensive monitoring.
 6. Data Logging: Expose sensor data for analysis through USART for debugging purposes.

## **Setup**  
[![Setup Photo 1](https://i.ibb.co/ysqXLWy/20250106-182804.jpg)](https://i.ibb.co/ysqXLWy/20250106-182804.jpg)
[![Setup Photo 2](https://i.ibb.co/QYCDRWy/20250106-182736.jpg)](https://i.ibb.co/QYCDRWy/20250106-182736.jpg)
[![Setup Photo 3](https://i.ibb.co/gyy3V0c/20250106-182714.jpg)](https://i.ibb.co/gyy3V0c/20250106-182714.jpg)
[![Setup Photo 4](https://i.ibb.co/ZSDVfY8/20250106-182705.jpg)](https://i.ibb.co/ZSDVfY8/20250106-182705.jpg)
[![Setup Photo 5](https://i.ibb.co/y5kF3NG/20250106-182654.jpg)](https://i.ibb.co/y5kF3NG/20250106-182654.jpg)

## **Conclusions**
This project demonstrates a solution for vehicle parking assistance, leveraging ultrasonic sensors to enhance safety and precision in parking scenarios.

It is a practical and versatile application of embedded and sensor technologies, addressing a real-world problem while showcasing core principles of robotics.

## **Resources**
### **Hardware Resources**
- [Arduino Uno Datasheet](https://www.arduino.cc/en/main/arduinoBoardUno)
- [HC-SR04 Ultrasonic Sensor Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [LCD-016N002B-CFH-ET LCD Display Datasheet](https://www.vishay.com/docs/37484/lcd016n002bcfhet.pdf)
- [Active Passive Buzzer](https://components101.com/misc/buzzer-pinout-working-datasheet)

### **Software Resources**
- [PlatformIO](https://platformio.org)
- [Visual Studio Code](https://code.visualstudio.com/)

### **Laboratory Resources**
- [Laboratorul 0: Aplicații introductive](https://robotics.unibuc.ro/dokuwiki/doku.php?id=start:labs:lab0)
- [Laboratorul 1: USART. Debugging](https://robotics.unibuc.ro/dokuwiki/doku.php?id=start:labs:lab1)
- [Laboratorul 2: Întreruperi. Timere](https://robotics.unibuc.ro/dokuwiki/doku.php?id=start:labs:lab2)
- [Laboratorul 3: Timere. PWM](https://robotics.unibuc.ro/dokuwiki/doku.php?id=start:labs:lab3)
- [Laboratorul 4: ADC](https://robotics.unibuc.ro/dokuwiki/doku.php?id=start:labs:lab4)
