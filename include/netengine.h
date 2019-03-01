#ifndef NETENGINE_H
#define NETENGINE_H

#include <vector>
#include <map>
#include <thread>

#include "msgpack.h"
#include "bucket.h"
#include "node.h"
#include "utils.h"

namespace NET{
class NetEngine
{
public:
    NetEngine(const NodeId _id, const bool _isServer = false);
    ~NetEngine();

    void startServer();
    void startClient(const std::string ip=SUPER_NODE, const uint16_t port=SRV_PORT);

    void printNodesInfo(int type = 0);   // 打印出所有节点信息
    void sendHello();

private:
    void setUdtOpt(const UDTSOCKET &sock);   //设置socket的非阻塞以及发送/接收缓冲器的大小
    int getReadableByte(const UDTSOCKET &sock);
    void handleMsg(UDTSOCKET, int epllFd = 0);
    int startPunch(int&,uint32_t ip, uint16_t port);

    void addPeertobkt(const NodeId &_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET sock=0);
    void addPeertobkt(const std::string&_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET sock=0 );
    void addCliNodetobkt(const NodeId &_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET& sock);//加入服务器K桶
    void addCliNodetobkt(const std::string &_id, const struct sockaddr_in& addr,const uint32_t& nat, const UDTSOCKET& sock);
    void addCliNodetobkt(const std::string& _id,const uint32_t& ip,const uint32_t& port_nat,const UDTSOCKET& sock);


    Node self;   //本节点的信息
    UDTSOCKET boot_sock;  //本节点与服务器通信的SOCKET
    std::map<NodeId , Node> peerNode; //与此节点连接的节点ID与节点信息对
    std::map<NodeId , Node> clientNode; //此节点作为服务端时使用，记录与之相连的客户端节点信息
    Bucket kad;//服务器或是客户机的K桶
    std::thread boot_thread; //启动线程，负责与服务器节点交互以及维护对端节点的连接
    bool boot_thread_flag;

    bool isServer;        //是否作为服务器
    std::thread server;   //服务器线程(后期可能改为单独进程),当节点有成为服务器节点的可能时，启动此线程
    bool server_thread_flag;

    //std::map<UDTSOCKET, NodeId> sockIdPair;  //记录UDT套接字与节点ID的对应关系，方便通过UDTSOCKET快速找到ID
    std::map<UDTSOCKET, Sp<Node>> sockNodePair;  //记录UDT套接字与节点的对应关系，方便通过UDTSOCKET快速找到node

    sockaddr_in local_addr ;


#if 0
    void addClientNode(const NodeId &_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET& sock);
    void addClientNode(const std::string &_id, const struct sockaddr_in& addr,const uint32_t& nat, const UDTSOCKET& sock);
    void addClientNode(const std::string& _id,const uint32_t& ip,const uint32_t& port_nat,const UDTSOCKET& sock);

   //这部分需要改一下
    bool findClientNode(const NodeId& _id, Node& node);
    bool findClientNode(const std::string& _id, Node& node);
    void delClientNode(const NodeId &_id);
    void delClientNode(const std::string &_id);
    void delClientNode(const UDTSOCKET& sock);

    void addPeerNode(const NodeId &_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET sock=0);
    void addPeerNode(const std::string&_id, const uint32_t& ip,const uint32_t& port_nat, const UDTSOCKET sock=0);

    //这部分需要改一下
    bool findPeerNode(const NodeId& _id, Node& node);
    bool findPeerNode(const std::string& _id, Node& node);
    void updatePeerNode(const NodeId &_id, const Node& node);
    void delPeerNode(const NodeId& _id);
    void delPeerNode(const std::string& _id);
    void delPeerNode(const UDTSOCKET& sock);
#endif

};
}

#endif // NETENGINE_H
