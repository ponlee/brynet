#ifndef BRYNET_NET_CONNECTOR_H_
#define BRYNET_NET_CONNECTOR_H_

#include <functional>
#include <memory>

#include <brynet/net/EventLoop.h>
#include <brynet/net/SocketLibTypes.h>
#include <brynet/utils/NonCopyable.h>
#include <brynet/net/Any.h>

namespace brynet
{
    namespace net
    {
        class ConnectorWorkInfo;

        class AsyncConnector : NonCopyable, public std::enable_shared_from_this<AsyncConnector>
        {
        public:
            typedef std::shared_ptr<AsyncConnector> PTR;
            typedef std::function<void(sock)> COMPLETED_CALLBACK;
            typedef std::function<void()> FAILED_CALLBACK;

            void                startThread();
            void                destroy();
            void                asyncConnect(const std::string& ip, 
                                             int port, 
                                             std::chrono::nanoseconds timeout,
                                             COMPLETED_CALLBACK, 
                                             FAILED_CALLBACK);

            static  PTR         Create();

        private:
            AsyncConnector();
            virtual ~AsyncConnector();
            void                run();

        private:
            EventLoop                       mEventLoop;

            std::shared_ptr<ConnectorWorkInfo> mWorkInfo;
            std::shared_ptr<std::thread>    mThread;
            std::mutex                      mThreadGuard;
            bool                            mIsRun;
        };
    }
}

#endif