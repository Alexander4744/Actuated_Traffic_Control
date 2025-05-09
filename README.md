# Traffic Light System with Sensors  

## **Overview**  
This project implements an intelligent traffic light system for intersections, using sensors (buttons) to detect vehicle presence and dynamically adjust green light durations. The system was first modeled in Proteus for simulation, then physically built using LEDs, buttons, and an STM32 F401RE development board.  

---

## **Hardware Components**  
1. **Development Board**: STM32 F401RE (ARM Cortex-M4 microcontroller).  
2. **Sensors**: Buttons connected to GPIO pins, simulated via external interrupts.  
   - Used to detect vehicles on major/minor roads (left/forward lanes).  
3. **LEDs**:  
   - Represent traffic light colors (red, yellow, green) for major and minor directions.  
   - Controlled via GPIO registers (e.g., `GPIOC->ODR` for major lights).  

---

## **Key Features**  
1. **Traffic Management**:  
   - **Major/Minor Roads**: Alternates priority based on detected demand.  
   - **Light States**:  
     - **Green**: Allows traffic for adjustable durations.  
     - **Yellow**: Transition to red (1 second).  
     - **Red**: Mandatory stop.  

2. **Queue System**:  
   - Vehicle requests from sensors are stored in a circular queue (`queue[MAX_SIZE]`).  
   - Queue functions: `enqueue()`, `dequeue()`, `isEmpty()`, `isFull()`.  
   - Prevents duplicate requests for the same direction.  

![Queue](Images\Queue_In_Action.gif)

3. **Dynamic Adaptation**:  
   - Green light duration (`green_duration`) extends if vehicles are waiting (max 12 sec, min 1 sec).  
   - Sensor (button) interrupts update the queue and adjust timing.  

![Green Extension](Images\Green_Extension.gif)

4. **Testing Mode**:  
   - A button on `PA0` triggers full light cycles (`MAJOR_TURNS` and `MINOR_TURNS`) for debugging.  

---

## **Program Flow**  
1. **Initialization**:  
   - Configures system clock and GPIO (LEDs as outputs, buttons as interrupt inputs).  
2. **Main Loop**:  
   - Checks queue status. If not empty, executes the next request (e.g., `MAJOR_FORWARD`).  
   - Removes completed requests (`dequeue()`).  
3. **Interrupts**:  
   - Button presses add requests (`enqueue()`) and extend green lights if active.  

See program [Here](Actuated_Traffic_Controller\Core\Src\main.c)

---

## **Proteus Simulation & Hardware Implementation**  
- **Simulation**:  
  - Proteus virtual components (LEDs, buttons) validated the logic.  
  
  ![Proteus Simulation Image](Images\Proteus_Simulation.png)
   The proteus simulation file is Actuated_Traffic_Lights.pdsprj - [Here](Actuated_Traffic_Lights.pdsprj)

- **Physical Build**:  
  - LEDs connected to GPIOB/GPIOC.  
  - Buttons on PORTA (pins 1, 4, 5, 6) with pull-down resistors.  

![Physical Build](Images\Physical_Build.jpeg)

---

## **Conclusion**  
This project demonstrates core features of a smart traffic light system:  
- **Dynamic traffic management** based on real-time demand.  
- **Robustness** via queue deduplication and time limits.  
- **Scalability**: Can integrate real sensors (IR/ultrasonic) and network monitoring.  

**Applications**: Urban intersections, adaptive traffic systems, smart city infrastructure.  

--- 

*Built with STM32CubeIDE | Tested on STM32F401RE*
