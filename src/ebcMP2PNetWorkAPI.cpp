﻿/* MP2P communication and network interface API/MP2P通讯与网络接口API函数
   File Name        : ebcMP2PNetWorkAPI.cpp
   Version          : 0.0.1
   Date             : 2019-03-23
   Interface design : Wang Yueping(version 0.0.1)
   Software         : Xu Xiaona,He Xiaoen,Sun jiarui(version 0.0.1)
   Language         : C++
   Development tool : Qt Creater 4.8.0
   Description      : MP2P communication and network interface API C++ file

  (C) Copyright 2019  Right Chain Technolegy Corp., LTD.
*/

#include "ebcMP2PNetWorkAPI.h"




// MP2P网络与通讯模块接口函数类
ebcMP2PNetWorkAPI::ebcMP2PNetWorkAPI()
{
}

ebcMP2PNetWorkAPI::~ebcMP2PNetWorkAPI()
{
}

/*
  功    能：按指定的组网节点创建MP2P网络
  输入参数：createNetworkNodeAddress-字符型数据，组网节点地址
  输出参数：无
  返回参数：true-创建成功，false-创建失败
*/
bool ebcMP2PNetWorkAPI::createNetwork(const char *createNetworkNodeAddress)
{
    engine.NetInit(createNetworkNodeAddress);
    engine.startClient();
    return 1;
}

/*
  功    能：按指定的组网节点刷新MP2P网络
  输入参数：createNetworkNodeAddress-字符型数据，组网节点地址
  输出参数：无
  返回参数：true-网络表有刷新，false-网络表无刷新
*/
bool ebcMP2PNetWorkAPI::updateNetwork()
{
    return 1;
}

/*
  功    能：读取组网节点的MP2P网络表
  输入参数：createNetworkNodeAddress-字符型数据，组网节点地址
  输出参数：networkTable-结构数据，MP2P域网络表
  返回参数：无
*/
void ebcMP2PNetWorkAPI::getNetworkTable(NETWORK_DOMAIN_TABLE *networkTable)
{
    engine.getBucket(networkTable->onlineNodeAddress);
}

/*
  功    能：加入一个指定的节点到MP2P网络中
  输入参数：createNetworkNodeAddress-字符型数据，组网节点地址
            jionNetworkNodeAddress-字符型数据，指定加入网络的节点地址
  输出参数：无
  返回参数：true-节点加入成功，false-节点加入失败
  备    注：可以指定一个节点加入到网络中来
*/
bool ebcMP2PNetWorkAPI::joinNodeToNetwork(const char *joinNetworkNodeAddress)
{
    return engine.joinNetWork(joinNetworkNodeAddress);
}

/*
  功    能：断开MP2P网络中的一个指定节点
  输入参数：createNetworkNodeAddress-字符型数据，组网节点地址
            breakNetworkNodeAddress-字符型数据，断开的网络节点地址
  输出参数：无
  返回参数：true-固定节点断开成功，false-固定节点断开失败
  备    注：可以指定一个网络中的节点断开
*/
bool ebcMP2PNetWorkAPI::breakNodeFormNetwork(const char *breakNetworkNodeAddress)
{
    return engine.eraseNode(breakNetworkNodeAddress);

}

/*
  功    能：由源地址发送数据流到目标地址函数
  输入参数：sourceNodeAddress-字符型数据，发送数据源节点地址
            targetNodeAddress-字符型数据，接收数据目标节点地址
            sendDataStreamBuffer-字符型数据流，发送数据流
            sendDataStreamBufferSize-整型数据，发送数据流长度
  输出参数：无
  返回参数：true-发送成功，false-发送失败
*/
bool ebcMP2PNetWorkAPI::sendDataStream(const char *sourceNodeAddress, const char *targetNodeAddress, const char *sendDataStreamBuffer, const uint32_t sendDataStreamBufferSize)
{
    engine.sendDataStream(targetNodeAddress, sendDataStreamBuffer, sendDataStreamBufferSize);
    return 0;
}

/*
  功    能：从网络接收数据流中读取数据函数
  输入参数：receiveDataStreamBufferSize-整型数据，读取数据流长度
  输出参数：receiveDataStreamBuffer-字符型数据，读取的数据流数据
  返回参数：实际读出的数据流字节数
*/
uint32_t ebcMP2PNetWorkAPI::getReceiveDataStream(char *receiveDataStreamBuffer, uint32_t receiveDataStreamBufferSize)
{	
    std::string data;
    if(!engine.getUserDate(data))
        return 0;

    memcpy(receiveDataStreamBuffer, data.data(), receiveDataStreamBufferSize);
    return 0;
}

/*** end of file **************************************************************/
