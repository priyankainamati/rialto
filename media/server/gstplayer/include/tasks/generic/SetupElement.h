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

#ifndef FIREBOLT_RIALTO_SERVER_SETUP_ELEMENT_H_
#define FIREBOLT_RIALTO_SERVER_SETUP_ELEMENT_H_

#include "GenericPlayerContext.h"
#include "IGlibWrapper.h"
#include "IGstGenericPlayerPrivate.h"
#include "IGstWrapper.h"
#include "IPlayerTask.h"
#include <gst/gst.h>
#include <memory>

namespace firebolt::rialto::server
{
class SetupElement : public IPlayerTask
{
public:
    SetupElement(GenericPlayerContext &context, std::shared_ptr<IGstWrapper> gstWrapper,
                 std::shared_ptr<IGlibWrapper> glibWrapper, IGstGenericPlayerPrivate &player, GstElement *element);
    ~SetupElement() override;
    void execute() const override;

private:
    GenericPlayerContext &m_context;
    std::shared_ptr<IGstWrapper> m_gstWrapper;
    std::shared_ptr<IGlibWrapper> m_glibWrapper;
    IGstGenericPlayerPrivate &m_player;
    GstElement *m_element;
};
} // namespace firebolt::rialto::server

#endif // FIREBOLT_RIALTO_SERVER_SETUP_ELEMENT_H_