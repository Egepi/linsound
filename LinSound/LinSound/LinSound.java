package LinSound;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import processing.core.*;

public class LinSound {
	//pointer to the processing applet
	PApplet parent;
	private PrintWriter outToServer = null;
	private Socket clientSocket = null;
	
	public LinSound(PApplet parent) 
	{
		this.parent = parent;
		parent.registerDispose(this);
		this.createConnection();
	}
	
	@SuppressWarnings("unused")
	public void createConnection()
	{
		String OS = System.getProperty("os.name");
		if(OS.substring(0,0).equalsIgnoreCase("w"))
		{
			try{
				Runtime.getRuntime().exec("C:/Program Files/Google/Picasa3/Picasa3.exe");
				}
			catch(IOException e){}			
		}
		else
		{
			String[] theP = { "perl","/home/taztwister/Documents/irrK/irrKlang-1.3.0b/irrKlang-1.3.0/examples/SoundLib/launch.pl" };
			try{
				Runtime.getRuntime().exec(theP);
				}
			catch(IOException e){}	
		}
        try {
        	clientSocket = new Socket("localhost", 51000);
            } catch(Exception e) {}
        try {
        	PrintWriter outToServer = new PrintWriter(clientSocket.getOutputStream(),true);
            } catch(Exception e) {}    
           
        
	}
	public void stopEngine() 
	{
		String toclient = "drop\0";
		outToServer.println(toclient);
	}
	 
	public PrintWriter getToServer() {
		return outToServer;
	}
	
	public String getSketchPath()
	{
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
