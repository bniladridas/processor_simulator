#include <fcgi_stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "processor_simulator.hpp"

std::string handleConversionRequest(const std::string& binary, const std::string& mode) {
    ProcessorSimulator simulator;
    ConversionMode conversionMode;

    // Convert string mode to enum
    if (mode == "SIGNED") {
        conversionMode = ConversionMode::SIGNED;
    } else if (mode == "UNSIGNED") {
        conversionMode = ConversionMode::UNSIGNED;
    } else if (mode == "FLOATING_POINT") {
        conversionMode = ConversionMode::FLOATING_POINT;
    } else {
        conversionMode = ConversionMode::STANDARD;
    }

    try {
        std::string hexResult = ProcessorSimulator::binaryToHex(binary, conversionMode);
        return "{\"hex\": \"" + hexResult + "\"}";
    } catch (const ProcessorSimulatorException& e) {
        return "{\"error\": \"" + std::string(e.what()) + "\"}";
    }
}

int main() {
    while (FCGI_Accept() >= 0) {
        printf("Content-Type: application/json\r\n\r\n");

        char* contentLength = getenv("CONTENT_LENGTH");
        int len = contentLength ? atoi(contentLength) : 0;

        std::string input;
        if (len > 0) {
            char* buffer = new char[len + 1];
            fread(buffer, 1, len, stdin);
            buffer[len] = '\0';
            input = buffer;
            delete[] buffer;

            // Basic JSON parsing (simplified)
            std::string binary = "1010";  // Default value
            std::string mode = "STANDARD";

            size_t binaryPos = input.find("\"binary\":");
            if (binaryPos != std::string::npos) {
                size_t start = input.find("\"", binaryPos + 10);
                size_t end = input.find("\"", start + 1);
                if (start != std::string::npos && end != std::string::npos) {
                    binary = input.substr(start + 1, end - start - 1);
                }
            }

            size_t modePos = input.find("\"mode\":");
            if (modePos != std::string::npos) {
                size_t start = input.find("\"", modePos + 8);
                size_t end = input.find("\"", start + 1);
                if (start != std::string::npos && end != std::string::npos) {
                    mode = input.substr(start + 1, end - start - 1);
                }
            }

            std::string response = handleConversionRequest(binary, mode);
            printf("%s", response.c_str());
        }
    }

    return 0;
}
