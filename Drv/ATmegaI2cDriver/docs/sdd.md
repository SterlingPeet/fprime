# ATmega I2C Driver Component

## 1. Introduction

I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).

## 2. Requirements

The requirements for `Drv::ATmegaI2cDriverComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
AT-I2C-001 | The `Drv::ATmegaI2cDriverComponent` component accepts I2cReadWrite requests and performs an I2C transaction | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Drv::ATmegaI2cDriverComponent` component has the following component diagram:

![`Drv::ATmegaI2cDriverComponent` Diagram](img/ATmegaI2cDriverComponentBDD.jpg "Drv::ATmegaI2cDriverComponent")

#### 3.1.2 Ports

The `Drv::ATmegaI2cDriverComponent` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
[`Drv::I2cWriteRead`](../I2cDriverPorts/docs/sdd.html) | i2cTransaction | Input | Sync | Transaction buffer pair for sending and recieving I2C data

### 3.2 Functional Description

This component takes the data in the I2C write buffer, and writes it to the I2C port.  Then data read back from the device is placed in the read buffer, and the component's work is done.

### 3.3 Scenarios

`Drv::ATmegaI2cDriverComponent` handles reentrance gracefully.
TODO: More description.

### 3.4 Underlying ATmega128 Registers

#### 3.4.1 ``TWCR`` TWI Control Register

The ``TWCR`` is used to control the operation of the ``TWI``.
It is used to enable the ``TWI``, to initiate a master access by applying a ``START`` condition to the bus, to generate a receiver acknowledge, to generate a stop condition, and to control halting of the bus while the data to be written to the bus are written to the ``TWDR``.
It also indicates a write collision if data is attempted written to ``TWDR`` while the register is inaccessible.

| Bit | Slug      | R/W | Name               |
| --- | --------- | --- | ------------------ |
| 7   | ``TWINT`` | R/W | TWI Interrupt Flag |
| 6   | ``TWEA``  | R/W | TWI Enable Acknowledge Bit |
| 5   | ``TWSTA`` | R/W | TWI START Condition Bit |
| 4   | ``TWSTO`` | R/W | TWI STOP Condition Bit |
| 3   | ``TWWC``  | R   | TWI Write Collision Flag |
| 2   | ``TWEN``  | R/W | TWI Enable Bit |
| 1   | ``Res``   | R   | Reserved Bit |
| 0   | ``TWIE``  | R/W | TWI Interrupt Enable |

#### 3.4.2 ``TWSR`` TWI Status Register

| Bit | Slug      | R/W | Name               |
| --- | --------- | --- | ------------------ |
| 7   | ``TWS7``  | R   | TWI Status bit 7 |
| 6   | ``TWS6``  | R   | TWI Status bit 6 |
| 5   | ``TWS5``  | R   | TWI Status bit 5 |
| 4   | ``TWS4``  | R   | TWI Status bit 4 |
| 3   | ``TWS3``  | R   | TWI Status bit 3 |
| 2   | ``Res``   | R   | Reserved Bit |
| 1   | ``TWPS1`` | R/W | TWI Prescaler Bits |
| 0   | ``TWPS0`` | R/W | TWI Prescaler Bits |

**Bits 7..3 – TWS: TWI Status**
These 5 bits reflect the status of the TWI logic and the Two-wire Serial Bus.
The different status codes are described later in this section.

**Bits 1..0 – TWPS: TWI Prescaler Bits**
These bits can be read and written, and control the bit rate prescaler.

#### 3.4.3 ``TWSR`` Status Codes Table

#### 3.4.4 Master Transmitter Hardware States

### 3.5 Software State

Internal state is tracked during the course of the ``i2cTransaction`` port call.
This allows a reentrant port call process in a single-threaded system, so the interrupting execution thread can queue the new work and continue the hardware I2C transaction uninterrupted.
Doing so makes the driver able to handle port calls that originate from ISR contexts, and might not know about an existing transaction in progress.

`Drv::ATmegaI2cDriverComponent` has the following state diagram:

![`Drv::ATmegaI2cDriver` State Machine](img/ATmegaI2cDriverStateMachine.png "Drv::ATmegaI2cDriver State Machine")

### 3.6 Algorithms

`Drv::ATmegaI2cDriverComponent` has a small software queue...

## 4. Dictionary

Dictionaries: [HTML](ATmegaI2cDriverComponent.html) [MD](ATmegaI2cDriverComponent.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/DrvATmegaI2cDriverComponent_gcov.txt)

[Coverage Output - `ATmegaI2cDriverComponent.cpp`](../test/ut/output/ATmegaI2cDriverComponent.cpp.gcov)

[Coverage Output - `ATmegaI2cDriverComponentComponentAc.cpp`](../test/ut/output/ATmegaI2cDriverComponentComponentAc.cpp.gcov)

## 6. Change Log

Date | Description
---- | -----------
11/11/2020 | Additional update and restructuring, add support for queued/interrupted transactions
08/17/2020 | Documentation updates and restructuring to better support ``fprime-util`` usage
12/20/2019 | Initial Component Design



