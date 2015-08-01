#include "Network.h"
#include <iostream>
#include <fstream>

void TestWrite()
{
    std::ofstream opFile("test.rnn");
    if (!opFile.is_open())
    {
        throw std::exception("failed to open the file");
    }
    Network rnn;
    rnn.Test();
    rnn.WriteState(opFile);
    std::cout << "successfully written!" << std::endl; 
    opFile.close();
}

void TestRead()
{
    std::ifstream ipFile("test.rnn");
    if (!ipFile.is_open())
    {
        throw std::exception("failed to open the file");
    }
    Network rnn;
    rnn.ReadState(ipFile);
    rnn.WriteState(std::cout);  // display the state
    ipFile.close();
}

int main()
{
    try
    {
        TestWrite();
        //TestRead();
    }
    catch (std::exception err)
    {
        std::cout << "Error!" << std::endl << err.what();
    }
    std::cin.get();
    return 0;
}