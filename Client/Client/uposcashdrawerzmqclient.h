/**
 ******************************************************************************
 * @file    UposCashDrwaerZMQClient.h
 *
 * @par     Project:
 *          Bizerba UPOS cashdrawer Interface - Copyright (c) 2018 BIZERBA
 * @par     Package:
 *          ZMQ Client
 *
 * @brief   Implementierung ZMQ 
 * 
 * @version 1
 * @date    01.06.2018
 * @author  Bizerba
 * 
 * @remarks For the connection of a 64 bit OCX with 32 Bit native library code
  * The 32-bit library was outsourced to a separate process (ZMQ server)
 ******************************************************************************
 */


#ifndef UposCashDrawerZMQClient_H
#define UposCashDrawerZMQClient_H
#include <zmq.hpp>
#include "uposcashdrawer.pb.h"
#include <iostream>
#include "osutils.h"

/*****************************************************************************
 *  Fehler Codes
 *****************************************************************************/

//
#define ZMQ_DEBUG_INFO              1
#define ZMQ_WAIT_TIMEOUT1         ( 500 )
#define ZMQ_WAIT_TIMEOUT2         ( 1000 )
#include "mytick.h"

/***************************************************
 * Konstanten UPOS allgemein
 *
 ***************************************************/

/** UPOS ohne Fehler */
#define UPOS_SUCCESS 0
/** Unendlicher Timeout */
#define UPOS_FOREVER -1

/** States */
#define UPOS_S_CLOSED  1
#define UPOS_S_IDLE    2
#define UPOS_S_BUSY    3
#define UPOS_S_ERROR   4


/* UPOS allgemeine Fehler */
#define UPOSERR_    100
#define UPOSERREXT_ 200


#define UPOS_E_CLOSED           1 + UPOSERR_
#define UPOS_E_CLAIMED          2 + UPOSERR_
#define UPOS_E_NOTCLAIMED       3 + UPOSERR_
#define UPOS_E_NOSERVICE        4 + UPOSERR_
#define UPOS_E_DISABLED         5 + UPOSERR_
#define UPOS_E_ILLEGAL          6 + UPOSERR_
#define UPOS_E_NOHARDWARE       7 + UPOSERR_
#define UPOS_E_OFFLINE          8 + UPOSERR_
#define UPOS_E_NOEXIST          9 + UPOSERR_
#define UPOS_E_EXISTS          10 + UPOSERR_
#define UPOS_E_FAILURE         11 + UPOSERR_
#define UPOS_E_TIMEOUT         12 + UPOSERR_
#define UPOS_E_BUSY            13 + UPOSERR_
#define UPOS_E_EXTENDED        14 + UPOSERR_

/* UPOS invalid handle */
#define UPOS_INVALID_HANDLE     -1


/*
 ******************************************************************************
 * typedefs
 ******************************************************************************
 */
typedef long TYUPOSHandle;

class sec_lock
{
public:
    sec_lock()
    {
        OsUtilsMutexCreate( &m_mut );
    }
	~sec_lock()
    {
        OsUtilsMutexDelete( &m_mut );
    }
	void  enter()
    {
        OsUtilsMutexLock( &m_mut );
    }
	void  leave()
    {
        OsUtilsMutexUnlock( &m_mut );
    }
private:
    TYtasMutex m_mut;
};

//Trace
class CMyPrint
{
public:
    void Print( TCHAR * text )
    {
        OutputDebugString( text );
    }
public:
    static CMyPrint * Instance()
    {
        static CMyPrint _instance;
        return &_instance;
    }
};

#ifndef _DEBUG
#define TRACE(x) (x)
#else
#define TRACE(x) CMyPrint::Instance()->Print(x)
#endif

class UposCashDrawerZMQClient
{
	// Attribute
private:
/**/
    zmq::context_t* m_pContext;
    zmq::socket_t* m_pSocket;
    std::string m_remoteAdr;
    std::string m_port;

    static UposCashDrawerZMQClient* thisPtr; // for StatusUpdateDTCCS Callback
    bool m_running;

	// Konstruktor
public:
	UposCashDrawerZMQClient();    

