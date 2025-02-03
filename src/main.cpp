#include <iostream>
#include <string>
#include "processor_simulator.hpp"

void demonstrateConversionModes() {
    ProcessorSimulator simulator;

    std::cout << "Conversion Mode Demonstrations:\n";

    // Standard Conversion
    std::string binaryInput = "1010"; // Decimal 10
    std::cout << "Standard Mode:\n";
    std::cout << "Binary: " << binaryInput 
              << " -> Hex: " << simulator.binaryToHex(binaryInput) << std::endl;

    // Signed Conversion (Negative Number)
    binaryInput = "11110000"; // -16 in 2's complement
    std::cout << "\nSigned Mode (Negative):\n";
    std::cout << "Binary: " << binaryInput 
              << " -> Hex: " << simulator.binaryToHex(binaryInput, ConversionMode::SIGNED) << std::endl;

    // Unsigned Conversion
    binaryInput = "11111111"; // 255
    std::cout << "\nUnsigned Mode:\n";
    std::cout << "Binary: " << binaryInput 
              << " -> Hex: " << simulator.binaryToHex(binaryInput, ConversionMode::UNSIGNED) << std::endl;

    // Floating Point Conversion (Simplified)
    binaryInput = "01000001001000000000000000000000"; // 10.0 in IEEE 754
    std::cout << "\nFloating Point Mode:\n";
    std::cout << "Binary: " << binaryInput 
              << " -> Hex: " << simulator.binaryToHex(binaryInput, ConversionMode::FLOATING_POINT) << std::endl;
}

void demonstrateProcessorState() {
    ProcessorSimulator simulator;
    ProcessorSimulator::ProcessorState& state = simulator.getState();

    std::cout << "\nProcessor State Demonstration:\n";

    // Set and get registers
    state.setRegister("R1", 42);
    state.setRegister("R2", 100);

    std::cout << "R1 Value: " << state.getRegister("R1") << std::endl;
    std::cout << "R2 Value: " << state.getRegister("R2") << std::endl;

    // Reset state
    state.reset();
    std::cout << "State reset. Attempting to access R1...\n";
    try {
        state.getRegister("R1");
    } catch (const ProcessorSimulatorException& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        // Demonstrate conversion modes
        demonstrateConversionModes();

        // Demonstrate processor state management
        demonstrateProcessorState();

        // If command-line arguments are provided, process them
        if (argc > 1) {
            ProcessorSimulator simulator;
            std::string binaryInput = argv[1];
            
            std::cout << "\nCommand-line Input Processing:\n";
            std::cout << "Binary: " << binaryInput 
                      << " -> Hex: " << simulator.binaryToHex(binaryInput) << std::endl;
        }
    } catch (const ProcessorSimulatorException& e) {
        std::cerr << "Processor Simulator Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected Error: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
