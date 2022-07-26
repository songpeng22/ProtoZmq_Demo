/**
 ******************************************************************************
 * @file    UposCashDrawerZMQServer.h
 *
 * @par     Project:
 *          Bizerba UPOS Cashdrawer Interface - Copyright (c) 2017 BIZERBA
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


#ifndef UPOSCASHDRAWERZMQSERVER_H
#define UPOSCASHDRAWERZMQSERVER_H
#include <zmq.hpp>

class UposCashDrawerZMQServer
{
	// Attribute
private:
    zmq::context_t* m_pContext;
    zmq::socket_t* m_pSocket;
    std::string m_remoteAdr;
    std::string m_port;
    static UposCashDrawerZMQServer* thisPtr; // for StatusUpdateDTCCS Callback
    bool m_running;

	// Konstruktor
public:
	UposCashDrawerZMQServer();    

	// Kopierkonstruktor
private:
	UposCashDrawerZMQServer(const UposCashDrawerZMQServer& uposPrinterZMQServer);

	// Destruktor
public:
	virtual ~UposCashDrawerZMQServer();

	// Methoden
private:

	int sendMsg(JposcashdrawerZMQ::Params &request);
	int receiveMsg(JposcashdrawerZMQ::Params &reply);
	int lazyConnect();
    void ZMQsrvInit(JposcashdrawerZMQ::Params &request);
    void ZMQsrvExit(JposcashdrawerZMQ::Params &request);
    void ZMQsrvOpen(JposcashdrawerZMQ::Params &request);
    void ZMQsrvClose(JposcashdrawerZMQ::Params &request);
#if 0
    void ZMQsrvClaim(JposcashdrawerZMQ::Params &request);
    void ZMQsrvGetClaimed(JposcashdrawerZMQ::Params &request); 
    void ZMQsrvReleaseDevice(JposcashdrawerZMQ::Params &request);
    void ZMQsrvSetDeviceEnabled(JposcashdrawerZMQ::Params &request);
    void ZMQsrvGetDeviceEnabled(JposcashdrawerZMQ::Params &request);
    void ZMQsrvDirectIO(JposcashdrawerZMQ::Params &request);
    void ZMQsrvGetState(JposcashdrawerZMQ::Params &request);
    void ZMQsrvSetAsyncMode(JposcashdrawerZMQ::Params &request);
    void ZMQsrvGetAsyncMode(JposcashdrawerZMQ::Params &request);
    void ZMQsrvOpenDrawer(JposcashdrawerZMQ::Params &request);
    void ZMQsrvOpened(JposcashdrawerZMQ::Params &request);
    void ZMQsrvWaitForDrawerClose(JposcashdrawerZMQ::Params &request);
#endif
public:
    int startServer(std::string port);
    bool receiveMsgUPosWrapper();

};

#endif
