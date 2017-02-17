#include <iostream>

#include "Server.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Io-Server start" << endl;

    Server server = Server();

    server.Init("qqq");
    server.Run();

	return 0;
}

