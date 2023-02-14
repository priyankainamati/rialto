/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 Sky UK
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

#ifndef FIREBOLT_RIALTO_SERVER_TASKS_WEBAUDIO_STOP_H_
#define FIREBOLT_RIALTO_SERVER_TASKS_WEBAUDIO_STOP_H_

#include "IGstWebAudioPlayerPrivate.h"
#include "IPlayerTask.h"

namespace firebolt::rialto::server::tasks::webaudio
{
class Stop : public IPlayerTask
{
public:
    explicit Stop(IGstWebAudioPlayerPrivate &player);
    ~Stop() override;
    void execute() const override;

private:
    IGstWebAudioPlayerPrivate &m_player;
};
} // namespace firebolt::rialto::server::tasks::webaudio

#endif // FIREBOLT_RIALTO_SERVER_TASKS_WEBAUDIO_STOP_H_
