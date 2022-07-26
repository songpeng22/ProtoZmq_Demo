/**
 ******************************************************************************
 * @file    osutils.cpp
 *
 * @par     Project:
 *          operating system abstraction laywer - Copyright (c) 2010 BIZERBA
 * 
 * @version 1
 * @date    04.11.2010
 * @author  thomas buck
 * 
 * @remarks -
 ******************************************************************************
 */
/**
 ******************************************************************************
 * @par     History:
 *          04.11.2010 created
 *
 ******************************************************************************
 */
#ifdef  _MSC_VER
#include <windows.h>
#endif
#ifdef __GNUC__
#include <errno.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <dlfcn.h>
#endif

#include <osutils.h>

#define OSUTILS_TRUE     1
#define OSUTILS_FALSE    0

/*
 ******************************************************************************
 * globals
 ******************************************************************************
 */

#ifdef __GNUC__
Display * g_TonX11Display = NULL;
#endif 

/**
 ******************************************************************************
 * OsUtilsMutexCreate - create a mutex
 *
 * @param    -
 * @return   OSUTILS_SUCCESS   successful
 *           OSUTILS_FAILURE failure
 ******************************************************************************
 */
long OsUtilsMutexCreate(TYtasMutex *tasMutex)
{
    long retCode = OSUTILS_SUCCESS;

#ifdef _MSC_VER
    if(tasMutex->mutexValid == OSUTILS_FALSE)
    {
       	/* Mutex erstellen */
        tasMutex->hMutex = CreateMutex(NULL, 0, NULL);
	    if (tasMutex->hMutex != 0)
	    {
            tasMutex->mutexValid = OSUTILS_TRUE;
	        retCode = OSUTILS_SUCCESS;
	    }
        else
        {
            tasMutex->mutexValid = OSUTILS_FALSE;
            retCode = OSUTILS_FAILURE;
        }
    }
#endif

#ifdef  __GNUC__
    int ret;
    pthread_mutexattr_t attr;

    if(tasMutex->mutexValid == OSUTILS_FALSE)
    {
        /* Mutex-Attribute initialisieren */
        pthread_mutexattr_init(&attr);

        /* Mutex erstellen */
        ret = pthread_mutex_init(&tasMutex->hMutex, &attr /* mutex attributes */);

        /* Thread-Attribute aufloesen */
        pthread_mutexattr_destroy(&attr);

        if(ret == 0)
        {
            tasMutex->mutexValid = OSUTILS_TRUE;
            retCode = OSUTILS_SUCCESS;
        }
        else
        {
            tasMutex->mutexValid = OSUTILS_FALSE;
            retCode  = OSUTILS_FAILURE;
        }
    }
#endif

   return retCode;
}

/**
 ******************************************************************************
 * OsUtilsMutexDelete - delete a mutex
 *
 * @param    -
 * @return   OSUTILS_SUCCESS   successful
 *           OSUTILS_FAILURE failure
 ******************************************************************************
 */
long OsUtilsMutexDelete(TYtasMutex *tasMutex)
{
    long retCode=OSUTILS_SUCCESS;

    if(tasMutex->mutexValid == OSUTILS_TRUE)
    {
#ifdef _MSC_VER
        /* Mutex-Handle loeschen */
	    if (CloseHandle(tasMutex->hMutex))
	    {
            tasMutex->mutexValid = OSUTILS_FALSE;
	        retCode = OSUTILS_SUCCESS;
	    }
        else
        {
            tasMutex->mutexValid = OSUTILS_TRUE;
	        retCode = OSUTILS_FAILURE;
        }
#endif

#ifdef  __GNUC__
        int ret;
        /* Mbox-Mutex loeschen */
        ret = pthread_mutex_destroy(&tasMutex->hMutex);
        if(ret == 0)
        {
            tasMutex->mutexValid = OSUTILS_FALSE;
	        retCode = OSUTILS_SUCCESS;
        }
        else
        {
            tasMutex->mutexValid = OSUTILS_TRUE;
	        retCode = OSUTILS_FAILURE;
        }
#endif
    }

    return retCode;
}

