#include "include/IOmanager.hpp"
#include "include/helper.hpp"
// #include "include/commands.hpp"

IOmanager::IOmanager(int argc, const char *argv[], Helper& helper_ref) 
    : helper(helper_ref)
{
    data.argc = argc;
    if (argc - 1 > MAX_ARGS)
    {
        helper.logWarning("Too many arguments given. Max arguments is set at: " + std::to_string(MAX_ARGS));
        ready = false;
    } 
    else 
    {
        ready = true;
        helper.printArgs(argc, argv);
        for (int i = 0; i < argc; ++i) {
            // helper.logDebug("Command line arg " + std::to_string(i) + ": '" + commandLineArgs.back() + "' (Length: " + std::to_string(commandLineArgs.back().length()) + ")");
            data.commandLineArgs.push_back(argv[i]);
        }
    }
}

bool IOmanager::readFileContent(std::string filename) {
    if(!ready){return false;}

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        // std::cerr << "Error: Could not open file " << filename << std::endl;
        helper.logError("Could not open file: " + filename);
        helper.logWarning("File either doesnt exist or is not named corectly. Please make sure file"  
                          " is named 'AvailableArgs.txt', or if available args file is not not needed," 
                          " then specify '--nofile' as the only argument");
        return false;
    }

    helper.logInfo("Storing arguments...");
    std::string line;
    while (std::getline(inputFile, line)) {
        helper.logDebug("Read line from file: '" + line + "' (Length: " + std::to_string(line.length()) + ")");
        data.availableArgs.push_back(line);
    }

    inputFile.close();
    helper.logInfo("Done storing argument.");
    
    return true;
}

command IOmanager::check()
{

    // if(readFileContent("AvailableArgs.txt")) // read the file
    // {
        
    // }

    // here I do 'data.argc - 1' because otherwise I get an 'std::length_error' 
        for(int i = 0; i < data.argc - 1; i++) 
        {
            std::string curent(data.commandLineArgs[i + 1]); // 'data.commandLineArgs[i + 1]' I do (i + 1) to skip the first arg, being the program name.
            helper.logDebug(curent);

            switch (hashit(curent))
            {
                case eServer:
                    helper.logDebug("Match");
                    return eServer;
                    break;
            
                case eClient:
                    helper.logDebug("Match");
                    return eClient;
                    break;

                case eTest:
                    helper.logDebug("Match");
                    return eTest;
                    break;
            
                default:
                    /* not a match */
                    helper.logWarning("Not a match. Or uncuaght argument. If a new command was added, please make sure to update the IOmanager::check() function, and the main function, as well as the hashit function and the enums. All must be updated.");
                    return eNull;
                    break;
            }
        }

    // This if statement is only reached if the file fails to be read.
    if(data.commandLineArgs[1] == "--nofile")
    {
        helper.logDebug("NoFile");
        return eNofile;
    }

    return eNull;
}