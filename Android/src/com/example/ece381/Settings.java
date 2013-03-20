package com.example.ece381;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class Settings extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		
		// This call will result in better error messages if you
		// try to do things in the wrong thread.
		StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
				.detectDiskReads().detectDiskWrites().detectNetwork()
				.penaltyLog().build());

		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_settings);
		
		//Method to initialize IP Addresses
		LoadPreferences();
		Button gotomenu = (Button) findViewById(R.id.button1);
		gotomenu.setTextColor(Color.RED);
		gotomenu.setText("Go To Menu");
		
		TCPReadTimerTask tcp_task = new TCPReadTimerTask();
		Timer tcp_timer = new Timer();
		tcp_timer.schedule(tcp_task, 3000, 500);

	}

	
	// Route called when the user presses "connect"
	public void openSocket(View view) {
		MyApplication app = (MyApplication) getApplication();
		TextView msgbox = (TextView) findViewById(R.id.error_message_box);

		// Make sure the socket is not already opened 
		if (app.sock != null && app.sock.isConnected() && !app.sock.isClosed()) {
			msgbox.setText("Socket already open");
			return;
		}
		
		// open the socket.  SocketConnect is a new subclass
	    // (defined below).  This creates an instance of the subclass
		// and executes the code in it.
		new SocketConnect().execute((Void) null);
		
		if (app.sock != null && app.sock.isConnected()) {
			msgbox.setText("Socket Opened");
		}
		
	}

	//  Called when the user wants to send a message
	public void sendkey(String msg) {
		MyApplication app = (MyApplication) getApplication();
		
		
		// Create an array of bytes.  First byte will be the
		// message length, and the next ones will be the message
		byte buf[] = new byte[msg.length() + 1];
		buf[0] = (byte) msg.length(); 
		System.arraycopy(msg.getBytes(), 0, buf, 1, msg.length());

		
		// Now send through the output stream of the socket
		OutputStream out;
		try {
			out = app.sock.getOutputStream();
			try {
				out.write(buf, 0, msg.length() + 1);
			} catch (IOException e) {
				e.printStackTrace();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	
	// Called when the user closes a socket
	public void closeSocket(View view) {
		MyApplication app = (MyApplication) getApplication();
		Socket s = app.sock;
		TextView msgbox = (TextView) findViewById(R.id.error_message_box);
		try {
			s.getOutputStream().close();
			s.close();
			msgbox.setText("Socket Closed");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	
	
	// Construct an IP address from the four boxes, also saves IP addresses.
	public String getConnectToIP() {
		String addr = "";
		EditText text_ip;
		text_ip = (EditText) findViewById(R.id.ip1);
		addr += text_ip.getText().toString();
		SavePreferences("ip1", text_ip.getText().toString());
		text_ip = (EditText) findViewById(R.id.ip2);
		addr += "." + text_ip.getText().toString();
		SavePreferences("ip2", text_ip.getText().toString());
		text_ip = (EditText) findViewById(R.id.ip3);
		addr += "." + text_ip.getText().toString();
		SavePreferences("ip3", text_ip.getText().toString());
		text_ip = (EditText) findViewById(R.id.ip4);
		addr += "." + text_ip.getText().toString();
		SavePreferences("ip4", text_ip.getText().toString());
		return addr;
	}

	
	// Gets the Port from the appropriate field.
	public Integer getConnectToPort() {
		Integer port;
		EditText text_port;

		text_port = (EditText) findViewById(R.id.port);
		port = Integer.parseInt(text_port.getText().toString());

		return port;
	}


    // This is the Socket Connect asynchronous thread.  Opening a socket
	// has to be done in an Asynchronous thread in Android.  Be sure you
	// have done the Asynchronous Tread tutorial before trying to understand
	// this code
	public class SocketConnect extends AsyncTask<Void, Void, Socket> {

		// The main parcel of work for this thread.  Opens a socket
		// to connect to the specified IP.
		
		protected Socket doInBackground(Void... voids) {
			Socket s = null;
			String ip = getConnectToIP();
			Integer port = getConnectToPort();

			try {
				s = new Socket(ip, port);
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return s;
		}

		// After executing the doInBackground method, this is 
		// automatically called, in the UI (main) thread to store
		// the socket in this app's persistent storage
		protected void onPostExecute(Socket s) {
			MyApplication myApp = (MyApplication) Settings.this
					.getApplication();
			myApp.sock = s;
		}
		
	}

	//Method used to save variables such as the IP addresses
	private void SavePreferences(String key, String value){
		SharedPreferences sharedPreferences = getPreferences(MODE_PRIVATE);
		SharedPreferences.Editor editor = sharedPreferences.edit();
		editor.putString(key, value);
		editor.commit();
	}

	//Method used to save Load IP addresses
	private void LoadPreferences(){
		SharedPreferences sharedPreferences = getPreferences(MODE_PRIVATE);	
		String adress1 = sharedPreferences.getString("ip1", "");
		EditText et1 = (EditText)findViewById(R.id.ip1);
		et1.setText(adress1);
		String adress2 = sharedPreferences.getString("ip2", "");
		EditText et2 = (EditText)findViewById(R.id.ip2);
		et2.setText(adress2);
		String adress3 = sharedPreferences.getString("ip3", "");
		EditText et3 = (EditText)findViewById(R.id.ip3);
		et3.setText(adress3);
		String adress4 = sharedPreferences.getString("ip4", "");
		EditText et4 = (EditText)findViewById(R.id.ip4);
		et4.setText(adress4);
	}
	
	public void gotomenu(View view){
		Intent openMainActivity = new Intent("com.example.ece381.MENU");
		startActivity(openMainActivity);	
	}
	
	public class TCPReadTimerTask extends TimerTask {
		public void run() {
			MyApplication app = (MyApplication) getApplication();
			if (app.sock != null && app.sock.isConnected()
					&& !app.sock.isClosed()) {
				
				try {
					InputStream in = app.sock.getInputStream();

					// See if any bytes are available from the Middleman
					
					int bytes_avail = in.available();
					if (bytes_avail > 0) {
						
						// If so, read them in and create a sring
						
						byte buf[] = new byte[bytes_avail];
						in.read(buf);

						final String s = new String(buf, 0, bytes_avail, "US-ASCII");
		
						// As explained in the tutorials, the GUI can not be
						// updated in an asyncrhonous task.  So, update the GUI
						// using the UI thread.
						
						runOnUiThread(new Runnable() {
							public void run() {
								EditText et = (EditText) findViewById(R.id.RecvdMessage);
								if(s.contentEquals("ready")){
									et.setText("ready");
								}else{
									et.setText("Not Ready");
								}
								
								
							}
						});
						
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
}
