# AvanSync

Eindopdracht **CPPLS2** versie 1.0 – najaar 2020  
**AvanSync** – Bob Polis, Avans Hogeschool, ’s-Hertogenbosch  
Ingeleverd: **11 december 2020**

AvanSync is a C++ client–server application that demonstrates core concepts from the CPPLS2 course: networking, concurrency, modular design and unit testing.  
The repository is structured as a Visual Studio solution with three main projects:

- `Client` – console client application
- `Server` – console server application
- `UnitTests` – automated tests for the core logic

---

## Table of Contents

- [Project Goals](#project-goals)
- [Architecture Overview](#architecture-overview)
  - [Client](#client)
  - [Server](#server)
  - [UnitTests](#unittests)
- [Technology Stack](#technology-stack)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Cloning the Repository](#cloning-the-repository)
  - [Opening the Solution](#opening-the-solution)
- [Building and Running](#building-and-running)
  - [Start the Server](#start-the-server)
  - [Start the Client](#start-the-client)
- [Running the Unit Tests](#running-the-unit-tests)
- [Project Structure](#project-structure)
- [Possible Extensions](#possible-extensions)
- [Credits](#credits)
- [License](#license)

---

## Project Goals

The main learning goals behind **AvanSync** are:

- Practice **C++** in a multi-file, multi-project solution.
- Design and implement a **client–server** architecture.
- Work with **networking** (sockets) and **concurrency** (threads).
- Apply **modular design** and separation of concerns:
  - networking
  - protocol/command handling
  - domain logic
- Add **unit tests** to verify core behaviour and prevent regressions.
- Deliver a complete assignment with:
  - working code,
  - documentation (this README),
  - and a maintainable folder structure.

---

## Architecture Overview

The solution consists of three main projects inside the repository:

### Client

The `Client` project contains the console-based client application. Typical responsibilities include:

- Establishing a connection to the server (e.g. via TCP).
- Sending user commands / requests to the server.
- Receiving responses and presenting them in a readable form.
- Handling basic input validation and error reporting.

The client is designed to be small and focused on:

- user interaction,
- serialising / deserialising messages,
- and delegating actual processing to the server.

### Server

The `Server` project implements the server-side application. Typical responsibilities include:

- Accepting incoming client connections.
- Handling multiple clients (e.g. via threads or other concurrency mechanisms).
- Parsing and interpreting the custom application protocol.
- Executing the requested operations and sending back responses.
- Logging and basic error handling.

The server is where most of the **core logic** lives; it is structured to keep protocol handling separate from the underlying logic so it can be tested and extended more easily.

### UnitTests

The `UnitTests` project contains automated tests for important parts of the code base.  
Typical tests check:

- correctness of protocol parsing / formatting,
- core logic classes without depending on the actual console UI,
- edge cases and error handling.

Using a separate test project helps keep tests organised and allows them to be run independently from the client and server.

---

## Technology Stack

- **Language:** C++ (≈ 98% of the repository)
- **Build System:** Visual Studio solution (`AvanSync.sln`)
- **Target Platform:** Windows (desktop)
- **Concepts:**
  - Sockets / networking
  - Concurrency / threads
  - Separation of concerns
  - Unit testing

---

## Getting Started

### Prerequisites

To build and run AvanSync you typically need:

- **Windows** (tested with a desktop version of Windows)
- **Visual Studio 2019 or 2022** with:
  - **“Desktop development with C++”** workload installed

> If you use another compiler or IDE, you may have to adapt include paths, project settings and/or socket APIs.

### Cloning the Repository

```bash
git clone https://github.com/ferrannl/AvanSync.git
cd AvanSync

Opening the Solution

1. Start Visual Studio.


2. Open the file: AvanSync.sln (in the repository root).


3. Let Visual Studio load and index all projects (Client, Server, UnitTests).




---

Building and Running

Start the Server

1. In Visual Studio, set Server as the Startup Project:

Right-click Server in Solution Explorer → Set as StartUp Project.



2. Select the desired configuration:

Debug / Release

x86 or x64 (whatever matches the project configuration)



3. Build and run:

Press F5 (Run with debugger)

or Ctrl+F5 (Run without debugger)




The server will start listening for incoming client connections on the configured address/port (see the source code for the specific settings).

Start the Client

1. Once the server is running, set Client as the Startup Project.


2. Build and run it the same way (F5 / Ctrl+F5).


3. The client will attempt to connect to the server using the configured host and port.



Typical flow:

1. Start Server.


2. Start one or more Client instances.


3. Use the client console to send requests/commands to the server.


4. Check the server output and/or logs to verify behaviour.



> Tip: If the client fails to connect, double-check:

server is running,

host/port configuration matches on both client and server,

firewall settings are not blocking local connections.





---

Running the Unit Tests

1. In Visual Studio, build the UnitTests project.


2. Open the Test Explorer:

Test → Test Explorer



3. Click Run All to execute all available tests.


4. Inspect the results and, if tests fail, check the corresponding code in both:

the production projects (Client, Server, shared code), and

the test project (UnitTests).




This helps to:

verify that refactoring or new features do not break existing behaviour,

document the expected behaviour in executable form.



---

Project Structure

Simplified view of the repository layout:

AvanSync/
├─ Client/
│  ├─ ...            # Client source files (C++)
│  └─ ...
├─ Server/
│  ├─ ...            # Server source files (C++)
│  └─ ...
├─ UnitTests/
│  ├─ ...            # Unit test source files
│  └─ ...
├─ AvanSync.sln      # Visual Studio solution
├─ .gitignore
└─ README.md         # This file

The exact structure inside Client, Server and UnitTests is organised per module/class, following the typical C++ .h / .cpp split.


---

Possible Extensions

If you want to build further on this assignment, some ideas:

Configuration file support
Allow host, port and other settings to be configured via a file instead of hard-coding them.

More detailed logging
Add log levels and log to files instead of (or alongside) the console.

Improved protocol
Extend the command set or change to a more structured format if desired.

Additional tests
Add tests for new features, edge cases and error handling branches.


These extensions are good opportunities to practice refactoring, testing and design improvements on top of the original assignment.


---

Credits

Author / Student: ferrannl

Course: CPPLS2

Institution: Avans Hogeschool, ’s-Hertogenbosch

Assignment Title: AvanSync – Eindopdracht CPPLS2 versie 1.0 (najaar 2020)

Date: 11 december 2020



---

License

This project was created as a school assignment.
Unless a separate license file is added, it should be treated as all rights reserved by the author.
If you want to reuse (parts of) this code, please contact the repository owner first.
