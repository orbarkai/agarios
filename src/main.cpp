#include <iostream>
#include "services/Console.h"
#include "services/Utils.h"

int main()
{

    Console::startSection(Console::paint("cyan", "Agarios"));

    Console::endSection();

    return 0;

}