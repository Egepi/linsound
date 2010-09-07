package LinSound;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import processing.core.*;

public class LinSound {
	//pointer to the processing applet
	PApplet parent;
	private PrintWriter outToClient = null;
    private ServerSocket Server = null;
    private Socket connected = null;
	
	public LinSound(PApplet parent) 
	{
		this.parent = parent;
		parent.registerDispose(this);
		this.createConnection();
	}
	
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
            Server = new ServerSocket (51000);
            } catch(Exception e) {}
        System.out.println ("TCPServer Waiting for client on port 51000");
 
    	try {
    		connected = Server.accept();
    		outToClient = new PrintWriter(connected.getOutputStream(),true);
    		} catch(Exception e) {}  

	}
	public void stopEngine() 
	{
		String toclient = "drop\0";
		outToClient.println(toclient);
	}
	 
	public PrintWriter getToServer() {
		return outToClient;
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
