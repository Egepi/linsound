import LinSound.*;

MusicPlayer newSound;
void setup()
{
   size(800 ,600);
   LinSound myEngine = new LinSound(this,6002);
   newSound = new MusicPlayer(myEngine, "fxnuabo.mp3");
   
}

void draw() {
  background(25,155,200);
}

void keyPressed() {
  if(key == 'p')
    newSound.play();
  if(key == 'u')
    newSound.pause(); 
}
