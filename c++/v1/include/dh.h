#ifndef _DH_H_
#define _DH_H_

#include <iostream>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <vector>

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include "function_result.h"
#include "os.h"
#include "logger.h"

#define BROADCAST_IP    "192.168.137.255"
#define CTRL_PORT       2334
#define FDB_PORT        2333

class DhCls
{
private:
    int isInit = 0;
    int dh_socket;

public:
    struct sockaddr_in ctrl_addr, fdb_addr, recv_addr;
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    

private:
    int init(); 
    int communicaiton(char *ip, int port, char *sendmsg, char *recvmsg);
    int encode(char *en_msg);
    int decode(char *de_msg);

public:
    DhCls(/* args */);
    ~DhCls();

    int do_ctrl(int word);
    int do_fdb(int word);
};

int get_ip(char *ip);

#endif // !_DH_H_