/**
 ******************************************************************************
 * @file    UposCashDrwaerZMQServer.cpp
 *
 * @par     Project:
 *          Bizerba UPOS cashdrawer Interface - Copyright (c) 2017 BIZERBA
 * @par     Package:
 *          ZMQ Server
 *
 * @brief   Implementierung ZMQ 
 * 
 * @version 1
 * @date    20.09.2017
 * @author  Bizerba
 * 
 * @remarks Fuer die Anbindung einer 64 bit Java VM mit 32 Bit native library code
 *          wurde die 32 Bit Library in einen eigenen Prozess (ZMQ Server) ausgelagert
 ******************************************************************************
 */


#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "uposcashdrawer.pb.h"
#include "UposCashDrawerZMQServer.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

#ifndef LONG
#define LONG int
#endif

/*
 ******************************************************************************
 * typedefs
 ******************************************************************************
 */
typedef long TYUPOSHandle;

// static init
UposCashDrawerZMQServer* UposCashDrawerZMQServer::thisPtr = NULL;

UposCashDrawerZMQServer::UposCashDrawerZMQServer()
{
    m_pContext = NULL;
    m_pSocket = NULL;
    m_running = false;
    m_remoteAdr = "tcp://*:";
}

UposCashDrawerZMQServer::~UposCashDrawerZMQServer()
{
	if (m_pSocket)
	{
		try
		{
			m_pSocket->close();
		}
		catch (zmq::error_t & err)
		{
			std::cout << "UposCashDrawerZMQServer::~UposCashDrawerZMQServer() Error closing the socket " << err.what() << " errno: " << err.num();
		}
		delete m_pSocket;
		m_pSocket = NULL;
	}

    if (m_pContext)
    {
        delete m_pContext;
        m_pContext = NULL;
    }
}


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

int UposCashDrawerZMQServer::startServer(std::string port)
{
    int retval = 0;
    try
    {
        m_pContext = new zmq::context_t(1);
        std::cout << "UposCashDrawerZMQServer::startServer(): Context created." << std::endl;
        m_port = port;

		retval = lazyConnect();
        thisPtr = this;
        m_running = true;
        while(m_running)
        {
            receiveMsgUPosWrapper();
        }
    }
	catch (zmq::error_t & err)
	{
		std::cout << "Error in UposCashDrawerZMQServer::startServer(): " << err.what() << " errno: " << err.num();
        retval = 1;
    }

    printf("Host port: %s", port.c_str());

    return retval;
}

int UposCashDrawerZMQServer::lazyConnect()
{
    int retval = 1;

    try
    {
        if ( ! m_pContext )
        {
            retval = -1;
            assert(m_pContext);
        }

        if ( ! m_pSocket )    // if pContext==NULL should have thrown an exception before
        {
            m_pSocket = new zmq::socket_t( *m_pContext, ZMQ_REP );
            std::cout << "UposCashDrawerZMQServer::lazyConnect() connection string: " << m_remoteAdr + m_port << std::endl;
            assert(m_pSocket);
            int linger = 0;
            m_pSocket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
            m_pSocket->bind(m_remoteAdr + m_port);
            std::cout << "UposCashDrawerZMQServer::lazyConnect() context/socket " << (m_pContext != NULL) << "/" << (m_pSocket != NULL) << std::endl;
        }

        retval = 0;
    }
    catch( zmq::error_t & err )
    {
		std::cout << "UposCashDrawerZMQServer::lazyConnect():error code:" << err.num() << ",error msg:" << err.what() << std::endl;
        retval = 1;
    }

    return retval;
}

int UposCashDrawerZMQServer::sendMsg(JposcashdrawerZMQ::Params &reply)
{
	int retval = 1;
	const int sz = reply.ByteSize();
    zmq::message_t msg(sz);

	if(reply.SerializeToArray(msg.data(), sz))
	{
		try
        {
            if (m_pSocket->send(msg))
            {
                retval = 0; // no error
            }
            else
            {
                retval = 1; // error
                std::cout << "Error in UposCashDrawerZMQServer::sndMsg()" << std::endl;
            }
        }
		catch (zmq::error_t & err)
		{
            std::cout << "Error in UposCashDrawerZMQServer::sendMsg(): " << err.what() << " errno: " << err.num() << std::endl;
        }
    }

    reply.Clear();

    return retval;
}

int UposCashDrawerZMQServer::receiveMsg(JposcashdrawerZMQ::Params &request)
{
    int retval = 0;
    if (&request != NULL)
    {
        try
        {
            zmq::message_t req;
            zmq::pollitem_t items[] = { { *m_pSocket, 0, ZMQ_POLLIN, 0 } };

            zmq::poll(&items[0], 1, 50);
            if (items[0].revents & ZMQ_POLLIN)
            {
                if (m_pSocket->recv(&req))
                {
                    // no error
                    request.ParseFromArray(req.data(), req.size());
                }
                else
                {
                    retval = 1; // error
                    std::cout << "Error in UposCashDrawerZMQServer::rcvMsg()" << std::endl;
                }
            }
            else
            {
                retval = 2;
            }
        } 
		catch (zmq::error_t & err)
		{
			std::cout << "Error in UposCashDrawerZMQServer::rcvMsg(): error code:" << err.num() << ",error msg:" << err.what() << std::endl;
        }
    }
    return retval;
}

