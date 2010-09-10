import LinSound.*;

void setup()
{
   size(800 ,600);
   LinSound myEngine = new LinSound(this,6002);
   MusicPlayer newSound = new MusicPlayer(myEngine, "fxnuabo.mp3");
   
}

void draw() {
  background(25,155,200);
}

