package com.technegames.tappyplane;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Point;
import android.media.AudioManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;

public final class MainActivity extends Activity
{
    private static final Logger logger = new Logger(MainActivity.class);

    protected RendererWrapper _rendererWrapper;
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

        Point size = ViewUtils.getScreenSize(this);

        if (Logger.isDebugEnabled())
        {
            logger.debug("dimension " + size.x + " x " + size.y);
        }

        _rendererWrapper = new RendererWrapper(this, size.x, size.y);
        _glSurfaceView = new GLSurfaceView(this);
        _glSurfaceView.setEGLContextClientVersion(2);
        _glSurfaceView.setRenderer(_rendererWrapper);

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
                            _rendererWrapper.handleTouchDown(event.getX(pointerIndex), event.getY(pointerIndex));
                            break;
                        case MotionEvent.ACTION_UP:
                        case MotionEvent.ACTION_POINTER_UP:
                        case MotionEvent.ACTION_CANCEL:
                            _rendererWrapper.handleTouchUp(event.getX(pointerIndex), event.getY(pointerIndex));
                            break;
                        case MotionEvent.ACTION_MOVE:
                            for (int i = 0; i < event.getPointerCount(); i++)
                            {
                                pointerIndex = i;
                                _rendererWrapper.handleTouchDragged(event.getX(pointerIndex), event.getY(pointerIndex));
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
        _rendererWrapper.onResume();
    }

    @Override
    protected void onPause()
    {
        _rendererWrapper.onPause();
        _glSurfaceView.onPause();

        super.onPause();
    }

    @Override
    public void onBackPressed()
    {
        if (_rendererWrapper.handleOnBackPressed())
        {
            return;
        }

        super.onBackPressed();
    }
}