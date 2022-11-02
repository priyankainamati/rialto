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

#include "ServerManagerModuleServiceTestsFixture.h"
#include "ServerManagerModuleService.h"
#include <string>

using testing::_;
using testing::Return;

namespace
{
const std::string SOCKET_NAME{"/tmp/rialtotest-0"};
constexpr int MAX_SESSIONS{5};
constexpr int socket{2};

rialto::SessionServerState convertSessionServerState(const firebolt::rialto::server::SessionServerState &state)
{
    switch (state)
    {
    case firebolt::rialto::server::SessionServerState::UNINITIALIZED:
        return rialto::SessionServerState::UNINITIALIZED;
    case firebolt::rialto::server::SessionServerState::INACTIVE:
        return rialto::SessionServerState::INACTIVE;
    case firebolt::rialto::server::SessionServerState::ACTIVE:
        return rialto::SessionServerState::ACTIVE;
    case firebolt::rialto::server::SessionServerState::NOT_RUNNING:
        return rialto::SessionServerState::NOT_RUNNING;
    case firebolt::rialto::server::SessionServerState::ERROR:
        return rialto::SessionServerState::ERROR;
    }
    return rialto::SessionServerState::ERROR;
}
} // namespace

ServerManagerModuleServiceTests::ServerManagerModuleServiceTests()
    : m_clientMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ClientMock>>()},
      m_serverMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ServerMock>>()},
      m_closureMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ClosureMock>>()},
      m_controllerMock{std::make_shared<StrictMock<firebolt::rialto::ipc::mock::ControllerMock>>()}
{
    auto sutFactory = firebolt::rialto::server::ipc::IServerManagerModuleServiceFactory::createFactory();
    m_sut = sutFactory->create(m_sessionServerManagerMock);
}

ServerManagerModuleServiceTests::~ServerManagerModuleServiceTests() {}

void ServerManagerModuleServiceTests::sessionServerManagerWillSetConfiguration(
    const firebolt::rialto::server::SessionServerState &state)
{
    EXPECT_CALL(m_sessionServerManagerMock, setConfiguration(SOCKET_NAME, state, MAX_SESSIONS)).WillOnce(Return(true));
}

void ServerManagerModuleServiceTests::sessionServerManagerWillSetState(
    const firebolt::rialto::server::SessionServerState &state)
{
    EXPECT_CALL(m_sessionServerManagerMock, setState(state)).WillOnce(Return(true));
}

void ServerManagerModuleServiceTests::sessionServerManagerWillSetLogLevels()
{
    EXPECT_CALL(m_sessionServerManagerMock,
                setLogLevels(RIALTO_DEBUG_LEVEL_DEBUG, RIALTO_DEBUG_LEVEL_DEBUG, RIALTO_DEBUG_LEVEL_DEBUG,
                             RIALTO_DEBUG_LEVEL_DEBUG, RIALTO_DEBUG_LEVEL_DEBUG, RIALTO_DEBUG_LEVEL_DEBUG));
}

void ServerManagerModuleServiceTests::sessionServerManagerWillFailToSetConfiguration(
    const firebolt::rialto::server::SessionServerState &state)
{
    EXPECT_CALL(m_sessionServerManagerMock, setConfiguration(SOCKET_NAME, state, MAX_SESSIONS)).WillOnce(Return(false));
}

void ServerManagerModuleServiceTests::sessionServerManagerWillFailToSetState(
    const firebolt::rialto::server::SessionServerState &state)
{
    EXPECT_CALL(m_sessionServerManagerMock, setState(state)).WillOnce(Return(false));
}

void ServerManagerModuleServiceTests::sendSetConfiguration(const firebolt::rialto::server::SessionServerState &state)
{
    rialto::SetConfigurationRequest request;
    rialto::SetConfigurationResponse response;

    request.set_sessionmanagementsocketname(SOCKET_NAME);
    request.mutable_resources()->set_maxplaybacks(MAX_SESSIONS);
    request.mutable_loglevels()->set_defaultloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_clientloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_sessionserverloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_ipcloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_servermanagerloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_commonloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.set_initialsessionserverstate(convertSessionServerState(state));

    m_sut->setConfiguration(m_controllerMock.get(), &request, &response, m_closureMock.get());
}

void ServerManagerModuleServiceTests::sendSetState(const firebolt::rialto::server::SessionServerState &state)
{
    rialto::SetStateRequest request;
    rialto::SetStateResponse response;

    request.set_sessionserverstate(convertSessionServerState(state));

    m_sut->setState(m_controllerMock.get(), &request, &response, m_closureMock.get());
}

void ServerManagerModuleServiceTests::sendSetLogLevels()
{
    rialto::SetLogLevelsRequest request;
    rialto::SetLogLevelsResponse response;

    request.mutable_loglevels()->set_defaultloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_clientloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_sessionserverloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_ipcloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_servermanagerloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));
    request.mutable_loglevels()->set_commonloglevels(static_cast<uint32_t>(RIALTO_DEBUG_LEVEL_DEBUG));

    m_sut->setLogLevels(m_controllerMock.get(), &request, &response, m_closureMock.get());
}

void ServerManagerModuleServiceTests::sessionServerManagerWillHandleRequestSuccess()
{
    EXPECT_CALL(*m_closureMock, Run());
}

void ServerManagerModuleServiceTests::sessionServerManagerWillHandleRequestFailure()
{
    EXPECT_CALL(*m_controllerMock, SetFailed(_));
    EXPECT_CALL(*m_closureMock, Run());
}
