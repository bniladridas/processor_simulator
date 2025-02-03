# 🏭 Industrial Binary Processor Simulator

## Overview
Sophisticated binary conversion tool for industrial and manufacturing applications.

## 🚀 Architecture
- **Backend**: C++ HTTP Server
- **Frontend**: React.js 
- **Containerization**: Docker Multi-Stage Build
- **CI/CD**: GitHub Actions

## 🌟 Key Features
- Multiple Binary Conversion Modes
  - Unsigned Interpretation
  - Signed (Two's Complement)
  - Floating Point Approximation
- Industrial-Themed UI
- Responsive Design

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
# Build and Start
docker-compose up -d

# Access Application
http://localhost
```

## 🛠 Technologies
- C++17
- React.js
- Docker
- Nginx
- GitHub Actions

## 🤝 Contributing
1. Fork Repository
2. Create Feature Branch
3. Commit Changes
4. Open Pull Request

## 📄 License
MIT License
