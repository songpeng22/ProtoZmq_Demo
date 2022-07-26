/**
 ******************************************************************************
 * @file    UposCashDrwaerZMQClient.cpp
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


//#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <string>
//#include "uposcashdrawer.pb.h"
#include "UposCashDrawerZMQClient.h"
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

#ifndef LONG
#define LONG int
#endif



// static init
UposCashDrawerZMQClient* UposCashDrawerZMQClient::thisPtr = NULL;
UposCashDrawerZMQClient instance;
UposCashDrawerZMQClient& UposCashDrawerZMQClient::_instance = instance;


UposCashDrawerZMQClient::UposCashDrawerZMQClient()
{
/**/
    m_pContext = NULL;
    m_pSocket = NULL;
    m_running = false;
    m_remoteAdr = "tcp://localhost:";
	//m_remoteAdr = "tcp://*:";
    m_port = "1081";


    //lazyConnect();
}

UposCashDrawerZMQClient::~UposCashDrawerZMQClient()
{
    lazyDisconnect();
}


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

void UposCashDrawerZMQClient::lazyDisconnect()
{
    if (m_pSocket)
    {
        try
        {
            m_pSocket->close();
        }
        catch (zmq::error_t & err)
        {
            std::cout << "UposCashDrawerZMQClient::~UposCashDrawerZMQClient() Error closing the socket " << err.what() << " errno: " << err.num();
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

int UposCashDrawerZMQClient::lazyConnect()
{
    int retval = 1;
/**/
    try
    {
        if ( ! m_pContext )
        {
            m_pContext = new zmq::context_t(1);
            std::cout << "UposCashDrawerZMQClient:: Context created." << std::endl;
        }
        if ( ! m_pSocket )    // if pContext==NULL should have thrown an exception before
        {
            m_pSocket = new zmq::socket_t( *m_pContext, ZMQ_REQ );
            std::cout << "UposCashDrawerZMQClient::lazyConnect() connection string: " << m_remoteAdr + m_port << std::endl;
            assert(m_pSocket);
            int linger = 0;
            m_pSocket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
#if 1
            m_pSocket->connect(m_remoteAdr + m_port);
#else
            m_pSocket->bind(m_remoteAdr + m_port);
#endif
            std::cout << "UposCashDrawerZMQClient::lazyConnect() context/socket " << (m_pContext != NULL) << "/" << (m_pSocket != NULL) << std::endl;
        }

        retval = 0;
    }
    catch( zmq::error_t & err )
    {
    	std::cout << "UposCashDrawerZMQClient::lazyConnect()" << err.what() << err.num() << std::endl;
        retval = 1;
    }

    return retval;
}

int UposCashDrawerZMQClient::sendMsg(JposcashdrawerZMQ::Params &reply)
{
    lazyConnect();
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
                std::cout << "Error in UposCashDrawerZMQClient::sndMsg()" << std::endl;
            }
        }
		catch (zmq::error_t & err)
		{
            std::cout << "Error in UposCashDrawerZMQClient::sendMsg(): " << err.what() << " errno: " << err.num() << std::endl;
#if 0
            std::string str = err.what();
            char * pStr = (char *)str.c_str();
            int nRet = err.num();
#endif
        }
    }

    reply.Clear();

    return retval;
}

int UposCashDrawerZMQClient::receiveMsg(JposcashdrawerZMQ::Params &request)
{
    int retval = 0;
    if (&request != NULL)
    {
        try
        {
            zmq::message_t req;
//            zmq::pollitem_t items[] = { { *m_pSocket, 0, ZMQ_POLLIN, 0 } };

//            zmq::poll(&items[0], 1, ZMQ_WAIT_TIMEOUT2/*50*/);
//            if (items[0].revents & ZMQ_POLLIN)
//            {
                if (m_pSocket->recv(&req))
                {
                    // no error
                    request.ParseFromArray(req.data(), req.size());
                }
                else
                {
                    retval = 1; // error
                    std::cout << "Error in UposCashDrawerZMQClient::rcvMsg()" << std::endl;
                }
//            }
//            else
//            {
//                retval = 2;
//            }
        } 
		catch (zmq::error_t & err)
		{
			std::cout << "Error in UposCashDrawerZMQClient::rcvMsg(): " << err.what() << " errno: " << err.num() << std::endl;
        }
    }
    return retval;
}

JposcashdrawerZMQ::Params UposCashDrawerZMQClient::sendMsg(JposcashdrawerZMQ::Params &sender,int timeout)
{
    lazyConnect();
    try
    {
    int retval = 1;
    JposcashdrawerZMQ::Params reply;
    reply.Clear();

	const int sz = sender.ByteSize();
    zmq::message_t msg(sz);

	if(sender.SerializeToArray(msg.data(), sz))
	{
		try
        {
            //Send
            if (m_pSocket->send(msg))
            {
                retval = 0; // no error
            }
            else
            {
                retval = 1; // error
                std::cout << "Error in UposCashDrawerZMQClient::sndMsg()" << std::endl;
            }
            
            //Rev
            if( 0 == retval )
            {
#if defined( ZMQ_DEBUG_INFO )
                TCHAR cBuf[200];
                int nCountBegin = ::GetTickCount();
                int nCountEnd;
#endif
                zmq::message_t req;
//                zmq::pollitem_t items[] = { { *m_pSocket, 0, ZMQ_POLLIN, 0 } };

//                int pollret = zmq::poll(&items[0], 1, timeout/*50*/);
//                if (items[0].revents & ZMQ_POLLIN)
//                {
                    if (m_pSocket->recv(&req))
                    {
                        // no error
                        reply.ParseFromArray(req.data(), req.size());
#if defined( ZMQ_DEBUG_INFO )
                        nCountEnd = ::GetTickCount();
                        swprintf(cBuf,TEXT("ZMQ::Rev takes:%d ms.\n"),nCountEnd - nCountBegin);
                        TRACE( cBuf );
#endif
                        return reply;
                    }
                    else
                    {
                        retval = 1; // error
                        std::cout << "Error in UposCashDrawerZMQClient::rcvMsg()" << std::endl;
#if defined( ZMQ_DEBUG_INFO )
                        TRACE( TEXT("ZMQ::Receive ret with error.\n") );
#endif
                        reply.Clear();
                        return reply;
                    }
//                }
//                else
//                {
//                    retval = 2;
//#if defined( ZMQ_DEBUG_INFO )
//                    nCountEnd = ::GetTickCount();
//                    swprintf(cBuf,TEXT("ZMQ::revents:%d,tick:%d ms,pollret:%d.\n"),items[0].revents,nCountEnd - nCountBegin,pollret);
//                    TRACE( cBuf );
//#endif
//                }
            }
            else
            {
#if defined( ZMQ_DEBUG_INFO )
                TRACE( TEXT("ZMQ::Send ret != 0.\n") );
#endif
            }
        }
		catch (zmq::error_t & err)
		{
            std::cout << "Error in UposCashDrawerZMQClient::sendMsg(): " << err.what() << " errno: " << err.num() << std::endl;
        }
    }

    sender.Clear();

    return reply;
    }
    catch (std::exception & err)
	{
        std::string str = err.what();
        char * pStr = (char *)str.c_str();
    }
}

