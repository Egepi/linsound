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

//#if defined(WIN32)
//#include <conio.h>
//#else
//#include "../common/conio.h"
//#endif


using namespace irrklang;
using namespace std;
ISoundEngine* engine;
int sock;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

void selectAction(ISoundEngine* e1, string);
void makeConnection();
void createSound(char*);

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
	   selectAction(engine, dataIn);
   
        /*printf("\nSEND (q or Q to quit) : ");
        gets(send_data);
           
        if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)
        	send(sock,send_data,strlen(send_data), 0); 

        else
        {
        	send(sock,send_data,strlen(send_data), 0);   
          close(sock);
          break;
        }*/
        
     }
	engine->drop();
	return 0;
}

//Sets up the connection to the java/processing application.
void makeConnection() {
 
        struct hostent *host;
        struct sockaddr_in server_addr;  
		
	   host = gethostbyname("127.0.0.1");
        //host = gethostbyname("131.193.79.160");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        	perror("Socket");
        	exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(51000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
}//End makeConnection()

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
		engine->drop();
		exit(0);
	}
}

void createSound(char* fileName) {
	ISound* myNewSound = engine->play2D(fileName, false, false, true);
	myNewSound->setIsLooped(true);
	myNewSound->setIsPaused(false);
	cout << "MY attemp: " << myNewSound->getSoundSource()->getName() << endl;	
	//engine->play2D(myNewSound);
}