	// Kopierkonstruktor
private:
	UposCashDrawerZMQClient(const UposCashDrawerZMQClient& uposPrinterZMQServer);

	// Destruktor
public:
	virtual ~UposCashDrawerZMQClient();

	// Methoden
public:
    long BUCashDrawerInit()
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerInit.\n") );
#endif 

        m_lockZMQ.enter();

        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibInit);
        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);

		//test
		std::cout << "rev:" << reply.errorcode() << std::endl;

        m_lockZMQ.leave();

        return reply.errorcode();
    }

    long BUCashDrawerExit()
    {
        m_lockZMQ.enter();

        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibExit);
        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);

        m_lockZMQ.leave();

        return reply.errorcode();
    }

    long BUCashDrawerOpen(TYUPOSHandle &insthdl, char *logDeviceName, char *errorTxt, long errorTxtLen)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpen.\n") );
#endif 
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpen::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibOpen);
        sender.add_strparam(logDeviceName);//        sender.set_strparam(0,logDeviceName);

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerOpen::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }
        if( reply.ByteSize() )
        {
            insthdl = reply.insthdl();
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpen::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerOpened(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }

    long BUCashDrawerClose(TYUPOSHandle insthdl, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerClose::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibClose);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( errorTxtLen > reply.errortext().length() )
            strcpy( errorTxt,(char *)reply.errortext().data() );
        else
            strcpy( errorTxt,(char *)"insufficent buffer." );
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerClose::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerClose(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }

    long BUCashDrawerClaim(TYUPOSHandle insthdl, long timeout, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerClaim::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibClaim);
        sender.set_insthdl( insthdl );
        sender.add_uint32param( timeout );

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( errorTxtLen > reply.errortext().length() )
            strcpy( errorTxt,(char *)reply.errortext().data() );
        else
            strcpy( errorTxt,(char *)"insufficent buffer." );
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerClaim::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerClaim(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerGetClaimed(TYUPOSHandle insthdl, bool &claimed, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetClaimed::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibGetClaimed);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( reply.ByteSize() )
        {
            claimed = reply.boolparam(0);
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );        
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetClaimed::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerGetClaimed(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerRelease(TYUPOSHandle insthdl, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerRelease::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibRelease);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( reply.ByteSize() )
        {
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );      
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerRelease::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerRelease(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerSetDeviceEnabled(TYUPOSHandle insthdl, bool enable, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerSetDeviceEnabled::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibSetDeviceEnabled);
        sender.set_insthdl( insthdl );
        sender.add_boolparam(enable);

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( reply.ByteSize() )
        {
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );        
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerSetDeviceEnabled::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerSetDeviceEnabled(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerGetDeviceEnabled(TYUPOSHandle insthdl, bool &enable, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetDeviceEnabled::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibGetDeviceEnabled);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( reply.ByteSize() )
        {
            enable = reply.boolparam(0);
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );        
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetDeviceEnabled::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();

        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerGetDeviceEnabled(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerGetState(TYUPOSHandle insthdl, long &state, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetState::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibGetState);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerGetState::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            if( 0 == reply.errorcode() )
                state = (long)reply.uint32param(0);
            else
                state = false;
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerGetState(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerSetAsyncMode(TYUPOSHandle insthdl, bool asyncMode, char *errorTxt, long errorTxtLen)
    {
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerSetAsyncMode::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibSetAsyncMode);
        sender.set_insthdl( insthdl );
        sender.add_boolparam(asyncMode);

        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerSetAsyncMode::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerSetAsyncMode::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerSetAsyncMode(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerGetAsyncMode(TYUPOSHandle insthdl, bool &asyncMode, char *errorTxt, long errorTxtLen)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetAsyncMode.\n") );
#endif 
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetAsyncMode::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibGetAsyncMode);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerGetAsyncMode::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            if( 0 == reply.errorcode() )
                asyncMode = (long)reply.boolparam(0);
            else
                asyncMode = false;
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerGetAsyncMode::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerGetAsyncMode(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    long BUCashDrawerDirectIO(TYUPOSHandle insthdl, const ULONG& id, ULONG& data, std::string & str1, std::string& errorText)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerDirectIO.\n") );
#endif
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerDirectIO::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibDirectIO);
        sender.set_insthdl( insthdl );
        sender.add_uint32param(id);
        sender.add_uint32param(data);
        sender.add_strparam(str1);
        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerDirectIO::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            str1 = reply.strparam(0);
            data = (long)reply.uint32param(0);
            errorText = reply.errortext().data();
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerDirectIO::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerDirectIO(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }

    long BUCashDrawerOpenDrawer(TYUPOSHandle insthdl, char *errorTxt, long errorTxtLen)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpenDrawer.\n") );
#endif 
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpenDrawer::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibOpenDrawer);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerOpenDrawer::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpenDrawer::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerOpenDrawer(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }

    long BUCashDrawerOpened(TYUPOSHandle insthdl, bool &cashDrawerState, char *errorTxt, long errorTxtLen)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpened.\n") );
#endif 
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpened::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibOpened);
        sender.set_insthdl( insthdl );

        JposcashdrawerZMQ::Params reply;
//        reply.add_boolparam(0);
//        int sz = reply.boolparam_size();

        reply = sendMsg(sender,5000);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerOpened::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )  //bool hasinst = reply.has_insthdl();//int bytesize = reply.ByteSize();
        {
            cashDrawerState = (long)reply.boolparam(0);
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerOpened::m_lockZMQ leave.\n") );
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerOpened(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }

    long BUCashDrawerWaitForDrawerClose(TYUPOSHandle insthdl, unsigned long timeout, unsigned long frequency, unsigned long duration, unsigned long delay, char *errorTxt, long errorTxtLen)
    {
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerWaitForDrawerClose.\n") );
        CMyTick tick('w');
        tick.OnBegin();
#endif
        try
        {
        m_lockZMQ.enter();
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerWaitForDrawerClose::m_lockZMQ enter.\n") );
#endif 
        JposcashdrawerZMQ::Params sender;
        sender.set_cmd(JposcashdrawerZMQ::UPOSlibWaitForDrawerClose);
        sender.set_insthdl( insthdl );
        sender.add_uint32param(timeout);
        sender.add_uint32param(frequency);
        sender.add_uint32param(duration);
        sender.add_uint32param(delay);

        JposcashdrawerZMQ::Params reply;
        reply = sendMsg(sender,timeout + ZMQ_WAIT_TIMEOUT1);
        if( !reply.ByteSize() )
        {
#if defined( ZMQ_DEBUG_INFO )
            TRACE( TEXT("BUCashDrawerWaitForDrawerClose::ZMQ timeout.\n") );
#endif 
            receiveMsg(reply);
        }

        if( reply.ByteSize() )
        {
            if( errorTxtLen > reply.errortext().length() )
                strcpy( errorTxt,(char *)reply.errortext().data() );
            else
                strcpy( errorTxt,(char *)"insufficent buffer." );
        }
#if defined( ZMQ_DEBUG_INFO )
        TRACE( TEXT("BUCashDrawerWaitForDrawerClose::m_lockZMQ leave.\n") );
        tick.OnEnd();
#endif 
        m_lockZMQ.leave();
        return reply.errorcode();
        }
        catch (std::exception & err)
		{
            m_lockZMQ.leave();
			std::cout << "Error in UposCashDrawerZMQClient::BUCashDrawerWaitForDrawerClose(): " << err.what() << std::endl;

            std::string str = err.what();
            char * pStr = (char *)str.c_str();
        }

        return 0;
    }
    void lazyDisconnect();
private:
    int lazyConnect();
    

	int sendMsg(JposcashdrawerZMQ::Params &request);
	int receiveMsg(JposcashdrawerZMQ::Params &reply);
    JposcashdrawerZMQ::Params sendMsg(JposcashdrawerZMQ::Params &sender,int timeout);

public:
    static UposCashDrawerZMQClient * Instance()
    {
        return &_instance;
    }

private:
    sec_lock m_lockZMQ;
    static UposCashDrawerZMQClient & _instance;
};

#endif
