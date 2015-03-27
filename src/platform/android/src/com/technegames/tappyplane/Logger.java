package com.technegames.tappyplane;

import android.util.Log;

/**
 * @author stephen gowen <stephen.gowen@chexar.com>
 */
public final class Logger
{
    /**
     * @param loggingLevel
     *            "ERROR" for error "WARN" for error and warning "INFO" for
     *            error, warning, and info "DEBUG" for error, warning, info, and
     *            debug Any other String will result in NO LOGGING
     */
    public static void initializeLoggingLevel(String loggingLevel)
    {
        if (loggingLevel.equalsIgnoreCase("DEBUG"))
        {
            Logger.loggingLevel = 4;
        }
        else if (loggingLevel.equalsIgnoreCase("INFO"))
        {
            Logger.loggingLevel = 3;
        }
        else if (loggingLevel.equalsIgnoreCase("WARN"))
        {
            Logger.loggingLevel = 2;
        }
        else if (loggingLevel.equalsIgnoreCase("ERROR"))
        {
            Logger.loggingLevel = 1;
        }
        else
        {
            Logger.loggingLevel = 0;
        }
    }

    public static boolean isErrorEnabled()
    {
        return loggingLevel >= 1;
    }

    public static boolean isWarnEnabled()
    {
        return loggingLevel >= 2;
    }

    public static boolean isInfoEnabled()
    {
        return loggingLevel >= 3;
    }

    public static boolean isDebugEnabled()
    {
        return loggingLevel >= 4;
    }

    private static int loggingLevel = 4;

    private final String TAG;

    public Logger(Class<?> clazz)
    {
        this.TAG = clazz.getSimpleName();
    }

    public void debug(String message)
    {
        if (loggingLevel >= 4)
        {
            Log.d(TAG, "[DEBUG] " + message);
        }
    }

    public void info(String message)
    {
        if (loggingLevel >= 3)
        {
            Log.i(TAG, "[INFO] " + message);
        }
    }

    public void warn(String message)
    {
        if (loggingLevel >= 2)
        {
            Log.w(TAG, "[WARN] " + message);
        }
    }

    public void warn(String message, Exception exception)
    {
        if (loggingLevel >= 2)
        {
            Log.w(TAG, "[WARN] " + message, exception);
        }
    }

    public void error(String message)
    {
        if (loggingLevel >= 1)
        {
            Log.e(TAG, "[ERROR] " + message);
        }
    }

    public void error(String message, Exception exception)
    {
        if (loggingLevel >= 1)
        {
            Log.e(TAG, "[ERROR] " + message, exception);
        }
    }

    public void error(String message, Throwable cause)
    {
        if (loggingLevel >= 1)
        {
            Log.e(TAG, "[ERROR] " + message, cause);
        }
    }
}