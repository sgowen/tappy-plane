package com.gowengamedev.tappyplane;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Point;
import android.media.AudioManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;

public final class MainActivity extends Activity
{
    private GameRenderer _gameRenderer;
    private GLSurfaceView _glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        // Do the stuff that initialize() would do for you
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FORCE_NOT_FULLSCREEN);

        setContentView(R.layout.activity_main);

        Point size = getScreenSize();

        Log.d("MainActivity", "dimension " + size.x + " x " + size.y);

        _gameRenderer = new GameRenderer(this, size.x, size.y);
        _glSurfaceView = new GLSurfaceView(this);
        _glSurfaceView.setEGLContextClientVersion(2);
        _glSurfaceView.setRenderer(_gameRenderer);

        LinearLayout gameContainer = (LinearLayout) findViewById(R.id.game);
        gameContainer.addView(_glSurfaceView);

        setVolumeControlStream(AudioManager.STREAM_MUSIC);

        _glSurfaceView.setOnTouchListener(new OnTouchListener()
        {
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, final MotionEvent event)
            {
                synchronized (this)
                {
                    int action = event.getAction() & MotionEvent.ACTION_MASK;
                    int pointerIndex = (event.getAction() & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;

                    switch (action)
                    {
                        case MotionEvent.ACTION_DOWN:
                        case MotionEvent.ACTION_POINTER_DOWN:
                            _gameRenderer.handleTouchDown(event.getX(pointerIndex), event.getY(pointerIndex));
                            break;
                        case MotionEvent.ACTION_UP:
                        case MotionEvent.ACTION_POINTER_UP:
                        case MotionEvent.ACTION_CANCEL:
                            _gameRenderer.handleTouchUp(event.getX(pointerIndex), event.getY(pointerIndex));
                            break;
                        case MotionEvent.ACTION_MOVE:
                            for (int i = 0; i < event.getPointerCount(); i++)
                            {
                                pointerIndex = i;
                                _gameRenderer.handleTouchDragged(event.getX(pointerIndex), event.getY(pointerIndex));
                            }
                            break;
                    }

                    return true;
                }
            }
        });
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        _glSurfaceView.onResume();
        _gameRenderer.onResume();
    }

    @Override
    protected void onPause()
    {
        _gameRenderer.onPause();
        _glSurfaceView.onPause();

        super.onPause();
    }

    @Override
    public void onBackPressed()
    {
        if (_gameRenderer.handleOnBackPressed())
        {
            return;
        }

        super.onBackPressed();
    }

    @SuppressLint("NewApi")
    @SuppressWarnings("deprecation")
    private Point getScreenSize()
    {
        Display display = getWindowManager().getDefaultDisplay();
        Point size = new Point();

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2)
        {
            display.getSize(size);
        }
        else
        {
            size.x = display.getWidth();
            size.y = display.getHeight();
        }

        return size;
    }
}