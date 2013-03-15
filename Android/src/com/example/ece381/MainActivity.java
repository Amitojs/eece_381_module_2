package com.example.ece381;

import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Settings {
	
    
    TextView textviewone;
    Button a_button;
    Button asharp_button;
    Button b_button;
    Button c_button;
    Button csharp_button;
    Button d_button;
    Button dsharp_button;
    Button e_button;
    Button f_button;
    Button fsharp_button;
    Button g_button;
    Button gsharp_button;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        a_button = (Button) findViewById(R.id.button_a);			// retrieves button id for the a button
        asharp_button = (Button) findViewById(R.id.button_asharp);	// retrieves button id for the a sharp button
        b_button = (Button) findViewById(R.id.button_b);			// retrieves button id for the b button
        c_button = (Button) findViewById(R.id.button_c);			// retrieves button id for the c button
        csharp_button = (Button) findViewById(R.id.button_csharp);	// retrieves button id for the c sharp button
        d_button = (Button) findViewById(R.id.button_d);			// retrieves button id for the d button
        dsharp_button = (Button) findViewById(R.id.button_dsharp);	// retrieves button id for the d sharp button
        e_button = (Button) findViewById(R.id.button_e);			// retrieves button id for the e button
        f_button = (Button) findViewById(R.id.button_f);			// retrieves button id for the f button
        fsharp_button = (Button) findViewById(R.id.button_fsharp);	// retrieves button id for the f sharp button
        g_button = (Button) findViewById(R.id.button_g);			// retrieves button id for the g button
        gsharp_button = (Button) findViewById(R.id.button_gsharp);	// retrieves button id for the g sharp button        
      
        check_button();    
    }
    
    

	@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

	public  void check_button(){
		// PURPOSE: Checks whether a button has been pressed
		// RETURNS: Nothing
        a_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action A..."); 	// testing purposes!
                    sendkey("1A");
                    handler.postDelayed(this, 500);
                }
            };

        });

        asharp_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action A#..."); 	// testing purposes!
                    sendkey("1A#");
                    handler.postDelayed(this, 500);
                }
            };

        });
               
        b_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action B..."); 	// testing purposes!
                    sendkey("1B");
                    handler.postDelayed(this, 500);
                }
            };

        });
 
        c_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action C..."); 	// testing purposes!
                    sendkey("1C");
                    handler.postDelayed(this, 500);
                }
            };

        });

        csharp_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action C#..."); 	// testing purposes!
                    sendkey("1C#");
                    handler.postDelayed(this, 500);
                }
            };

        });
        
        d_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action D..."); 	// testing purposes!
                    sendkey("1D");
                    handler.postDelayed(this, 500);
                }
            };

        });

        dsharp_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action D#..."); 	// testing purposes!
                    sendkey("1D#");
                    handler.postDelayed(this, 500);
                }
            };

        });
        
        e_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action E..."); 	// testing purposes!
                    sendkey("1E");
                    handler.postDelayed(this, 500);
                }
            };

        });

        f_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action F..."); 	// testing purposes!
                    sendkey("1F");
                    handler.postDelayed(this, 500);
                }
            };

        });

        fsharp_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action F#..."); 	// testing purposes!
                    sendkey("1F#");
                    handler.postDelayed(this, 500);
                }
            };

        });
        
        g_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action G..."); 	// testing purposes!
                    sendkey("1G");
                    handler.postDelayed(this, 500);
                }
            };

        });

        gsharp_button.setOnTouchListener(new View.OnTouchListener() {
        	// listens for c_button to be pressed
            private Handler handler;	// handler to deal with the event
            @Override 
            public boolean onTouch(View v, MotionEvent event) {
            	// onTouch() is a singular event
            	// Cannot be used to check if the user is still performing the action
                switch(event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                	// user has pressed down the screen
                    if (handler != null) return true;
                    handler = new Handler();
                    handler.postDelayed(mAction, 100);
                    break;
                case MotionEvent.ACTION_UP:
                	// user has pressed upwards on the screen
                    if (handler == null) return true;
                    handler.removeCallbacks(mAction);
                    handler = null;
                    break;
                }
                return false;
            }
            Runnable mAction = new Runnable() {
            	// Runnable will keep running until the event has finished
                @Override public void run() {
                    System.out.println("Performing action G#..."); 	// testing purposes!
                    sendkey("1G#");
                    handler.postDelayed(this, 500);
                }
            };

        });
         
	}
	
    
}
