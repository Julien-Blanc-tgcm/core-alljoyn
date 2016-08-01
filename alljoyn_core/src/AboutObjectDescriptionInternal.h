/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
#ifndef _ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H
#define _ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H

#include <alljoyn/AboutObjectDescription.h>
#include <qcc/Mutex.h>
#include <qcc/LockLevel.h>

#include <set>
#include <map>

namespace ajn {
/**
 * Class used to hold internal values for the AboutObjectDescription
 */
class AboutObjectDescription::Internal {
    friend class AboutObjectDescription;
  public:
    Internal() : announceObjectsMapLock(qcc::LOCK_LEVEL_ABOUTOBJECTDESCRIPTION_INTERNAL_ANNOUNCEOBJECTSMAPLOCK) { }

    AboutObjectDescription::Internal& operator=(const AboutObjectDescription::Internal& other) {
        announceObjectsMap = other.announceObjectsMap;
        return *this;
    }

  private:
    /**
     * Mutex that protects the announceObjectsMap
     *
     * this is marked as mutable so we can grab the lock to prevent the Objects
     * map being modified while its being read.
     */
    mutable qcc::Mutex announceObjectsMapLock;

    /**
     *  map that holds interfaces
     */
    std::map<qcc::String, std::set<qcc::String> > announceObjectsMap;
};
}
#endif //_ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H