/**
 ******************************************************************************
 * OsUtilsMutexLock - lock a mutex
 *
 * @param    -
 * @return   -
 ******************************************************************************
 */
void OsUtilsMutexLock(TYtasMutex *tasMutex)
{
    /* Mutex lock */
#ifdef  _MSC_VER
    if (tasMutex->mutexValid) WaitForSingleObject(tasMutex->hMutex, INFINITE);
#endif

#ifdef __GNUC__
    if (tasMutex->mutexValid) pthread_mutex_lock(&tasMutex->hMutex);
#endif
}

/**
 ******************************************************************************
 * OsUtilsMutexUnlock - unlock a mutex
 *
 * @param    -
 * @return   -
 ******************************************************************************
 */
void OsUtilsMutexUnlock(TYtasMutex *tasMutex)
{
    /* Mutex unlock */
#ifdef  _MSC_VER
    if (tasMutex->mutexValid) ReleaseMutex(tasMutex->hMutex);
#endif

#ifdef __GNUC__
    if (tasMutex->mutexValid) pthread_mutex_unlock(&tasMutex->hMutex);
#endif
}

/**
 ******************************************************************************
 * OsUtilsSleep - delay for a specified amount of time (milliseconds)
 *
 * @param    time  : amount of milliseconds
 ******************************************************************************
 */
void OsUtilsSleep(unsigned long time)
{
#ifdef _MSC_VER
    Sleep(time);
#endif

#ifdef __GNUC__
    usleep(time*1000);
#endif
}

/**
 ******************************************************************************
 * OsUtilsTonInit - init tone
 ******************************************************************************
 */
void OsUtilsToneInit(void)
{
#ifdef __GNUC__
    if (g_TonX11Display == NULL) 
    {
        g_TonX11Display = XOpenDisplay(NULL);
    }
#endif
    return;
}

/**
 ******************************************************************************
 * OsUtilsTonExit - exit tone
 ******************************************************************************
 */
void OsUtilsToneExit(void)
{
#ifdef __GNUC__
    if (g_TonX11Display != NULL) 
    {
            XCloseDisplay(g_TonX11Display);
            g_TonX11Display = NULL;
    }
#endif
    return;
}

/**
 ******************************************************************************
 * OsUtilsTon - beep over speaker
 ******************************************************************************
 */
void OsUtilsTone(unsigned long frequence, unsigned long duration)
{
#ifdef __GNUC__
    unsigned char tonCycles = 1;
    XKeyboardControl values;
    unsigned long mask = KBBellDuration | KBBellPitch;
    if (g_TonX11Display != NULL) 
    {
        values.bell_duration = tonCycles * duration /2 /* ms */;
        values.bell_pitch = frequence /* Hz */;

        XChangeKeyboardControl(g_TonX11Display, mask, &values);
        XFlush(g_TonX11Display);
        XBell(g_TonX11Display, 100 /* percent */);
        XFlush(g_TonX11Display);

        // wait, because linux is async
        OsUtilsSleep(duration);
    }
#endif
#ifdef _MSC_VER
    Beep(frequence, duration);
#endif
    return;
}

/**
 ******************************************************************************
 * OsUtilsTonSave - save values from speaker
 ******************************************************************************
 */
void OsUtilsToneSave(unsigned int &pitch, unsigned int &duration)
{
#ifdef __GNUC__
    XKeyboardState state;

    if (g_TonX11Display != NULL) 
    {
        /* save settings */
        XGetKeyboardControl(g_TonX11Display, &state);

        pitch = state.bell_pitch;
        duration = state.bell_duration;
    }
#endif
    return;
}

/**
 ******************************************************************************
 * OsUtilsTonRestore - restore values from speaker
 ******************************************************************************
 */
void OsUtilsToneRestore(unsigned int pitch, unsigned int duration)
{
#ifdef __GNUC__
    XKeyboardControl values;
    unsigned long mask = KBBellDuration | KBBellPitch;
 
    if (g_TonX11Display != NULL) 
    {
        values.bell_pitch = pitch;
        values.bell_duration = duration;
        
        /* save settings */
        XChangeKeyboardControl(g_TonX11Display, mask, &values);
    }
#endif
    return;
}

