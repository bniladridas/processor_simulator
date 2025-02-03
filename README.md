# Processor Simulator

## Overview
A full-stack web application for binary-to-hexadecimal conversion with multiple processing modes.

## Features
- Binary to Hexadecimal conversion
- Multiple conversion modes:
  * Standard
  * Signed
  * Unsigned
  * Floating Point
- Responsive web interface
- C++ backend with HTTP support
- React frontend

## Prerequisites
- CMake
- C++17 compiler
- Node.js (v14 or later)
- npm

## Detailed Setup and Installation

### 1. Clone the Repository
```bash
git clone https://github.com/bniladridas/processor_simulator.git
cd processor_simulator
```

### 2. Build Backend (C++ Server)
```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Return to project root
cd ..
```

### 3. Install Frontend Dependencies
```bash
cd frontend
npm install
cd ..
```

### 4. Run the Application

#### Terminal 1: Start Backend Server
```bash
cd build
./processor_server
# Server will run on http://localhost:8081
```

#### Terminal 2: Start Frontend
```bash
cd frontend
npm start
# Frontend will run on http://localhost:3001
```

### 5. Access the Application
Open your web browser and navigate to:
- Frontend URL: `http://localhost:3001`

### Usage
1. Enter a binary number (e.g., "1010")
2. Select a conversion mode
3. Click "Convert"
4. View the hexadecimal result

## Troubleshooting
- Ensure all prerequisites are installed
- Check that no other services are running on ports 8081 and 3001
- Verify CMake and npm installations

## Technologies
- Backend: C++, CMake, cpp-httplib
- Frontend: React, Bootstrap
- Conversion Modes: Standard, Signed, Unsigned, Floating Point

## License
MIT License
