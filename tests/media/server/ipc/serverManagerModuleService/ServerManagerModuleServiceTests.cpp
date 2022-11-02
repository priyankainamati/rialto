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

TEST_F(ServerManagerModuleServiceTests, shouldSetConfiguration)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetConfiguration(firebolt::rialto::server::SessionServerState::ACTIVE);
    sessionServerManagerWillSetLogLevels();
    sendSetConfiguration(firebolt::rialto::server::SessionServerState::ACTIVE);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetStateToUninitialized)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetState(firebolt::rialto::server::SessionServerState::UNINITIALIZED);
    sendSetState(firebolt::rialto::server::SessionServerState::UNINITIALIZED);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetStateToInactive)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetState(firebolt::rialto::server::SessionServerState::INACTIVE);
    sendSetState(firebolt::rialto::server::SessionServerState::INACTIVE);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetStateToActive)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetState(firebolt::rialto::server::SessionServerState::ACTIVE);
    sendSetState(firebolt::rialto::server::SessionServerState::ACTIVE);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetStateToNotRunning)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetState(firebolt::rialto::server::SessionServerState::NOT_RUNNING);
    sendSetState(firebolt::rialto::server::SessionServerState::NOT_RUNNING);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetStateToError)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetState(firebolt::rialto::server::SessionServerState::ERROR);
    sendSetState(firebolt::rialto::server::SessionServerState::ERROR);
}

TEST_F(ServerManagerModuleServiceTests, shouldSetLogLevels)
{
    sessionServerManagerWillHandleRequestSuccess();
    sessionServerManagerWillSetLogLevels();
    sendSetLogLevels();
}

TEST_F(ServerManagerModuleServiceTests, shouldFailToSetConfiguration)
{
    sessionServerManagerWillHandleRequestFailure();
    sessionServerManagerWillFailToSetConfiguration(firebolt::rialto::server::SessionServerState::ACTIVE);
    sessionServerManagerWillSetLogLevels();
    sendSetConfiguration(firebolt::rialto::server::SessionServerState::ACTIVE);
}

TEST_F(ServerManagerModuleServiceTests, shouldFailToSetState)
{
    sessionServerManagerWillHandleRequestFailure();
    sessionServerManagerWillFailToSetState(firebolt::rialto::server::SessionServerState::ACTIVE);
    sendSetState(firebolt::rialto::server::SessionServerState::ACTIVE);
}
