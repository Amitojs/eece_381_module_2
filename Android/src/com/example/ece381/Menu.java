package com.example.ece381;

import android.os.Bundle;
import android.app.ListActivity;
import android.content.Intent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class Menu extends ListActivity {

	String activity_names[] = {"Settings", "Piano"};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setListAdapter(new ArrayAdapter<String>(Menu.this, android.R.layout.simple_list_item_1, activity_names));
	}

	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		super.onListItemClick(l, v, position, id);
		try {
			Class MainActivityClass = Class.forName("com.example.ece381." + activity_names[position]);
			Intent MainActivityIntent = new Intent(Menu.this, MainActivityClass);
			startActivity(MainActivityIntent);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
}
