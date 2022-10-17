#include "Application.h"

Application::Application(int argc, char **argv)
{
    if (argc > 1)
    {
        this->argc = argc;
        this->argv = argv;
    }
}
void Application::run()
{
    try
    {
        findMode();
        processMode();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void Application::processMode()
{
    switch (this->mode)
    {
    case AppMode::GenUsers:
        if (this->argc != 4)
            throw std::invalid_argument("Invalid argument: --gu used incorrectly");
        Generator gen;
        gen.genUsersFile(std::atoi(argv[2]), argv[3]);
        break;
    default:
        break;
    }
}

void Application::findMode()
{
    string modeArg = argv[1];
    if (modeArg == "")
    {
        throw std::invalid_argument("Invalid command line argument");
        return;
    }
    if (modeArg == "--gu")
    {
        this->mode = AppMode::GenUsers;
        return;
    }
}