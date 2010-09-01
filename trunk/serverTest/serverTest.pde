import LinSound.*;

void setup()
{
   size(800,600);
   String[] theP = { "perl","/home/taztwister/Documents/EVL/LinSound/launch.pl" };
   //exec(theP);
}


void draw() {
  background(25,155,200);
}

void keyPressed() {
   LinSound myEngine = new LinSound(this);
   Sounds newSound = new Sounds(myEngine, "fxnuabo.mp3");
}

