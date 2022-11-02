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

#ifndef SESSION_SERVER_APP_MANAGER_TESTS_FIXTURE_H_
#define SESSION_SERVER_APP_MANAGER_TESTS_FIXTURE_H_

#include "ControllerMock.h"
#include "EventThreadFactoryMock.h"
#include "EventThreadMock.h"
#include "ISessionServerAppManager.h"
#include "SessionServerAppFactoryMock.h"
#include "SessionServerAppMock.h"
#include "StateObserverMock.h"
#include <condition_variable>
#include <gtest/gtest.h>
#include <memory>
#include <mutex>
#include <string>

using testing::StrictMock;

class SessionServerAppManagerTests : public testing::Test
{
public:
    SessionServerAppManagerTests();
    virtual ~SessionServerAppManagerTests() = default;

    void sessionServerLaunchWillFail(const rialto::servermanager::service::SessionServerState &state);
    void sessionServerConnectWillFail(const rialto::servermanager::service::SessionServerState &state);
    void sessionServerChangeStateWillFail(const rialto::servermanager::service::SessionServerState &state);
    void sessionServerWillLaunch(const rialto::servermanager::service::SessionServerState &state);
    void sessionServerWillChangeState(const rialto::servermanager::service::SessionServerState &state);
    void sessionServerWillReturnAppSocketName(const std::string &socketName);
    void sessionServerWillChangeStateToUninitialized();
    void sessionServerWillChangeStateToInactive();
    void sessionServerWillFailToSetConfiguration();
    void sessionServerWillSetLogLevels();
    void sessionServerWillFailToSetLogLevels();
    void sessionServerWillKillRunningApplicationAtTeardown();
    void clientWillBeRemovedAfterStateChangedIndication(const rialto::servermanager::service::SessionServerState &state);

    bool triggerSetSessionServerState(const rialto::servermanager::service::SessionServerState &newState);
    void triggerOnSessionServerStateChanged(const rialto::servermanager::service::SessionServerState &newState);
    std::string triggerGetAppConnectionInfo();
    bool triggerSetLogLevel();

private:
    std::unique_ptr<rialto::servermanager::ipc::IController> m_controller;
    std::shared_ptr<StrictMock<rialto::servermanager::service::mocks::StateObserverMock>> m_stateObserver;
    std::unique_ptr<rialto::servermanager::common::ISessionServerApp> m_sessionServerApp;
    StrictMock<rialto::servermanager::ipc::mocks::ControllerMock> &m_controllerMock;
    StrictMock<rialto::servermanager::common::mocks::SessionServerAppMock> &m_sessionServerAppMock;
    StrictMock<rialto::servermanager::common::mocks::SessionServerAppFactoryMock> *m_sessionServerAppFactoryMock;
    StrictMock<firebolt::rialto::common::mocks::EventThreadMock> *m_eventThreadMock;
    std::unique_ptr<rialto::servermanager::common::ISessionServerAppManager> m_sut;
};

#endif // SESSION_SERVER_APP_MANAGER_TESTS_FIXTURE_H_
