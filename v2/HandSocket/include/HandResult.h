#pragma once

namespace HandSocket
{
    namespace ResultCode
    {
        enum FunctionResult
        {
            SUCCESS = 0,
            FAIL = -1,
            RUNNING = 1,
            PREPARE = 2,
            EXECUTE = 3,
            NOT_EXECUTE = 4,
            TIMEOUT = 5,
        };

        enum SocketResult
        {
            SOCKET_SEND_FAILED = -10001,
            SOCKET_SEND_SIZE_WRONG = -10002,
            SOCKET_RECEIVE_FAILED = -10003,
            SOCKET_RECEIVE_SIZE_WRONG = -10004,
        };
    } // namespace Result
}