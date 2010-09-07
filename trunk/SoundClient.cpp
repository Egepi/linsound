#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <irrKlang.h>
#include <ik_ISoundEngine.h>
#include <iostream>
#include <sys/uio.h>
#include <sys/select.h>
#include <sys/stat.h>

#if defined(WIN32)
#include <conio.h>
#else
#include "conio.h"
#endif


using namespace irrklang;
using namespace std;
ISoundEngine* engine;
int sock;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

void selectAction(ISoundEngine* e1, string);
void makeConnection();
void createSound(char*);

int server_sock;

int main(int argc, const char** argv)
{
	char send_data[1024],recv_data[1024];
	int bytes_recieved;
	string dataIn = ""; 

	// start the sound engine with default parameters
	engine = createIrrKlangDevice();

	if (!engine) {
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	
	makeConnection(); //Connect to processing/java

     while(1)
     {
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved] = '\0';
	   dataIn = recv_data;
	   printf("the data in: %s\n", recv_data);
	   selectAction(engine, dataIn); 
     }
}

/************************************************************/
//Sets up the connection to the java/processing application.
void makeConnection() {	

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}
	
	// allow fast reuse of ports 
	int reuse_true = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_true, sizeof(reuse_true));

	struct sockaddr_in addr; 	// internet socket address data structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(51000); // byte order is significant
	addr.sin_addr.s_addr = INADDR_ANY; // listen to all interfaces
	
	int res = bind(server_sock, (struct sockaddr*)&addr, sizeof(addr));
	if(res < 0) {
		perror("Error binding to port");
		exit(1);
	}

	struct sockaddr_in remote_addr;
	unsigned int socklen = sizeof(remote_addr); 

	while(1) {
		// wait for a connection
		res = listen(server_sock,0);
		if(res < 0) {
			perror("Error listening for connection");
			exit(1);
		}
		
		int sock;
		sock = accept(server_sock, (struct sockaddr*)&remote_addr, &socklen);
		if(sock < 0) {
			perror("Error accepting connection");
			exit(1);
		} else {
			break;
		}
	}


}//End makeConnection()

/************************************************************/
void selectAction(ISoundEngine* e1, string theData) {
	//Pull the action to be preformed out from the input string	
	int thePos = theData.find_first_of("#");
	string theAction = theData.substr(0,thePos);

	//Store the remaining part of the input string into another string
	string remainingInput = theData.substr(thePos+1, theData.length());
	char *remainingChar = (char*)remainingInput.c_str();
	
	//Determine which action should be taken
	if(theAction.compare("create") == 0) {
		createSound(remainingChar);
	} else if(theAction.compare("drop") == 0) {
		cout << "good bye!\n";
		shutdown(sock,SHUT_RDWR);
		close(sock);
		shutdown(server_sock,SHUT_RDWR);
		engine->drop();
		exit(0);
	}
}

/************************************************************/
void createSound(char* fileName) {
	printf("The filename: %s\n", fileName);
	ISound* myNewSound = engine->play2D(fileName, true, true, true, ESM_AUTO_DETECT,false);
	//myNewSound->setIsLooped(true);
	myNewSound->setIsPaused(false);
	cout << "MY attemp: " << myNewSound->getSoundSource()->getName() << endl;	
	//engine->play2D(myNewSound);
}
