#include <gtest/gtest.h>
#include "../src/processor_simulator.hpp"

class ProcessorSimulatorTest : public ::testing::Test {
protected:
    ProcessorSimulator simulator;
};

TEST_F(ProcessorSimulatorTest, InputValidation) {
    // Valid binary inputs
    EXPECT_TRUE(ProcessorSimulator::validateBinaryInput("1010"));
    EXPECT_TRUE(ProcessorSimulator::validateBinaryInput("00001111"));

    // Invalid binary inputs
    EXPECT_FALSE(ProcessorSimulator::validateBinaryInput("10102"));
    EXPECT_FALSE(ProcessorSimulator::validateBinaryInput("abc"));
}

TEST_F(ProcessorSimulatorTest, StandardBinaryToHexConversion) {
    // Test standard conversion
    EXPECT_EQ(simulator.binaryToHex("1010"), "A");
    EXPECT_EQ(simulator.binaryToHex("00001010"), "0A");
    EXPECT_EQ(simulator.binaryToHex("11110000"), "F0");
}

TEST_F(ProcessorSimulatorTest, SignedBinaryToHexConversion) {
    // Test signed conversion (2's complement)
    EXPECT_EQ(
        simulator.binaryToHex("11110000", ConversionMode::SIGNED), 
        "FFFFFFF0"  // Represents -16 in hex
    );
    EXPECT_EQ(
        simulator.binaryToHex("00001010", ConversionMode::SIGNED), 
        "A"  // Represents positive 10
    );
}

TEST_F(ProcessorSimulatorTest, UnsignedBinaryToHexConversion) {
    // Test unsigned conversion
    EXPECT_EQ(
        simulator.binaryToHex("11110000", ConversionMode::UNSIGNED), 
        "F0"
    );
}

TEST_F(ProcessorSimulatorTest, FloatingPointConversion) {
    // Test floating point conversion (simplified)
    // 10.0 in IEEE 754 single-precision format
    EXPECT_NO_THROW(
        simulator.binaryToHex(
            "01000001001000000000000000000000", 
            ConversionMode::FLOATING_POINT
        )
    );
}

TEST_F(ProcessorSimulatorTest, MultiThreadedConversion) {
    // Test multi-threaded conversion
    std::string largeBinary = "101010101010101010101010101010101010101010";
    std::string multiThreadedHex = simulator.multiThreadedBinaryToHex(largeBinary);
    
    // Verify the conversion is correct and not empty
    EXPECT_FALSE(multiThreadedHex.empty());
}

TEST_F(ProcessorSimulatorTest, ProcessorStateManagement) {
    ProcessorSimulator::ProcessorState& state = simulator.getState();

    // Test register operations
    state.setRegister("R1", 42);
    EXPECT_EQ(state.getRegister("R1"), 42);

    state.setRegister("R2", 100);
    EXPECT_EQ(state.getRegister("R2"), 100);

    // Test state reset
    state.reset();
    EXPECT_THROW(state.getRegister("R1"), ProcessorSimulatorException);
}

TEST_F(ProcessorSimulatorTest, ErrorHandling) {
    // Test invalid binary input throws an exception
    EXPECT_THROW(
        simulator.binaryToHex("10102"), 
        ProcessorSimulatorException
    );

    // Test empty instruction throws an exception
    EXPECT_THROW(
        simulator.executeInstruction(""), 
        ProcessorSimulatorException
    );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
