package com.amu.flappybird;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.res.AssetManager;
import android.content.res.Resources;
import android.opengl.GLSurfaceView;

public class NativeRenderer implements GLSurfaceView.Renderer{

	// screen width and height
	int width, height;
	
	// desired frame rate
	long fps = (long) (1.0 / 60.0);
	
	public NativeRenderer(Resources resources){
		nativeOnStart();
		
		// set asset manager for use with ndk for loading assets (very important)
		AssetManager manager = resources.getAssets();
		nativeSetAssetManager(manager);
	}
	
	public void onDrawFrame(GL10 gl) {
		long startTime = System.currentTimeMillis();
		
		// update and render scene
		nativeOnRender();
		
		long endTime = System.currentTimeMillis();
		long delta = endTime - startTime;
		
		if (delta < fps){
			try {
				Thread.sleep(fps - delta);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		width = w;
		height = h;
		nativeOnSurfaceCreated(width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	}
	
	public void onTouch(int x, int y, int touchDown){
		nativeOnTouch(x, y, touchDown);
	}
	
	public void OnQuit(){
		nativeOnQuit();
	}
	
	public void pause(){
		nativeOnPause();
	}
	
	public void resume(){
		nativeOnResume();
	}
	
	public static native void nativeOnStart();
	public static native void nativeSetAssetManager(AssetManager assetManager);
	public static native void nativeOnSurfaceCreated(int width, int height);
	public static native void nativeOnRender();
	public static native void nativeOnTouch(int x, int y, int touchDown);
	public static native void nativeOnPause();
	public static native void nativeOnResume();
	public static native void nativeOnQuit();
	
	static{
		System.loadLibrary("FlappyBird");
	}
}
