#include "include/IOmanager.hpp"
#include "include/helper.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <stdexcept>

// Include the Windows API header file for GetModuleFileNameA and MAX_PATH.
#include <windows.h>

// #include "include/commands.hpp"

IOmanager::IOmanager(int argc, const char* argv[], Helper& helper_ref)
    : helper(helper_ref)
{
    helper.printArgs(argc, argv);
}

bool IOmanager::readFileContent(std::string filename) {
    //if(!ready){return false;}

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        // std::cerr << "Error: Could not open file " << filename << std::endl;
        helper.logError("Could not open file: " + filename);
        helper.logWarning("File does not exist");
        return false;
    }

    helper.logInfo("printing file: " + filename);
    std::string line;
    while (std::getline(inputFile, line)) {
        helper.logDebug("Read line from file: '" + line + "' (Length: " + std::to_string(line.length()) + ")");
        //data.availableArgs.push_back(line);
    }

    inputFile.close();
    helper.logInfo("Done printing file.");
    
    return true;
}

command IOmanager::check()
{
    return eNull;
}



// Cross-platform function to get the executable's directory.
// For simplicity, this example uses a common technique for Linux and Windows.
// A more robust solution for older systems may use platform-specific APIs.
std::filesystem::path IOmanager::getExecutableDirectory() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    if (GetModuleFileNameA(NULL, buffer, MAX_PATH) == 0) {
        throw std::runtime_error("Could not get executable path.");
    }
    std::filesystem::path p(buffer);
#else
    char buffer; // Using a fixed-size buffer
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        std::filesystem::path p(buffer);
    }
    else {
        throw std::runtime_error("Could not get executable path.");
    }
#endif
    return p.parent_path();
}

/**
 * @brief Creates a new file at a specified path relative to the executable's location.
 * @param relativePath The path and filename to create, relative to the executable.
 * @param contents The string content to write to the file.
 * @return True if the file was created successfully, false otherwise.
 */
bool IOmanager::writeFileFromExePath(const std::filesystem::path& relativePath, const std::string& contents, FileWriteMode mode) {
    try {
        std::filesystem::path executableDir = getExecutableDirectory();
        std::filesystem::path fullPath = executableDir / relativePath;

        // Create parent directories if they don't exist.
        std::filesystem::create_directories(fullPath.parent_path());

        // Select the appropriate open mode based on the function parameter.
        std::ios_base::openmode openMode = std::ios_base::out;
        if (mode == FileWriteMode::Append) {
            openMode |= std::ios_base::app;
        }

        std::ofstream fileStream(fullPath, openMode);

        if (fileStream.is_open()) {
            fileStream << contents;
            fileStream.close();
            return true;
        }
        else {
            std::cerr << "Error: Could not open file for writing at " << fullPath << std::endl;
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

int IOmanager::printToLogFile(std::string logMsg) {
    writeFileFromExePath(helper.serverLogFile, logMsg + '\n', FileWriteMode::Append);
    return 0;
}

int IOmanager::test() {
    const std::string filename = "data/log.txt";

    // Example 1: Overwrite or create a new file.
    writeFileFromExePath(filename, "This is the first log entry.\n", FileWriteMode::Append);

    // Example 2: Append a new line to the existing file.
    writeFileFromExePath(filename, "This is the second log entry.\n", FileWriteMode::Append);

    // Example 3: Append another line.
    writeFileFromExePath(filename, "This is the third log entry.\n", FileWriteMode::Append);

    // Check the final file content
    std::cout << "Writing complete. Check " << filename << " in the executable directory." << std::endl;

    return 0;
}