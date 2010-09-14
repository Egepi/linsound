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

//Global Variables
char soundNames[100][255];
ISound* soundObjects[100];
int numOfSounds = 0;

/*********************************************************************
 * createSound()
 * Creates a sound object, but does not play the file
 */
void createSound(char* fileName) {
	soundObjects[numOfSounds] = engine->play2D(fileName, false,true, true, ESM_AUTO_DETECT,false);
	strcpy(soundNames[numOfSounds],(char*)soundObjects[numOfSounds]->getSoundSource()->getName());
	numOfSounds++;
}//End createSound()

/*********************************************************************
*/
int findSound(string fileName) {
	cout << "Method Start: find\n     Name: " << fileName << endl;
	int i = 0;
	for(i; i < numOfSounds; i++) {
		if(fileName.compare(soundNames[i]) == 0) {
			printf("Method End: find w/ >0\n");			
			return i;
		}
	}
		printf("Method End: find w/ -1\n");
		return -1;
}//End findSound()

/*********************************************************************
*/
void playSound(string remainingCommand) {
	cout << "Method Start: play\n";
	int theSound = findSound(remainingCommand);
	printf("The sound: %d\n", theSound);
	if( theSound >= 0 )
		soundObjects[theSound]->setIsPaused(false);
	cout << "Method End: play\n";
}//End playSound()

/*********************************************************************
*/
void pauseSound(string remainingCommand) {
	int theSound = findSound(remainingCommand);
	if( theSound >= 0 )
		soundObjects[theSound]->setIsPaused(true);
}//End pauseSound()

/*********************************************************************
*/
void stopSound(string remainingCommand) {

}//End stopSound()

/*********************************************************************
*/
void loopSound(string remainingCommand) {

}//End loopSound()

/*********************************************************************
*/
void closeServer() {
	cout << "good bye!\n";
	engine->drop();
	exit(0);
}//End closeServer()

/*********************************************************************
 * makeConnection()
 * Sets up the connection to the java/processing application.
 */
void makeConnection() {
       // host = gethostbyname("131.193.79.160");
        struct hostent *host;
        struct sockaddr_in server_addr;  
        host = gethostbyname("127.0.0.1");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(6002);

        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }

}//End makeConnection()

/*********************************************************************
 * selectAction
 * Reads the input from the processing app and decides what action to take
 */
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
	} else if(theAction.compare("play") == 0) {
		cout << "Action: play\n";
		playSound(remainingInput);
	} else if(theAction.compare("pause") == 0) {
		cout << "Action: pause\n";
		pauseSound(remainingInput);
	} else if(theAction.compare("stop") == 0) {
		cout << "Action: stop\n";
		stopSound(remainingInput);
	} else if(theAction.compare("loop") == 0) {
		cout << "Action: loop\n";
		loopSound(remainingInput);
	} else if(theAction.compare("drop") == 0) {
		cout << "Action: drop\n";
		closeServer();
	}
}//End selectAction()

/*********************************************************************
*/
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
	   if(bytes_recieved == 0) {
	   	cout << "good bye!\n";
		engine->drop();
		exit(0);
	   }
        recv_data[bytes_recieved] = '\0';
	   dataIn = recv_data;
	   printf("the data in: %s\n", recv_data);
	   selectAction(engine, dataIn);
        
     }
	engine->drop();
	return 0;
}//End main()

//EOF



