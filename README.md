
# Microcontroller Embedded C Programming: Absolute Beginners

This repo contains notes and programming assignments for the Udemy's "[Microcontroller Embedded C Programming: Absolute Beginners](https://www.udemy.com/course/microcontroller-embedded-c-programming/)" course by FastBit Embedded Brain Academy.

Date: November, 2022.

- The course is instructed by Engineer Kiran Nayak.

- The [**Certificate**](https://github.com/renatosoriano/Udemy-Embedded-Course1_Microcontroller-Embedded-C-Programming-Absolute-Beginners/blob/main/Certificate.pdf) is available. 

- The [**C Language Coding Exercises**](https://github.com/renatosoriano/Udemy-Embedded-Course1_Microcontroller-Embedded-C-Programming-Absolute-Beginners/tree/main/Host_Workspace) are available. 

- The [**Embedded Microcontroller Coding Exercises**](https://github.com/renatosoriano/Udemy-Embedded-Course1_Microcontroller-Embedded-C-Programming-Absolute-Beginners/tree/main/Target_Workspace) are available. 

## Descriptions

This course is mainly targeted for absolute beginners to learn microcontroller programming using the 'C ' programming language.
Some of the critical microcontroller-related 'C' concepts discussed with clear examples and writing code for the target embedded board are:

1. Importance of bitwise operators.
2. Usage of bit manipulation techniques to program MCU peripheral registers.
3. Accessing memory-mapped registers using pointers.
4. Pointers and casting.
5. Structures, bitfields, unions, and bit extraction techniques.
6. Representing hardware registers details and configuring them using 'C' structure definitions.
7. Usage of const and volatile type qualifiers.
8. Interpret complex variable definitions involving the combination of const and volatile.
9. The precise usage of const pointers, const data, volatile const, with pointer and non-pointer variables.
10. The behavior of the code during compiler optimization and solution using volatile.
11. Functions and friends.
12. Data types, variables definitions, storage class specifiers and much more.
13. Loops: while, for, do. while.
14. MCU internal architecture and programming peripherals.
15. Interfacing projects.

## Requirements

**[STM32 Nucleo-F446RE Development Board](https://www.st.com/en/evaluation-tools/nucleo-f446re.html#overview)** - Board used in this course but any board with Arm Cortex-M0/3/4 core will work, just modifying the target board and configuring with the respective datasheet. \
**[Eclipse-based STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)** - C/C++ development platform with peripheral configuration, code generation, code compilation, and debug features for STM32 microcontrollers and microprocessors. Works on Windows/Linux/Mac and is free.

## Notes
* #### FPU warning fix
    Right click on the project -> properties -> expand C/C++ build -> Settings -> Tool settings -> MCU settings
  * `Floating-point unit: None`
  * `Floating-point ABI: Software implementation ( -mfloat-abi=soft )`

![FPU_warning.png](https://github.com/renatosoriano/Udemy-Embedded-Course1_Microcontroller-Embedded-C-Programming-Absolute-Beginners/blob/main/Images/FPU_warning.png)

* #### Setting up SWV ITM Data Console

Open *syscalls.c* file and paste following code bellow *Includes*

```c
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//           Implementation of printf like feature using ARM Cortex M3/M4/ ITM functionality
//           This function will not work for ARM Cortex M0/M0+
//           If you are using Cortex M0, then you can use semihosting feature of openOCD
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//Debug Exception and Monitor Control Register base address
#define DEMCR                   *((volatile uint32_t*) 0xE000EDFCU )

/* ITM register addresses */
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )

void ITM_SendChar(uint8_t ch)
{

	//Enable TRCENA
	DEMCR |= ( 1 << 24);

	//enable stimulus port 0
	ITM_TRACE_EN |= ( 1 << 0);

	// read FIFO status in bit [0]:
	while(!(ITM_STIMULUS_PORT0 & 1));

	//Write to ITM stimulus port0
	ITM_STIMULUS_PORT0 = ch;
}
```


After that find function *_write* and replace `__io_putchar(*ptr++)` with `ITM_SendChar(*ptr++)` like in code snippet below
```c
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		//__io_putchar(*ptr++);
		ITM_SendChar(*ptr++);
	}
	return len;
}
```

After these steps navigate to Debug configuration and check `Serial Wire Viewer (SWV)` check box like on snapshot below

![Debugger.png](https://github.com/renatosoriano/Udemy-Embedded-Course1_Microcontroller-Embedded-C-Programming-Absolute-Beginners/blob/main/Images/Debugger.png)

Once you enter *Debug* mode, go to `Window -> Show View -> SWV -> Select SWV ITM Data Console`. On this way `ITM Data Console` will be shown in *Debug* session.


In `SWV ITM Data Console Settings` in section `ITM Stimulus Ports` enable port 0, so that you can see `printf` data.