void UposCashDrawerZMQServer::ZMQsrvInit(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    long err = 12345;//BUCashDrawerInit();
    reply.set_errorcode(err);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvExit(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;    
    long err = 2;//BUCashDrawerExit();
    reply.set_errorcode(err);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvOpen(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();
    const char *logDeviceName  = request.strparam(0).c_str();
    long err = 3;//BUCashDrawerOpen(handle, (char*)logDeviceName, errorTxt, sizeof(errorTxt) - 1);
    reply.set_insthdl(handle);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvClose(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();   
    long err = 4;//BUCashDrawerClose(handle, errorTxt, sizeof(errorTxt) - 1);
    reply.set_insthdl(handle);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}
/*
void UposCashDrawerZMQServer::ZMQsrvClaim(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    long timeout = request.uint32param(0);
    long err = BUCashDrawerClaim(handle, timeout, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);

}

void UposCashDrawerZMQServer::ZMQsrvGetClaimed(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    bool claimed = true;
    long err = BUCashDrawerGetClaimed(handle,claimed, errorTxt, sizeof(errorTxt) - 1);
    reply.add_boolparam(claimed);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvReleaseDevice(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    long err =  BUCashDrawerRelease(handle, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvSetDeviceEnabled(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    bool enable = request.boolparam(0);
    long err = BUCashDrawerSetDeviceEnabled(handle, enable, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvGetDeviceEnabled(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    TYUPOSHandle handle = request.insthdl();
    char errorTxt[255];
    bool enabled;
    long err = BUCashDrawerGetDeviceEnabled(handle, enabled, errorTxt, sizeof(errorTxt) - 1);
    reply.add_boolparam(enabled);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvSetAsyncMode(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    bool asyncMode = request.boolparam(0);
    long err =  BUCashDrawerSetAsyncMode(handle, asyncMode, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvGetAsyncMode(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    bool asyncMode;
    long err = BUCashDrawerGetAsyncMode(handle, asyncMode, errorTxt, sizeof(errorTxt) - 1);
    reply.add_boolparam(asyncMode);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvGetState(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    long state;
    long err =  BUCashDrawerGetState(handle, state, errorTxt, sizeof(errorTxt) - 1);
    reply.add_uint32param(state);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvDirectIO(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    long command = request.uint32param(0);
    long data = request.uint32param(1);
    char *obj = (char*)request.strparam(0).c_str();
    long objLen = strlen(obj);
    long err = BUCashDrawerDirectIO(handle, command,data, obj, objLen, errorTxt, sizeof(errorTxt) - 1);
    reply.add_uint32param(data);
    reply.add_strparam(obj);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvOpenDrawer(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    long err =  BUCashDrawerOpenDrawer(handle, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvOpened(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    bool drawerOpened;
    long err = BUCashDrawerOpened(handle, drawerOpened, errorTxt, sizeof(errorTxt) - 1);
    reply.add_boolparam(drawerOpened);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}

void UposCashDrawerZMQServer::ZMQsrvWaitForDrawerClose(JposcashdrawerZMQ::Params &request)
{
    JposcashdrawerZMQ::Params reply;
    char errorTxt[255];
    TYUPOSHandle handle = request.insthdl();    
    unsigned long timeout = request.uint32param(0);
    unsigned long frequency = request.uint32param(1);
    unsigned long duration = request.uint32param(2);
    unsigned long delay = request.uint32param(3);
    long err = BUCashDrawerWaitForDrawerClose(handle, timeout, frequency, duration, delay, errorTxt, sizeof(errorTxt) - 1);
    reply.set_errorcode(err);
    reply.set_errortext(errorTxt);
    sendMsg(reply);
}
*/
bool UposCashDrawerZMQServer::receiveMsgUPosWrapper()
{
    JposcashdrawerZMQ::Params request;
    int retVal = receiveMsg(request);
    if ( retVal == 0)
    {
        // message received
        int cmd = request.cmd();

        switch (cmd)
        {
        case JposcashdrawerZMQ::UPOSlibInit:
            {
                ZMQsrvInit(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibExit:
            {
                ZMQsrvExit(request);
                m_running = false;
                break;
            }
        case JposcashdrawerZMQ::UPOSlibOpen:
            {
                ZMQsrvOpen(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibClose:
            {
                ZMQsrvClose(request);
                break;
            }
#if 0
        case JposcashdrawerZMQ::UPOSlibClaim:
            {
                ZMQsrvClaim(request);
                break;
            }
            
        case JposcashdrawerZMQ::UPOSlibGetClaimed:
            {
                ZMQsrvGetClaimed(request);
                break;
            }
            
        case JposcashdrawerZMQ::UPOSlibRelease:
            {
                ZMQsrvReleaseDevice(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibSetDeviceEnabled:
            {
                ZMQsrvSetDeviceEnabled(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibGetDeviceEnabled:
            {
                ZMQsrvGetDeviceEnabled(request);
                break;
            }            
            
        case JposcashdrawerZMQ::UPOSlibDirectIO:
            {
                ZMQsrvDirectIO(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibGetState:
            {
                ZMQsrvGetState(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibSetAsyncMode:
            {
                ZMQsrvSetAsyncMode(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibGetAsyncMode:
            {
                ZMQsrvGetAsyncMode(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibOpenDrawer:
            {
                ZMQsrvOpenDrawer(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibOpened:
            {
                ZMQsrvOpened(request);
                break;
            }
        case JposcashdrawerZMQ::UPOSlibWaitForDrawerClose:
            {
                ZMQsrvWaitForDrawerClose(request);
                break;
            }
#endif
        } // end switch case

        request.Clear();
    }

    return true;
}

int main(int argc, char* argv[])
{
	//GOOGLE_PROTOBUF_VERIFY_VERSION;

    UposCashDrawerZMQServer serv;

    if(argc == 2)
    {
        if(serv.startServer(argv[1]))
        {
            return -1;
        }
    }
    else
    {
	    if(serv.startServer("1081"))//5561
        {
            return -1;
        }
    }

    return 0;
} // end main
