import LinSound.*;
String[] theP = { "xterm","-e","perl","/home/taztwister/Documents/EVL/Lin/trunk/launch.pl" };
void setup()
{
   size(800,600);
   exec(theP); 
   LinSound myEngine = new LinSound(this,6002);
   MusicPlayer newSound = new MusicPlayer(myEngine, "fxnuabo.mp3");
   
}


void draw() {
  background(25,155,200);
}

