package LinSound;

import java.io.PrintWriter;

public class MusicPlayer {
	private LinSound soundEngine;
	private String soundFile;
	private PrintWriter toServer;
	public MusicPlayer(LinSound theSoundEngine, String soundName) {
		this.soundEngine = theSoundEngine;
		this.soundFile = soundEngine.getSketchPath() + "/data/" + soundName;
		this.toServer = soundEngine.getToServer();
		
		String toclient = "create#" + this.soundFile + "\0"; 
		toServer.println(toclient);
	}
	
	public void play() {
		String toclient = "play#" + this.soundFile + "\0"; 
		toServer.println(toclient);		
	}
	
	public void stop() {
		String toclient = "stop#" + this.soundFile + "\0";
		toServer.println(toclient);
	}
	
	public void loop() {
		String toclient = "loop#" + this.soundFile + "\0";
		toServer.println(toclient);
	}
	
	public void pause() {
		String toclient = "pause#" + this.soundFile + "\0";
		toServer.println(toclient);
	}
}
