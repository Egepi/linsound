package LinSound;

import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import processing.core.*;

public class LinSound {
	
	Runtime a = Runtime.getRuntime();
	a.exec("picassa.exe");
	
	PApplet parent;
	private PrintWriter outToClient = null;
	private ServerSocket Server = null;
	private Socket connected = null;
	
	public LinSound(PApplet parent) 
	{
		this.parent = parent;
		parent.registerDispose(this);
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
	 
	public PrintWriter getToClient() {
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
