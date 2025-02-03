# 🏭 Industrial Binary Processor Simulator

## Overview
A sophisticated binary conversion tool designed for industrial and manufacturing applications, providing precise and versatile binary number representations.

## 🚀 Project Architecture
- **Backend**: C++ HTTP Server
- **Frontend**: React.js with Industrial Design
- **Containerization**: Docker Multi-Stage Build
- **CI/CD**: GitHub Actions

## 🔧 Technical Specifications

### Entry Stage Architecture
```
Project Root
│
├── src/                # C++ Backend Source
│   └── processor_simulator.hpp
│   └── http_server.cpp
│
├── frontend/           # React Frontend
│   ├── src/
│   │   ├── App.js      # Main Application Component
│   │   └── index.css   # Industrial Theme Styles
│
├── Dockerfile          # Multi-Stage Docker Build
├── docker-compose.yml  # Container Orchestration
└── nginx.conf          # Web Server Configuration
```

## 🌟 Key Features
- Multiple Binary Conversion Modes
  - Unsigned Interpretation
  - Signed (Two's Complement)
  - Floating Point Approximation
- Industrial-Themed UI
- Responsive Design
- Precise Conversion Algorithms

## 🐳 Docker Deployment Stages

### 1. Backend Build Stage
- Base Image: Ubuntu 20.04
- Installs build dependencies
- Compiles C++ backend
- Uses CMake for build configuration

### 2. Frontend Build Stage
- Base Image: Node.js 18 Alpine
- Installs npm dependencies
- Builds React application
- Generates production-ready static files

### 3. Final Deployment Stage
- Combines backend executable
- Integrates frontend build
- Configures Nginx web server
- Exposes ports 80 (Web) and 8080 (API)

## 🚀 Quick Start

### Local Development
```bash
# Clone Repository
git clone https://github.com/bniladridas/processor_simulator.git

# Backend Setup
mkdir build && cd build
cmake ..
make

# Frontend Setup
cd frontend
npm install
npm start

# Run Backend Server
./processor_simulator
```

### Docker Deployment
```bash
# Build Docker Image
docker-compose build

# Start Containers
docker-compose up -d

# Access Application
http://localhost
```

## 🔬 Conversion Modes

### 1. Unsigned Interpretation
- Standard binary to decimal conversion
- Treats all bits as positive magnitude

### 2. Signed (Two's Complement)
- Handles negative numbers
- Interprets Most Significant Bit (MSB)
- Supports 4-bit to 32-bit representations

### 3. Floating Point Approximation
- IEEE 754 style conversion
- Supports simplified floating-point representation

## 🛠 Technologies
- C++17
- CMake
- React.js
- Node.js
- Docker
- Nginx
- GitHub Actions

## 📦 Dependencies
- Boost C++ Libraries
- React Bootstrap
- Axios
- React Icons

## 🤝 Contributing
1. Fork the Repository
2. Create Feature Branch
3. Commit Changes
4. Push to Branch
5. Open Pull Request

## 📄 License
MIT License

## 🏢 Industrial Use Cases
- Manufacturing Process Control
- Embedded Systems Development
- Digital Signal Processing
- Educational Tools
- Hardware Design Simulation

## 📞 Contact
Nilanjan Das - [Your Email/LinkedIn]
