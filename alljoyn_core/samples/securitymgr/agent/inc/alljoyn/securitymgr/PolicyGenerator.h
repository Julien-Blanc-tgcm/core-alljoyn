#ifndef ALLJOYN_SECMGR_POLICYGENERATOR_H_
#define ALLJOYN_SECMGR_POLICYGENERATOR_H_

/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <vector>

#include <qcc/GUID.h>
#include <qcc/CryptoECC.h>

#include <alljoyn/PermissionPolicy.h>
#include <alljoyn/Status.h>

#include "GroupInfo.h"

namespace ajn {
namespace securitymgr {
/**
 * @brief PolicyGenerator, helps in generating default policies.
 */
class PolicyGenerator {
  public:
    /*
     * @brief Constructor for PolicyGenerator.
     *
     *        Each policy generated by an instance, will have a section allowing
     *        members of the AdminGroup to make changes to the security
     *        configuration.
     *
     * @param[in]  _adminGroup  The AdminGroup for which a special administrator
     *                          section will be added to each policy generated by
     *                          this instance.
     */
    PolicyGenerator(GroupInfo& _adminGroup) :
        adminGroup(_adminGroup) { };

    /*
     * @brief Generate a default policy.
     *
     *        The default policy allows any member of the specified groups to
     *        provide any interface to this application and to modify any
     *        interface provided by this application.
     *
     * @param[in]  groupInfos  The groups in the generated policy.
     * @param[out] policy      The generated policy.
     *
     * @return ER_OK           If policy was generated successfully.
     * @return others          On failure.
     */
    QStatus DefaultPolicy(const vector<GroupInfo>& groupInfos,
                          PermissionPolicy& policy) const;

    /**
     * @brief Vector containing all KeyInfo objects of applications for which
     *        any access should be denied.
     */
    vector<KeyInfoNISTP256> deniedKeys;

  private:

    /**
     * @brief Generate an ACL for denied applications.
     *
     * @param[in,out] acl   The ACL that will contain the permissions for the
     *                      denied applications.
     */
    void DenyAcl(const vector<KeyInfoNISTP256>& keys,
                 PermissionPolicy::Acl& acl) const;

    /**
     * @brief Generate an ACL for the admin security group.
     *
     * @param[in,out] acl   The ACL that will contain the permissions for the
     *                      admin security group.
     */
    void AdminAcl(PermissionPolicy::Acl& acl) const;

    /**
     * @brief Generate a default ACL for a security group, giving members of
     * this group full access to all interfaces.
     *
     * @param[in,out] acl   The ACL that will contain the default permissions
     *                      for the security group.
     */
    void DefaultGroupPolicyAcl(const GroupInfo& group,
                               PermissionPolicy::Acl& acl) const;

    /**
     * @brief Generate a default rule for a security group, giving members of
     * this group full access to all interfaces.
     *
     * @param[in,out] rule  The rule that will contain the default permissions
     *                      for a security group.
     */

    void DefaultGroupPolicyRule(PermissionPolicy::Rule& rule) const;

    GroupInfo adminGroup;
};
}
}

#endif  /* ALLJOYN_SECMGR_POLICYGENERATOR_H_ */