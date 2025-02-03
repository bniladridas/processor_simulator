#ifndef PROCESSOR_SIMULATOR_HPP
#define PROCESSOR_SIMULATOR_HPP

#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <unordered_map>

// Enum for different conversion modes
enum class ConversionMode {
    STANDARD,
    SIGNED,
    UNSIGNED,
    FLOATING_POINT
};

class ProcessorSimulator {
public:
    // Processor state simulation
    class ProcessorState {
    public:
        void reset();
        void setRegister(const std::string& name, uint64_t value);
        uint64_t getRegister(const std::string& name) const;
        
    private:
        std::unordered_map<std::string, uint64_t> registers;
    };

    // Public accessor for processor state
    ProcessorState& getState() { return state; }
    const ProcessorState& getState() const { return state; }

    // Enhanced binary to hex conversion with multiple modes
    static std::string binaryToHex(const std::string& binaryStr, 
                                   ConversionMode mode = ConversionMode::STANDARD);
    
    // Multi-threaded conversion with error handling
    std::string multiThreadedBinaryToHex(const std::string& binaryStr, 
                                         ConversionMode mode = ConversionMode::STANDARD);
    
    // Instruction execution simulation
    void executeInstruction(const std::string& instruction);
    
    // Validate binary input
    static bool validateBinaryInput(const std::string& binaryStr);

private:
    // Thread-safe conversion helper
    std::string convertChunk(const std::string& chunk, ConversionMode mode);
    
    // Mutex for thread-safe operations
    std::mutex conversionMutex;
    
    // Processor state
    ProcessorState state;
};

// Custom exception for processor simulator
class ProcessorSimulatorException : public std::runtime_error {
public:
    explicit ProcessorSimulatorException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // PROCESSOR_SIMULATOR_HPP
