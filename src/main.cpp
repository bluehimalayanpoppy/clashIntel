#include <iostream>
#include <cstdlib>
#include "ClashClient.h"

int main (int argc, char ** argv) 
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <player_tag>\n";
        return 1;
    }

    const char* token = std::getenv("CLASH_API_TOKEN");
    if (!token) {
        std::cerr << "Error: set CLASH_API_TOKEN environment variable\n";
        return 1;
    }

    ClashClient client(token);
    std::cout << client.getPlayer(argv[1]) << "\n";

    return 0;
}
