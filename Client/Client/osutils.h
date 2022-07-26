#ifndef __OSUTILSH__
#define __OSUTILSH__
/**
 ******************************************************************************
 * @file    osutils.h
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

/*
 ******************************************************************************
 * defines
 ******************************************************************************
 */
#ifdef  _MSC_VER    
    typedef HANDLE TYprnIoMutex;
#endif

#ifdef __GNUC__
    typedef pthread_mutex_t TYprnIoMutex;
#endif

typedef struct 
{
    TYprnIoMutex    hMutex;
    int             mutexValid;
} TYtasMutex;

#define OSUTILS_SUCCESS     0
#define OSUTILS_FAILURE     1

/*
 ******************************************************************************
 * functions
 ******************************************************************************
 */
/**
 ******************************************************************************
 * OsUtilsMutexCreate - create a mutex
 *
 * @param    -
 * @return   UPOS_SUCCESS   successful
 *           UPOS_E_FAILURE failure
 ******************************************************************************
 */
long OsUtilsMutexCreate(TYtasMutex *tasMutex);

/**
 ******************************************************************************
 * OsUtilsMutexDelete - delete a mutex
 *
 * @param    -
 * @return   UPOS_SUCCESS   successful
 *           UPOS_E_FAILURE failure
 ******************************************************************************
 */
long OsUtilsMutexDelete(TYtasMutex *tasMutex);

/**
 ******************************************************************************
 * OsUtilsMutexLock - lock a mutex
 *
 * @param    -
 * @return   -
 ******************************************************************************
 */
void OsUtilsMutexLock(TYtasMutex *tasMutex);

/**
 ******************************************************************************
 * OsUtilsMutexUnlock - unlock a mutex
 *
 * @param    -
 * @return   -
 ******************************************************************************
 */
void OsUtilsMutexUnlock(TYtasMutex *tasMutex);

/**
 ******************************************************************************
 * OsUtilsSleep - delay for a specified amount of time (milliseconds)
 *
 * @param    time  : amount of milliseconds
 ******************************************************************************
 */
void OsUtilsSleep(unsigned long time);

/**
 ******************************************************************************
 * OsUtilsTonInit - init tone
 ******************************************************************************
 */
void OsUtilsToneInit(void);

/**
 ******************************************************************************
 * OsUtilsTonExit - exit tone
 ******************************************************************************
 */
void OsUtilsToneExit(void);

/**
 ******************************************************************************
 * OsUtilsTon - beep over speaker
 ******************************************************************************
 */
void OsUtilsTone(unsigned long frequence, unsigned long duration);

/**
 ******************************************************************************
 * OsUtilsTonSave - save values from speaker
 ******************************************************************************
 */
void OsUtilsToneSave(unsigned int &pitch, unsigned int &duration);

/**
 ******************************************************************************
 * OsUtilsTonRestore - restore values from speaker
 ******************************************************************************
 */
void OsUtilsToneRestore(unsigned int pitch, unsigned int duration);

#endif
