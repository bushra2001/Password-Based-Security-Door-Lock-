# Task Description:
Implement a microcontroller/microprocessor-based application to operate a password-protected locker
with machine-to-machine (M2M) communication incorporated in the design. Password is entered
through a keypad and a digital display (LCD or seven-segment display) is used to show the current
status of the locker.
If the locker door is latched, password can be entered by the user to unlatch it. The password entered,
by the user, is sent by the microcontroller (which we call the transmitter microcontroller) to another
serially interfaced (UART) microcontroller (called the receiver microcontroller). At the receiver end,
password entered is matched to the correct password of the respective locker. On ‘successful match’,
a servo-motor interfaced with the receiver microcontroller is used to latch or unlatch the locker door.
A dip switch/push button or any other mechanism can be used to latch the door-lock at the receiver
microcontroller when the user wants it, thus updating the status of the locker at the transmitter end.
The design should be robust enough to handle incorrect passwords entered. The design can be
enhanced as per the vision of the design team, however, keeping the basic functionality and
requirements in perspective.

## Requirements:
### Hardware Requirement:
- AVR kit
- Jumper Wires
- Servomotor
- Keypad

### Software Requirment:
- Atmel Studio
- Proteus
- Khazama

## Hardware Implementation:
- Build Receiver Code and Transmitter code on Atmel Studio.
- From Khazama, upload hex files on AVR kits.
- Connect wires as shown in Proteus.
- Again connect from CPU to power AVR kits.

# Design Decisions and Implementations:

## Transmitter:

### Keypad Interfacing:
Keypad is interfaced with the 4 MSB bits of DDRD register. The MSBs are then right shifted 4 times and AND masked to get an 8 bit number which is then used to get the index of a lookup array. The index of the lookup array then tells which key is pressed.

### Transmission of Key Pressed:
 The pressed key is then transmitted to the receiver through USART port. PD0 and PD1 are used to connect the transmitter and receiver with each other. The transmitter first transmits to the receiver in order to initiate handshaking. And then when it is acknowledged by the receiver it then puts the key pressed into UDR register and its contents are then transmitted through pin PD0 serially. 

### Reception of Door Status: 
The status of door transmitted by the receiver is received by the transmitter through pin PD1 which is then saved into variable receiveData.

### Display of Door Status On 7-Segement:
The contents of variable receiveData are then sent to PORT A register which is declared as output register. It is then connected to the seven segment dislay where the door status is displayed.

## Receiver:

### Reception of Password: 

The password sent by the transmitter is received through pin PD1 by the receiver.

### Matching of Received Password with Original Password: 
The password is matched with the original password.

### Rotation of Servomotor and Door Status: 
If the password matches and the push button is not pressed the servomotor rotates to 90 degrees and the door is unlatched. A variable status is updated and contains the new status of the door.

### Transmission of Door Status: 
The status of the door is then transmitted back to the transmitter through pin PD0.

### Use of Push Button to Latch the Door:
If the push button is pressed the door is latched and the status of door is updated to C which means closed.

## Simulation:
I have used [Proteus](https://www.labcenter.com/) for simulation. 

### PCB Semantics:
![PCB_Semantics](https://user-images.githubusercontent.com/61081924/182027131-7db4fd18-1716-4019-90a9-66a2846a846b.jpeg)

### Case I : Wrong Password. The door remains latched. Seven Segment Display shows C which means door is closed.
![Case_I](https://user-images.githubusercontent.com/61081924/182027194-0fc9e66b-4e28-4430-ab7c-3688def09cb8.jpeg)

### Case II : Correct Password. The door unlatches. Servomotor rotates. Seven Segment Display shows O which means door is open.
![CASE_II](https://user-images.githubusercontent.com/61081924/182027224-6ed38efd-404b-4cef-9d0f-5a1949ba38e9.jpeg)

### Case III: Push button is pressed to latch the door. The Seven Segment display shows C which means the door is closed again.
![CASE_III](https://user-images.githubusercontent.com/61081924/182027244-8f82a6a4-3aac-4923-a494-7826dc788337.jpeg)

## AVR Kit Implementation:
![CASE_IV](https://user-images.githubusercontent.com/61081924/182027284-55294689-f820-4d74-b973-ab4e037b37fd.jpeg)

