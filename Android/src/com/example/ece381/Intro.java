//Class which displays the splash screen at the start of the Android Application

package com.example.ece381;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;

public class Intro extends Activity {

	MediaPlayer intro_song;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_intro);
		intro_song = MediaPlayer.create(Intro.this, R.raw.supermario_theme);
		intro_song.start();
		
		//Creates a thread which sleeps for 2 seconds, and then starts the Menu activity
		Thread timer = new Thread(){
			@Override
			public void run(){
				try{
					sleep(2000);
				}catch(InterruptedException e){
					e.printStackTrace();
				}finally{
					Intent openMainActivity = new Intent("com.example.ece381.MENU");
					startActivity(openMainActivity);
				}
			};			
		};

		timer.start();
	}

	@Override
	protected void onPause() {
		super.onPause();
		intro_song.release();
		finish();
	}

	
}
