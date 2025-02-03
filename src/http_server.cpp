#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <vector>
#include <regex>
#include <httplib.h>
#include "processor_simulator.hpp"

class HttpServer {
private:
    std::string extractBinaryFromJson(const std::string& json) {
        std::regex binaryRegex("\"binary\":\\s*\"([^\"]+)\"");
        std::smatch match;
        if (std::regex_search(json, match, binaryRegex)) {
            return match[1].str();
        }
        return "1010";  // Default value
    }

    std::string extractModeFromJson(const std::string& json) {
        std::regex modeRegex("\"mode\":\\s*\"([^\"]+)\"");
        std::smatch match;
        if (std::regex_search(json, match, modeRegex)) {
            return match[1].str();
        }
        return "STANDARD";  // Default value
    }

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

public:
    void start(int port = 8081) {  // Changed default port
        httplib::Server svr;

        // Handle OPTIONS request for CORS preflight
        svr.Options("/convert", [](const httplib::Request& req, httplib::Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            res.status = 204;
        });

        // Handle POST request for conversion
        svr.Post("/convert", [this](const httplib::Request& req, httplib::Response& res) {
            // Set CORS headers
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            res.set_header("Content-Type", "application/json");

            // Log incoming request body for debugging
            std::cout << "Received request body: " << req.body << std::endl;

            // Parse JSON body
            std::string binary = extractBinaryFromJson(req.body);
            std::string mode = extractModeFromJson(req.body);

            // Perform conversion
            std::string result = handleConversionRequest(binary, mode);

            // Set response
            res.body = result;
            res.status = 200;
        });

        std::cout << "Server attempting to listen on port " << port << std::endl;
        
        // Bind to all interfaces
        if (!svr.listen("0.0.0.0", port)) {
            std::cerr << "Failed to bind to port " << port << std::endl;
            exit(1);
        }
    }
};

int main() {
    HttpServer server;
    server.start();
    return 0;
}
