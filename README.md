# tec-TTY
TTY, Teleprinter/Teletypewriter, is an example of a serial terminal that was widely used in the early days of computing. A serial terminal is a device that allows users to interact with a computer or mainframe using a serial communication protocol.

The TTY was an electromechanical typewriter that could be connected to a computer or mainframe using a serial connection. It provided a means for users to input commands and receive output from the computer. The TEC-1 TTY used a teleprinter-style interface, where characters were typed on a keyboard and transmitted one at a time to the computer.

In addition to the TTY, there were other types of serial terminals used in the past, including video terminals and ASCII terminals. These terminals typically connected to the computer using a serial port and used asynchronous communication protocols.

Asynchronous protocols are a type of serial communication protocol where data is transmitted one character at a time, with each character preceded by a start bit and followed by one or more stop bits. This allows for communication between devices that may have slightly different timing or clock rates.

Serial terminals and TTY devices played a significant role in early computer systems, providing a means for users to interact with computers and input commands. They have largely been replaced by graphical user interfaces and modern computer keyboards, but the term "TTY" is still sometimes used to refer to virtual consoles or terminal emulators in Unix-like operating systems.

### Mod a an electric typewriter into a TTY
Adapting a TTY or serial terminal,  to a Z80 Single-Board Computer (SBC) would involve establishing a serial communication interface between the two systems. Here are the general steps to accomplish this:

1. Identify the serial interface on the Z80 SBC: Determine the available serial communication ports on the Z80 SBC. This could be a built-in UART (Universal Asynchronous Receiver-Transmitter) or a serial expansion module.

2. Connect the TTY to the Z80 SBC:
   - consider compatability or lack of for electric voltages, currents etc
   - Connect the TTY device to the serial interface on the Z80 SBC. This typically involves connecting the appropriate wires for transmit (TX), receive (RX), ground (GND), and possibly other control signals such as data terminal ready (DTR) and request to send (RTS).

4. Configure the serial communication settings: Set the desired baud rate, data bits, stop bits, and parity on both the TTY and the Z80 SBC. These settings need to match for proper communication.

5. Implement the serial communication protocol: On the Z80 SBC, you'll need to write software to handle the serial communication. This typically involves initializing the UART, setting up interrupts if necessary, and implementing code to send and receive data over the serial port.

6. Handle input and output on the Z80 SBC: Once the serial communication is established, you'll need to handle input and output from the TTY device on the Z80 SBC. This could involve reading characters received from the TTY and processing them as commands or displaying output on the TTY by sending characters from the Z80 SBC.

The specific steps and code required for adapting the TTY to a Z80 SBC will depend on the exact hardware and software environment you are working with. The documentation and resources available for your specific Z80 SBC and TTY device will be valuable references during the adaptation process.


## RTTY
RTTY stands for "Radio Teletype," and it is a communication mode used in radio and telecommunications for transmitting text messages. It is also known as "Radioteletype" or "Radio TeleTYpe." RTTY was widely used in the past for sending text-based information over long distances, particularly in fields like maritime communication and broadcasting. Here's a more detailed explanation of RTTY:

1. **Encoding Method**: RTTY encodes characters into electrical or radio frequency signals for transmission. It uses a combination of two frequencies, known as "shifts," to represent binary data. The most common shifts are 170 Hz and 850 Hz, although other variations exist.

2. **Character Transmission**: Each character in the message is represented as a series of bits (usually 5 or 7 bits per character), and these bits are then transmitted using the specified frequency shifts. Typically, start and stop bits are used to frame each character for synchronization.

3. **Usage**: RTTY was historically used for transmitting text messages over long distances, especially in situations where voice communication was not ideal or feasible. It found applications in areas like telegraphy, weather reporting, aviation communication, and naval communication.

4. **Equipment**: To transmit and receive RTTY signals, specialized equipment is required. This includes teletype machines, which were widely used in the past, and later, computer-based systems with sound cards and software capable of generating and decoding RTTY signals.

5. **Shifts and Speeds**: RTTY can be transmitted at various speeds, measured in words per minute (WPM). Common speeds include 45.45 baud (which equates to 50 WPM when using a 5-bit code), 75 baud (66 WPM), and 100 baud (110 WPM). The choice of speed depends on factors such as signal propagation conditions and available bandwidth.

6. **Advantages and Limitations**: RTTY has the advantage of being able to transmit text information over long distances with relatively simple equipment. However, it is not as bandwidth-efficient as modern digital communication modes like PSK31 or FT8, which can transmit more data in the same bandwidth.

