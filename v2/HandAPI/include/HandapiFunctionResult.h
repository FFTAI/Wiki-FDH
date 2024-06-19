namespace HandProtocol
{
    namespace APIResultCode
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
    } // namespace APIResultCode
} // namespace HandAPI