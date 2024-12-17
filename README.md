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
- Visual Alerts: Displays distance information and proximity warnings through LCD display.
- Audio Feedback: Emits beeping sounds that increase in frequency as the vehicle approaches an obstacle.
- Multi-Sensor Integration: Supports multiple ultrasonic sensors for comprehensive environmental coverage.
- USART: Exposes information useful for debugging through USART.

### **Block Diagram**
- TBD

## **Hardware Design**

### **Components**  
| Component                  | Quantity | Description                                   |
|----------------------------|:--------:|-----------------------------------------------|
| Arduino Uno                |    1     | Microcontroller for managing system state     |
| LCD Display                |    1     | Display information like measured distances   |
| Potentiometer 10 K         |    1     | Controls the contrast of LCD                  |
| Speaker                    |    1     | Indicates distance through beeps frequency    |
| Pushbutton                 |    1     | Toggle metric - imperial distance on LCD      |
| Resistors (220 K)          |    2     | For components                                |
| Breadboard & Wires         |    1     | For circuit                                   |
| HC-SR04 Ultrasonic Sensor  |    2     | Measure distances                             |
| Cable USB-A - USB-B        |    1     | Power, developing, debugging                  |

### Diagrams
- TBD

## **Software Design**  
- **IDE**: Visual Studio Code, PlatformIO
- **Libraries**: Arduino, LiquidCrystal
- **Planned Functionalities**:
 1. Real-Time Obstacle Detection: Continuously monitor the surroundings using ultrasonic sensors to detect obstacles within a specified range.
 2. Accurate Distance Calculation: Measure and display the precise distance to nearby objects, updating in real-time.
 3. Proximity Alerts:
 - Visual Feedback: LCD display to show distance and proximity levels.
 - Audio Alerts: Emit beeps or tones that increase in frequency as the vehicle approaches an obstacle.
 4. Multi-Sensor Data Fusion: Integrate data from multiple ultrasonic sensors to cover a broader detection area, ensuring comprehensive monitoring.
 5. Data Logging: Expose sensor data for analysis through USART for debugging purposes.

## **Setup**  
- TBD

## **Conclusions**

## **Resources**  
### **Hardware Resources**  
- Arduino Uno Datasheet: [https://www.arduino.cc/en/main/arduinoBoardUno](https://www.arduino.cc/en/main/arduinoBoardUno)

### **Software Resources**  
- PlatformIO: [https://platformio.org](https://platformio.org)  
