/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Sky UK
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SessionManagementServerTestsFixture.h"
#include "IpcClientMock.h"
#include "IpcServerFactoryMock.h"
#include "MediaKeysCapabilitiesModuleServiceFactoryMock.h"
#include "MediaKeysModuleServiceFactoryMock.h"
#include "MediaPipelineModuleServiceFactoryMock.h"
#include "RialtoControlModuleServiceFactoryMock.h"
#include "SessionManagementServer.h"
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <vector>

using testing::_;
using testing::Invoke;
using testing::Return;
using testing::SetArgReferee;

namespace
{
const std::string socketName{"/tmp/sessionmanagementservertest-0"};
const RIALTO_DEBUG_LEVEL defaultLogLevels{RIALTO_DEBUG_LEVEL_FATAL};
const RIALTO_DEBUG_LEVEL clientLogLevels{RIALTO_DEBUG_LEVEL_ERROR};
const RIALTO_DEBUG_LEVEL ipcLogLevels{RIALTO_DEBUG_LEVEL_DEBUG};
const RIALTO_DEBUG_LEVEL commonLogLevels{RIALTO_DEBUG_LEVEL_DEFAULT};
} // namespace

MATCHER_P4(SetLogLevelsEventMatcher, defaultLogLevels, clientLogLevels, ipcLogLevels, commonLogLevels, "")
{
    std::shared_ptr<firebolt::rialto::SetLogLevelsEvent> event =
        std::dynamic_pointer_cast<firebolt::rialto::SetLogLevelsEvent>(arg);
    return ((defaultLogLevels == event->defaultloglevels()) && (clientLogLevels == event->clientloglevels()) &&
            (ipcLogLevels == event->ipcloglevels()) && (commonLogLevels == event->commonloglevels()));
}

SessionManagementServerTests::SessionManagementServerTests()
    : m_clientMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ClientMock>>()},
      m_serverMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ServerMock>>()},
      m_mediaPipelineModuleMock{
          std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaPipelineModuleServiceMock>>()},
      m_mediaKeysModuleMock{
          std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysModuleServiceMock>>()},
      m_mediaKeysCapabilitiesModuleMock{
          std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysCapabilitiesModuleServiceMock>>()},
      m_rialtoControlModuleMock{
          std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::RialtoControlModuleServiceMock>>()}
{
    std::shared_ptr<StrictMock<firebolt::rialto::ipc::mock::ServerFactoryMock>> serverFactoryMock =
        std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ServerFactoryMock>>();
    EXPECT_CALL(*serverFactoryMock, create(_)).WillOnce(Return(m_serverMock));
    std::shared_ptr<StrictMock<firebolt::rialto::server::ipc::mock::MediaPipelineModuleServiceFactoryMock>>
        mediaPipelineModuleFactoryMock =
            std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaPipelineModuleServiceFactoryMock>>();
    EXPECT_CALL(*mediaPipelineModuleFactoryMock, create(_)).WillOnce(Return(m_mediaPipelineModuleMock));
    std::shared_ptr<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysModuleServiceFactoryMock>> mediaKeysModuleFactoryMock =
        std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysModuleServiceFactoryMock>>();
    EXPECT_CALL(*mediaKeysModuleFactoryMock, create(_)).WillOnce(Return(m_mediaKeysModuleMock));
    std::shared_ptr<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysCapabilitiesModuleServiceFactoryMock>>
        mediaKeysCapabilitiesModuleFactoryMock =
            std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::MediaKeysCapabilitiesModuleServiceFactoryMock>>();
    EXPECT_CALL(*mediaKeysCapabilitiesModuleFactoryMock, create(_)).WillOnce(Return(m_mediaKeysCapabilitiesModuleMock));
    std::shared_ptr<StrictMock<firebolt::rialto::server::ipc::mock::RialtoControlModuleServiceFactoryMock>>
        rialtoControlModuleFactoryMock =
            std::make_shared<StrictMock<firebolt::rialto::server::ipc::mock::RialtoControlModuleServiceFactoryMock>>();
    EXPECT_CALL(*rialtoControlModuleFactoryMock, create(_)).WillOnce(Return(m_rialtoControlModuleMock));
    m_sut =
        std::make_unique<firebolt::rialto::server::ipc::SessionManagementServer>(serverFactoryMock,
                                                                                 mediaPipelineModuleFactoryMock,
                                                                                 mediaKeysModuleFactoryMock,
                                                                                 mediaKeysCapabilitiesModuleFactoryMock,
                                                                                 rialtoControlModuleFactoryMock,
                                                                                 m_playbackServiceMock, m_cdmServiceMock);
}

SessionManagementServerTests::~SessionManagementServerTests() {}

void SessionManagementServerTests::serverWillInitialize()
{
    EXPECT_CALL(*m_serverMock, addSocket(socketName, _, _))
        .WillOnce(Invoke(
            [this](const std::string &socketPath,
                   std::function<void(const std::shared_ptr<firebolt::rialto::ipc::IClient> &)> clientConnectedCb,
                   std::function<void(const std::shared_ptr<firebolt::rialto::ipc::IClient> &)> clientDisconnectedCb) {
                m_clientConnectedCb = clientConnectedCb;
                m_clientDisconnectedCb = clientDisconnectedCb;
                return true;
            }));
}

void SessionManagementServerTests::serverWillFailToInitialize()
{
    EXPECT_CALL(*m_serverMock, addSocket(socketName, _, _)).WillOnce(Return(false));
}

void SessionManagementServerTests::serverWillStart()
{
    EXPECT_CALL(*m_serverMock, process()).WillOnce(Return(false));
}

void SessionManagementServerTests::clientWillConnect()
{
    EXPECT_CALL(*m_mediaPipelineModuleMock,
                clientConnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_mediaKeysModuleMock,
                clientConnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_mediaKeysCapabilitiesModuleMock,
                clientConnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_rialtoControlModuleMock,
                clientConnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
}

void SessionManagementServerTests::clientWillDisconnect()
{
    EXPECT_CALL(*m_mediaKeysCapabilitiesModuleMock,
                clientDisconnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_mediaKeysModuleMock,
                clientDisconnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_mediaPipelineModuleMock,
                clientDisconnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
    EXPECT_CALL(*m_rialtoControlModuleMock,
                clientDisconnected(std::dynamic_pointer_cast<::firebolt::rialto::ipc::IClient>(m_clientMock)));
}

void SessionManagementServerTests::serverWillSetLogLevels()
{
    EXPECT_CALL(*m_clientMock,
                sendEvent(SetLogLevelsEventMatcher(defaultLogLevels, clientLogLevels, ipcLogLevels, commonLogLevels)));
}

void SessionManagementServerTests::sendServerInitialize()
{
    EXPECT_TRUE(m_sut->initialize(socketName));
}

void SessionManagementServerTests::sendServerInitializeAndExpectFailure()
{
    EXPECT_FALSE(m_sut->initialize(socketName));
}

void SessionManagementServerTests::sendServerStart()
{
    m_sut->start();
}

void SessionManagementServerTests::sendConnectClient()
{
    m_clientConnectedCb(m_clientMock);
}

void SessionManagementServerTests::sendDisconnectClient()
{
    m_clientDisconnectedCb(m_clientMock);
}

void SessionManagementServerTests::sendSetLogLevels()
{
    m_sut->setLogLevels(defaultLogLevels, clientLogLevels, ipcLogLevels, commonLogLevels);
}
