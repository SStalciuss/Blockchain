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
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --gu used incorrectly");
        gen.genUsersFile(std::atoi(argv[2]));
        break;

    case AppMode::GenTransactions:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --gTx used incorrectly");
        gen.genTransactionsFile(std::atoi(argv[2]));
        break;

    case AppMode::Mine:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --mine used incorrectly");
        cli.startMining(std::atoi(argv[2]));
        break;

    case AppMode::GetBlockCount:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --getBlockCount used incorrectly");
        cli.getBlockCount();
        break;

    case AppMode::GetBlockInfo:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: --getBlockInfo used incorrectly");
        cli.getBlockInfo(std::atoi(argv[2]));
        break;

    case AppMode::GetBestHashBlock:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --getBeshHashBlock used incorrectly");
        cli.getBestHashBlock();
        break;

    case AppMode::GetHardestBlock:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --getHardestBlock used incorrectly");
        cli.getHardestBlock();
        break;

    case AppMode::GetAverageDifficulty:
        if (this->argc != 2)
            throw std::invalid_argument("Invalid argument: --getAverageDifficulty used incorrectly");
        cli.getAverageDifficulty();
        break;

    case AppMode::GetBlockTransaction:
        if (this->argc != 4)
            throw std::invalid_argument("Invalid argument: --getBlockTransaction used incorrectly");
        cli.getBlockTransaction(std::atoi(argv[2]), std::atoi(argv[3]));
        break;

    default:
        throw std::invalid_argument("Mode not found");
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
    if (modeArg == "--gTx")
    {
        this->mode = AppMode::GenTransactions;
        return;
    }
    if (modeArg == "--mine")
    {
        this->mode = AppMode::Mine;
        return;
    }
    if (modeArg == "--getBlockCount")
    {
        this->mode = AppMode::GetBlockCount;
        return;
    }
    if (modeArg == "--getBlockInfo")
    {
        this->mode = AppMode::GetBlockInfo;
        return;
    }
    if (modeArg == "--getBeshHashBlock")
    {
        this->mode = AppMode::GetBestHashBlock;
        return;
    }
    if (modeArg == "--getHardestBlock")
    {
        this->mode = AppMode::GetHardestBlock;
        return;
    }
    if (modeArg == "--getAverageDifficulty")
    {
        this->mode = AppMode::GetAverageDifficulty;
        return;
    }
    if (modeArg == "--getBlockTransaction")
    {
        this->mode = AppMode::GetBlockTransaction;
        return;
    }
    if (modeArg == "--getBlockInfo")
    {
        this->mode = AppMode::GetBlockInfo;
        return;
    }
}
