package com.amu.flappybird;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;

public class GameActivity extends Activity implements OnTouchListener {

	NativeRenderer renderer;
	GLSurfaceView glSurface;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// hide title bar
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		// create instance of native renderer
		renderer = new NativeRenderer(getResources());
		
		// create new opengl surface
		glSurface = new GLSurfaceView(this);
		
		// window format
		if (getWindowManager().getDefaultDisplay().getPixelFormat() == 1){
			glSurface.setEGLConfigChooser(8, 8, 8, 0, 24, 8);
		}
		else if (getWindowManager().getDefaultDisplay().getPixelFormat() == 4){
			glSurface.setEGLConfigChooser(5, 6, 5, 0, 24, 8);
		}
		
		// opengl context version
		glSurface.setEGLContextClientVersion(2);
		// preserve egl context on pausing
		glSurface.setPreserveEGLContextOnPause(true);
		// set renderer
		glSurface.setRenderer(renderer);
		// add touch listener
		glSurface.setOnTouchListener(this);
		
		// add view to layout
		setContentView(glSurface);	
	}
	
	public boolean onTouch(View view, MotionEvent event) {
		// call native on touch function
		renderer.onTouch((int)event.getX(), (int)event.getY(), event.getAction() == MotionEvent.ACTION_DOWN ? 1 : 0);
		return true;
	}
	
	protected void onDestroy() {
		// destroy native objects
		renderer.OnQuit();
		
		super.onDestroy();
		
		// exit from the application (clean up)
		System.exit(0);
	}
	
	protected void onPause() {
		super.onPause();
		
		// pause native game
		renderer.pause();
		
		// pause glSurface
		glSurface.onPause();
	}
	
	protected void onResume() {
		super.onResume();
		
		// resume native game
		renderer.resume();
		
		// resume glSurface
		glSurface.onResume();
	}
}
