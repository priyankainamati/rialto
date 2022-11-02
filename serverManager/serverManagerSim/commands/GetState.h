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

#ifndef RIALTO_SERVERMANAGER_GET_STATE_H_
#define RIALTO_SERVERMANAGER_GET_STATE_H_

#include "Command.h"

namespace rialto::servermanager
{
class HttpRequest;
class TestService;
} // namespace rialto::servermanager

namespace rialto::servermanager
{
class GetState : public Command
{
public:
    GetState(TestService &service, const HttpRequest &request);
    virtual ~GetState() = default;

    void run() const override;

private:
    TestService &m_service;
    const HttpRequest &m_kRequest;
};
} // namespace rialto::servermanager

#endif // RIALTO_SERVERMANAGER_GET_STATE_H_
