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

#ifndef RIALTO_SERVERMANAGER_COMMON_MOCKS_SESSION_SERVER_APP_MOCK_H_
#define RIALTO_SERVERMANAGER_COMMON_MOCKS_SESSION_SERVER_APP_MOCK_H_

#include "ISessionServerApp.h"
#include <gmock/gmock.h>
#include <string>

namespace rialto::servermanager::common::mocks
{
class SessionServerAppMock : public ISessionServerApp
{
public:
    SessionServerAppMock() = default;
    virtual ~SessionServerAppMock() = default;

    MOCK_METHOD(bool, launch, (), (override));
    MOCK_METHOD(std::string, getSessionManagementSocketName, (), (const, override));
    MOCK_METHOD(service::SessionServerState, getInitialState, (), (const, override));
    MOCK_METHOD(int, getAppManagementSocketName, (), (const, override));
    MOCK_METHOD(int, getMaxPlaybackSessions, (), (const, override));
    MOCK_METHOD(void, cancelStartupTimer, (), (override));
    MOCK_METHOD(void, kill, (), (const, override));
};
} // namespace rialto::servermanager::common::mocks

#endif // RIALTO_SERVERMANAGER_COMMON_MOCKS_SESSION_SERVER_APP_MOCK_H_
