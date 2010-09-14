package LinSound;

import java.io.PrintWriter;

public class MusicPlayer {
	private LinSound soundEngine;
	private String soundFile;
	private PrintWriter writeTo;
	public MusicPlayer(LinSound theSoundEngine, String soundName) {
		this.soundEngine = theSoundEngine;
		this.soundFile = soundEngine.getSketchPath() + "/data/" + soundName;
		this.writeTo = soundEngine.getWriter();
		
		String toclient = "create#" + this.soundFile + "\0"; 
		writeTo.println(toclient);
	}
	
	/*
	 * Plays this sound file from it's current location once till the end
	 */
	public void play() {
		String toclient = "play#" + this.soundFile + "\0"; 
		writeTo.println(toclient);		
	}
	
	/*
	 * Stop playing the sound and rewind it to the beginning
	 */
	public void stop() {
		String toclient = "stop#" + this.soundFile + "\0";
		writeTo.println(toclient);
	}
	/*
	 * Play the sound and continue looping it
	 */
	public void loop() {
		String toclient = "loop#" + this.soundFile + "\0";
		writeTo.println(toclient);
	}
	
	/*
	 * Pause the sound at it's current location
	 */
	public void pause() {
		String toclient = "pause#" + this.soundFile + "\0";
		writeTo.println(toclient);
	}
}