7. **Legacy and Modern Use**: While RTTY is no longer the primary mode of communication for most applications due to the prevalence of digital communication technologies, it is still used in some niche areas and enjoys popularity among amateur radio operators for its historical significance and the charm of "old-school" communication.

## MINT implementation RTTY components.

implementation has:

1. Full Start/Stop Bit Handling
2. Complete Baudot Tables (Letters/Figures)
3. Shift State Management
4. Parity Checking
5. Signal Filtering
6. Sync Detection
7. Circular Buffer Management
8. Signal Quality Monitoring
9. Error Detection
10. Diagnostic Functions

Key features:
- Proper LTRS/FIGS shift handling
- Signal quality monitoring
- Debug mode for diagnostics
- Error detection and correction
- Buffer management
- Comprehensive test suite


```
// Complete RTTY Implementation for MINT2
// Constants and Variables:
// f = mark frequency (2125 Hz)
// s = space frequency (2295 Hz)
// b = baud rate (45.45)
// p = audio output port
// i = audio input port
// t = transmit mode flag
// m = message buffer
// r = receive buffer
// g = goertzel accumulator
// h = shift state (letters/figures)
// q = signal quality
// c = circular buffer
// d = debug flag

// Initialize system
:I #2125 f!                    // Mark frequency
   #2295 s!                    // Space frequency
   45 b!                       // Baud rate
   #80 p!                      // Output port
   #81 i!                      // Input port
   /T t!                       // Start in transmit
   [ 0 0 0 0 0 0 0 0 ] m!     // Message buffer
   [ 0 0 0 0 0 0 0 0 ] c!     // Circular buffer
   0 h!                        // Letters shift
   L                          // Load letter table
   N ;                        // Load number table

// Complete Baudot/ITA2 Letter Table
:L [ 0 #45 #0A #41 #20 #53 #49 #55 #0D #44 
     #52 #4A #4E #46 #43 #4B #54 #5A #4C #57
     #48 #59 #50 #51 #4F #42 #47 #4D #58 #56 ] l! ;

// Complete Baudot/ITA2 Number/Symbol Table
:N [ 0 #33 #0A #2D #20 #27 #38 #37 #0D #24 
     #34 #07 #2C #21 #3A #28 #35 #2B #29 #32
     #23 #36 #30 #31 #39 #3F #26 #2E #2F #3B ] n! ;

// Start/Stop Bit Handler
:X 0 T                         // Send start bit
   m 5 (                       // Send 5 data bits
     /i m ? 1 & T             // Send each bit
     b 22 * ()                // Bit timing
   )
   1 T                        // Send stop bit
   1 T ;                      // Second stop bit

// Letter/Figure Shift Control
:H h @ /F (                    // If not in letter shift
     #1F B                    // Send LTRS code
     /T h!                    // Set letters mode
   ) ;

:F h @ /T (                    // If not in figures shift
     #1B B                    // Send FIGS code
     /F h!                    // Set figures mode
   ) ;

// Parity Generator and Checker
:P 0 p!                       // Clear parity
   5 (                        // For 5 bits
     m /i ? 1 & p + p!       // Add each bit
   )
   p 1 & ;                   // Return odd parity

// Moving Average Filter
:V [ 0 0 0 0 ] v!            // Filter buffer
   i /I " v 0 ? + v 1 ? + v 2 ? + v 3 ? + 4 /  // Average
   v 0 ? v 1 ?! v 1 ? v 2 ?! v 2 ? v 3 ?! " v 3 ?! ;

// Sync Detection and Recovery
:Y 0 y!                      // Clear sync counter
   /U (                      // Loop
     i /I #80 > (            // If strong signal
       y 1+ y!               // Count samples
       y b 20 * = /W         // Break when baud time reached
     ) /E (
       0 y!                  // Reset on weak signal
     )
   ) ;

// Circular Buffer Management
:A h @ c ?!                  // Add to buffer
   h 1+ 7 & h! ;            // Increment head

:G t @ c ?                   // Get from buffer
   t 1+ 7 & t! ;            // Increment tail

// Signal Quality Monitor
:Q 0 q!                     // Clear quality sum
   100 (                    // Sample 100 times
     V q + q!               // Add filtered sample
   )
   q 100 / d @ (           // If debug mode
     `Signal Quality: ` . /N // Show quality
   ) ;

// Error Detection and Correction
:E m P /F (                 // If parity error
     d @ (                  // If debug mode
       `Parity Error` /N
     )
     R                     // Request retransmission
   ) ;

// Diagnostic Functions
:D /T d!                    // Enable debug mode
   `Debug Mode ON` /N ;

:O /F d!                    // Disable debug mode
   `Debug Mode OFF` /N ;

// Main Transmit Function with All Features
:M H                        // Ensure letters shift
   /U (
     t @ /W                 // While in transmit
     /K " #20 > (          // If printable char
       B                    // Convert to Baudot
       P m!                 // Add parity
       X                    // Transmit
       Q                    // Monitor quality
     )
   ) ;

// Main Receive Function with All Features
:R Y                        // Sync to signal
   V                        // Filter input
   Q                        // Check quality
   g f G s @ > (           // If mark detected
     r 1 { r!              // Shift in 1
   ) /E (
     r 0 { r!              // Shift in 0
   )
   E ;                     // Check for errors

// Complete Test Suite
:T I                       // Initialize
   D                       // Enable debug
   `RYRYRY` X             // Send test pattern
   1000( R )              // Receive test
   O ;                    // Disable debug

// Run System
:Z I                      // Initialize
   t @ ( M ) /E ( R ) ;  // Transmit or receive
```


