package LinSound;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import processing.core.*;

public class LinSound {
	//pointer to the processing applet
	private PApplet parent;
	private PrintWriter outToClient = null;
    private ServerSocket Server = null;
    private Socket connected = null;
    private int connectionPort = 51000;
	private boolean ifHold;
	public LinSound(PApplet parent, boolean holdValue) {
		this.parent = parent;
		this.ifHold = holdValue;
		parent.registerDispose(this);
		this.createConnection();
	}

	public LinSound(PApplet parent, int portNum, boolean holdValue) {
		this.parent = parent;
		this.connectionPort = portNum;
		this.ifHold = holdValue;
		parent.registerDispose(this);
		this.createConnection();
	}
	
	public void createConnection() {
		String OS = System.getProperty("os.name");
		if(OS.substring(0,0).equalsIgnoreCase("w")) {
			try {
				Runtime.getRuntime().exec("C:/Program Files/Google/Picasa3/Picasa3.exe");
				} catch(IOException e){}			
		} 
		else {
			
			String libraryDirectory = System.getProperty("user.home") +"/sketchbook/libraries/LinSound/library/";
			if(this.ifHold){
				String[] theP = new String[7];
				theP[0] = "xterm";
				theP[1] = "-hold"; 
				theP[2] = "-e";
				theP[3] = "perl";
				theP[4] = "" + libraryDirectory + "launch.pl";
				theP[5] = "" + libraryDirectory;
				theP[6] = Integer.toString(connectionPort);
				try {
					Runtime.getRuntime().exec(theP);
					} catch(IOException e){}
			}
			else {
				String[] theP = new String[6];
				theP[0] = "xterm";
				theP[1] = "-e";
				theP[2] = "perl";
				theP[3] = "" + libraryDirectory + "launch.pl";
				theP[4] = "" + libraryDirectory;
				theP[5] = "" + Integer.toString(connectionPort);			
				try {
					Runtime.getRuntime().exec(theP);
					} catch(IOException e){}
			}	
		}
		
        try {
            Server = new ServerSocket (connectionPort);
            } catch(Exception e) {}
        System.out.println("LinSound waiting for client on port " + connectionPort);
 
    	try {
    		connected = Server.accept();
    		outToClient = new PrintWriter(connected.getOutputStream(),true);
    		} catch(Exception e) {}  

	}
	public void stopEngine() {
		String toclient = "drop\0";
		outToClient.println(toclient);
	}
	 
	public PrintWriter getWriter() {
		return outToClient;
	}
	
	public String getSketchPath() {
		return parent.sketchPath;
	}

    public void dispose() {
    	this.stopEngine();
	    // anything in here will be called automatically when 
	    // the parent applet shuts down. for instance, this might
	    // shut down a thread used by this library.
	    // note that this currently has issues, see Issue 43:
	    // http://code.google.com/p/processing/issues/detail?id=43
	}
}
