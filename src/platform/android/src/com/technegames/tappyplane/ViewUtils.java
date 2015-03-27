package com.technegames.tappyplane;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Point;
import android.os.Build;
import android.os.Build.VERSION;
import android.view.Display;

public final class ViewUtils
{
    @SuppressLint("NewApi")
    @SuppressWarnings("deprecation")
    public static Point getScreenSize(Activity activity)
    {
        Display display = activity.getWindowManager().getDefaultDisplay();
        Point size = new Point();

        if (VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2)
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

    private ViewUtils()
    {
        // Hide Constructor
    }
}