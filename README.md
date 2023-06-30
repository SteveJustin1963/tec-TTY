# tec-TTY
TTY, Teleprinter/Teletypewriter, is an example of a serial terminal that was widely used in the early days of computing. A serial terminal is a device that allows users to interact with a computer or mainframe using a serial communication protocol.

The TTY was an electromechanical typewriter that could be connected to a computer or mainframe using a serial connection. It provided a means for users to input commands and receive output from the computer. The TEC-1 TTY used a teleprinter-style interface, where characters were typed on a keyboard and transmitted one at a time to the computer.

In addition to the TTY, there were other types of serial terminals used in the past, including video terminals and ASCII terminals. These terminals typically connected to the computer using a serial port and used asynchronous communication protocols.

Asynchronous protocols are a type of serial communication protocol where data is transmitted one character at a time, with each character preceded by a start bit and followed by one or more stop bits. This allows for communication between devices that may have slightly different timing or clock rates.

Serial terminals and TTY devices played a significant role in early computer systems, providing a means for users to interact with computers and input commands. They have largely been replaced by graphical user interfaces and modern computer keyboards, but the term "TTY" is still sometimes used to refer to virtual consoles or terminal emulators in Unix-like operating systems.

### proj - Mod a typewriter
Adapting a TTY or serial terminal, such as the TEC-1 TTY, to a Z80 Single-Board Computer (SBC) would involve establishing a serial communication interface between the two systems. Here are the general steps to accomplish this:

1. Identify the serial interface on the Z80 SBC: Determine the available serial communication ports on the Z80 SBC. This could be a built-in UART (Universal Asynchronous Receiver-Transmitter) or a serial expansion module.

2. Connect the TTY to the Z80 SBC: Connect the TTY device to the serial interface on the Z80 SBC. This typically involves connecting the appropriate wires for transmit (TX), receive (RX), ground (GND), and possibly other control signals such as data terminal ready (DTR) and request to send (RTS).

3. Configure the serial communication settings: Set the desired baud rate, data bits, stop bits, and parity on both the TTY and the Z80 SBC. These settings need to match for proper communication.

4. Implement the serial communication protocol: On the Z80 SBC, you'll need to write software to handle the serial communication. This typically involves initializing the UART, setting up interrupts if necessary, and implementing code to send and receive data over the serial port.

5. Handle input and output on the Z80 SBC: Once the serial communication is established, you'll need to handle input and output from the TTY device on the Z80 SBC. This could involve reading characters received from the TTY and processing them as commands or displaying output on the TTY by sending characters from the Z80 SBC.

The specific steps and code required for adapting the TTY to a Z80 SBC will depend on the exact hardware and software environment you are working with. The documentation and resources available for your specific Z80 SBC and TTY device will be valuable references during the adaptation process.




