#include "processor_simulator.hpp"

bool ProcessorSimulator::validateBinaryInput(const std::string& binaryStr) {
    // Check if the input contains only 0s and 1s
    return std::all_of(binaryStr.begin(), binaryStr.end(), [](char c) {
        return c == '0' || c == '1';
    });
}

std::string ProcessorSimulator::binaryToHex(const std::string& binaryStr, ConversionMode mode) {
    // Validate input first
    if (!validateBinaryInput(binaryStr)) {
        throw ProcessorSimulatorException("Invalid binary input: must contain only 0s and 1s");
    }

    // Pad the binary string to ensure it's a multiple of 4
    std::string paddedBinary = binaryStr;
    while (paddedBinary.length() % 4 != 0) {
        paddedBinary = '0' + paddedBinary;
    }

    std::stringstream hexStream;
    hexStream << std::hex << std::uppercase;

    // Handle different conversion modes
    switch (mode) {
        case ConversionMode::STANDARD:
            // Standard conversion
            for (size_t i = 0; i < paddedBinary.length(); i += 4) {
                std::string chunk = paddedBinary.substr(i, 4);
                unsigned long decimal = std::bitset<4>(chunk).to_ulong();
                hexStream << decimal;
            }
            break;

        case ConversionMode::SIGNED: {
            // Signed integer conversion (2's complement)
            bool isNegative = paddedBinary[0] == '1';
            if (isNegative) {
                // Convert 2's complement to decimal
                std::bitset<64> bits(paddedBinary);
                int64_t signedDecimal = static_cast<int64_t>(bits.to_ulong());
                hexStream << std::hex << signedDecimal;
            } else {
                // Positive number conversion remains the same
                for (size_t i = 0; i < paddedBinary.length(); i += 4) {
                    std::string chunk = paddedBinary.substr(i, 4);
                    unsigned long decimal = std::bitset<4>(chunk).to_ulong();
                    hexStream << decimal;
                }
            }
            break;
        }

        case ConversionMode::UNSIGNED:
            // Unsigned integer conversion
            for (size_t i = 0; i < paddedBinary.length(); i += 4) {
                std::string chunk = paddedBinary.substr(i, 4);
                unsigned long decimal = std::bitset<4>(chunk).to_ulong();
                hexStream << decimal;
            }
            break;

        case ConversionMode::FLOATING_POINT:
            // IEEE 754 floating-point conversion (simplified)
            // Note: This is a basic implementation and doesn't cover all floating-point nuances
            std::bitset<32> bits(paddedBinary);
            float floatValue = *reinterpret_cast<float*>(&bits);
            hexStream << std::hex << std::scientific << floatValue;
            break;
    }

    return hexStream.str();
}

std::string ProcessorSimulator::multiThreadedBinaryToHex(const std::string& binaryStr, ConversionMode mode) {
    // Validate input first
    if (!validateBinaryInput(binaryStr)) {
        throw ProcessorSimulatorException("Invalid binary input: must contain only 0s and 1s");
    }

    // Pad the binary string to ensure it's a multiple of 4
    std::string paddedBinary = binaryStr;
    while (paddedBinary.length() % 4 != 0) {
        paddedBinary = '0' + paddedBinary;
    }

    // Determine number of threads based on hardware concurrency
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;  // Default to 4 threads if detection fails

    size_t chunkSize = paddedBinary.length() / numThreads;
    std::vector<std::string> results(numThreads);
    std::vector<std::thread> threads;

    // Split binary into chunks and process concurrently
    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? paddedBinary.length() : start + chunkSize;
        
        threads.emplace_back([this, &paddedBinary, &results, i, start, end, mode]() {
            std::string chunk = paddedBinary.substr(start, end - start);
            results[i] = convertChunk(chunk, mode);
        });
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Combine results
    std::stringstream finalResult;
    for (const auto& result : results) {
        finalResult << result;
    }

    return finalResult.str();
}

std::string ProcessorSimulator::convertChunk(const std::string& chunk, ConversionMode mode) {
    // This method is similar to binaryToHex, but works on smaller chunks
    std::stringstream hexStream;
    hexStream << std::hex << std::uppercase;

    switch (mode) {
        case ConversionMode::STANDARD:
        case ConversionMode::UNSIGNED:
            for (size_t i = 0; i < chunk.length(); i += 4) {
                std::string subChunk = chunk.substr(i, 4);
                unsigned long decimal = std::bitset<4>(subChunk).to_ulong();
                hexStream << decimal;
            }
            break;

        case ConversionMode::SIGNED: {
            std::bitset<64> bits(chunk);
            int64_t signedDecimal = static_cast<int64_t>(bits.to_ulong());
            hexStream << std::hex << signedDecimal;
            break;
        }

        case ConversionMode::FLOATING_POINT:
            std::bitset<32> bits(chunk);
            float floatValue = *reinterpret_cast<float*>(&bits);
            hexStream << std::hex << std::scientific << floatValue;
            break;
    }

    return hexStream.str();
}

void ProcessorSimulator::executeInstruction(const std::string& instruction) {
    // Basic instruction simulation
    // This is a placeholder for more complex processor instruction simulation
    if (instruction.empty()) {
        throw ProcessorSimulatorException("Empty instruction");
    }
    // Future implementation would parse and execute different types of instructions
}

void ProcessorSimulator::ProcessorState::reset() {
    registers.clear();
}

void ProcessorSimulator::ProcessorState::setRegister(const std::string& name, uint64_t value) {
    registers[name] = value;
}

uint64_t ProcessorSimulator::ProcessorState::getRegister(const std::string& name) const {
    auto it = registers.find(name);
    if (it != registers.end()) {
        return it->second;
    }
    throw ProcessorSimulatorException("Register not found: " + name);
}