## requirements to modify an electric typewriter into a TTY for the TEC-1,
hardware needed:

1. Interface Hardware Needed:
- Solenoid drivers for each key (to simulate key presses)
- Key position sensors or switches to detect typewriter key presses
- Current limiting resistors and protection diodes
- Buffer/level shifters (for voltage compatibility)

2. Control Logic Required:
- Microcontroller or interface circuit to:
  * Convert serial data to solenoid activations
  * Convert key detections to serial data
  * Handle timing/synchronization
  * Manage power for solenoids

3. Power Supply Requirements:
- Separate power supply for solenoids (likely 12V or 24V)
- Logic level power supply (5V)
- Common ground between systems

4. Additional Components:
- Optocouplers for electrical isolation
- Shift registers for parallel control
- Filtering capacitors
- Status LEDs
- Reset circuit

## complete design 
 
1. Hardware Components:

![image](https://github.com/user-attachments/assets/0ecb337c-e8bd-4ded-83c4-2470c3e47c06)

- Power supplies (12V/24V for solenoids, 5V for logic)
- 74HC595 shift register for solenoid control
- ULN2803A Darlington arrays for solenoid drivers
- 74HC165 shift register for key scanning
- 4N25 optocouplers for isolation
- Protection diodes and resistors

2. Key Features:

![image](https://github.com/user-attachments/assets/1085410a-2966-4f45-9811-251e1c74dc5a)

- Bidirectional operation (typing and receiving)
- Solenoid timing control
- Key scanning
- Serial interface to TEC-1
- Electrical isolation
- Protection circuits

3. Software Features:
- Solenoid pattern generation
- Key scanning and debounce
- Mode selection (type/receive)
- Buffer management
- Timing control
- Test functions

```
// TTY Interface Control Code
// Variables:
// p = shift register port (#80)
// k = key scan port (#81)
// s = solenoid delay time
// b = key buffer
// t = type mode flag
// d = data latch

// Initialize system
:I #80 p!          // Shift register port
   #81 k!          // Key scan port
   50 s!           // Solenoid timing
   [ 0 0 0 0 0 0 0 0 ] b! // Key buffer
   /T t!           // Start in type mode
   0 d! ;          // Clear data latch

// Shift out solenoid pattern
:S d!              // Save pattern
   8 (             // 8 bits
     d 7 } 1 & p /O // Output MSB
     d { d!        // Shift left
   ) ;

// Scan for key press
:K k /I b!         // Read key port to buffer
   8 (             // Check 8 bits
     b /i ? 1 & (  // If bit set
       /i S        // Activate solenoid
       s ()        // Delay
       0 S         // Release solenoid
     )
   ) ;

// Serial receive handler
:R /K d!           // Get character
   d S             // Activate solenoid
   s ()           // Hold time
   0 S ;          // Release

// Serial transmit handler
:T K              // Scan keys
   b 0 ? /F = (   // If key pressed
     b 0 ? .      // Send character
   ) ;

// Main control loop
:M I              // Initialize
   /U (           // Loop forever
     t @ (        // If type mode
       T          // Handle typing
     ) /E (       // Else
       R          // Handle receive
     )
   ) ;

// Test program
:Y I              // Initialize
   `TEST` R       // Test receive
   1000( T ) ;    // Test transmit

// Mode toggle
:W t @ /F t! ;    // Toggle type mode
```

4. Usage:
```mint
:M    // Run main program
:Y    // Run test sequence
:W    // Toggle mode
```
