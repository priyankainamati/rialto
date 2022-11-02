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

#ifndef FIREBOLT_RIALTO_IPC_MOCK_IPC_CONTROLLER_MOCK_H_
#define FIREBOLT_RIALTO_IPC_MOCK_IPC_CONTROLLER_MOCK_H_

#include "IIpcController.h"
#include <gmock/gmock.h>
#include <memory>
#include <string>

namespace firebolt::rialto::ipc::mock
{
class ControllerMock : public IController
{
public:
    ControllerMock() = default;
    virtual ~ControllerMock() = default;

    MOCK_METHOD(std::shared_ptr<IClient>, getClient, (), (override, const));
    MOCK_METHOD(void, Reset, (), (override));
    MOCK_METHOD(bool, Failed, (), (override, const));
    MOCK_METHOD(std::string, ErrorText, (), (override, const));
    MOCK_METHOD(void, StartCancel, (), (override));
    MOCK_METHOD(void, SetFailed, (const std::string &reason), (override));
    MOCK_METHOD(bool, IsCanceled, (), (override, const));
    MOCK_METHOD(void, NotifyOnCancel, (google::protobuf::Closure * callback), (override));
};
} // namespace firebolt::rialto::ipc::mock

#endif // FIREBOLT_RIALTO_IPC_MOCK_IPC_CONTROLLER_MOCK_H_
