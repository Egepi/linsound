package LinSound;

import java.io.PrintWriter;

public class MusicPlayer {
	private LinSound soundEngine;
	private String soundFile;
	private PrintWriter writeTo;
	private String theSoundName;
	public MusicPlayer(LinSound theSoundEngine, String soundName) {
		this.soundEngine = theSoundEngine;
		this.theSoundName = soundName;
		this.soundFile = soundEngine.getSketchPath() + "/data/" + this.theSoundName;
		this.writeTo = soundEngine.getWriter();
		
		String toclient = "create#" + this.soundFile + "\0"; 
		writeTo.println(toclient);
	}
	
	/*
	 * Plays this sound file from it's current location once till the end
	 */
	public void play() {
		String toclient = "play#" + this.theSoundName + "\0"; 
		writeTo.println(toclient);		
	}
	
	/*
	 * Stop playing the sound and rewind it to the beginning
	 */
	public void stop() {
		String toclient = "stop#" + this.theSoundName + "\0";
		writeTo.println(toclient);
	}
	/*
	 * Play the sound and continue looping it
	 */
	public void loop() {
		String toclient = "loop#" + this.theSoundName + "\0";
		writeTo.println(toclient);
	}
	
	/*
	 * Pause the sound at it's current location
	 */
	public void pause() {
		String toclient = "pause#" + this.theSoundName + "\0";
		writeTo.println(toclient);
	}
}
