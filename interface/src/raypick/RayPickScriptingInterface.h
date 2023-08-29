//
//  RayPickScriptingInterface.h
//  interface/src/raypick
//
//  Created by Sam Gondelman 8/15/2017
//  Copyright 2017 High Fidelity, Inc.
//  Copyright 2023 Overte e.V.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//  SPDX-License-Identifier: Apache-2.0
//
#ifndef hifi_RayPickScriptingInterface_h
#define hifi_RayPickScriptingInterface_h

#include <QtCore/QObject>

#include "RegisteredMetaTypes.h"
#include <DependencyManager.h>

#include "PickScriptingInterface.h"

class ScriptValue;

/*@jsdoc
 * The <code>RayPick</code> API is a subset of the {@link Picks} API, as used for ray picks.
 *
 * @namespace RayPick
 *
 * @deprecated This API is deprecated and will be removed. Use the {@link Picks} API instead.
 *
 * @hifi-interface
 * @hifi-client-entity
 * @hifi-avatar
 */
class RayPickScriptingInterface : public QObject, public Dependency {
    Q_OBJECT
    SINGLETON_DEPENDENCY

public:

    /*@jsdoc
     * Creates a new ray pick.
     * <p><strong>Warning:</strong> Picks created using this method currently always intersect at least visible and collidable
     * things but this may not always be the case.</p>
     * @function RayPick.createRayPick
     * @param {Picks.RayPickProperties} properties - Properties of the pick.
     * @returns {number} The ID of the pick created. <code>0</code> if invalid.
     */
    Q_INVOKABLE unsigned int createRayPick(const QVariant& properties);

    /*@jsdoc
     * Enables a ray pick.
     * @function RayPick.enableRayPick
     * @param {number} id - The ID of the ray pick.
     */
    Q_INVOKABLE void enableRayPick(unsigned int uid);

    /*@jsdoc
     * Disables a ray pick.
     * @function RayPick.disableRayPick
     * @param {number} id - The ID of the ray pick.
     */
    Q_INVOKABLE void disableRayPick(unsigned int uid);

    /*@jsdoc
     * Removes (deletes) a ray pick.
     * @function RayPick.removeRayPick
     * @param {number} id - The ID of the ray pick.
     */
    Q_INVOKABLE void removeRayPick(unsigned int uid);

    /*@jsdoc
     * Gets the most recent pick result from a ray pick. A ray pick continues to be updated ready to return a result, as long
     * as it is enabled.
     * @function RayPick.getPrevRayPickResult
     * @param {number} id - The ID of the ray pick.
     * @returns {RayPickResult}
     */
    Q_INVOKABLE QVariantMap getPrevRayPickResult(unsigned int uid);


    /*@jsdoc
     * Sets whether or not a ray pick should use precision picking, i.e., whether it should pick against precise meshes or
     * coarse meshes.
     * @function RayPick.setPrecisionPicking
     * @param {number} id - The ID of the ray pick.
     * @param {boolean} precisionPicking - <code>true</code> to use precision picking, <code>false</code> to use coarse picking.
     */
    Q_INVOKABLE void setPrecisionPicking(unsigned int uid, bool precisionPicking);

    /*@jsdoc
     * Sets a list of entity and avatar IDs that a ray pick should ignore during intersection.
     * @function RayPick.setIgnoreItems
     * @param {number} id - The ID of the ray pick.
     * @param {Uuid[]} ignoreItems - The list of IDs to ignore.
     */
    Q_INVOKABLE void setIgnoreItems(unsigned int uid, const ScriptValue& ignoreEntities);

    /*@jsdoc
     * Sets a list of entity and avatar IDs that a ray pick should include during intersection, instead of intersecting with
     * everything.
     * @function RayPick.setIncludeItems
     * @param {number} id - The ID of the ray pick.
     * @param {Uuid[]} includeItems - The list of IDs to include.
     */
    Q_INVOKABLE void setIncludeItems(unsigned int uid, const ScriptValue& includeEntities);


    /*@jsdoc
     * Checks if a pick is associated with the left hand: a ray or parabola pick with <code>joint</code> property set to
     * <code>"_CONTROLLER_LEFTHAND"</code> or <code>"_CAMERA_RELATIVE_CONTROLLER_LEFTHAND"</code>, or a stylus pick with
     * <code>hand</code> property set to <code>0</code>.
     * @function RayPick.isLeftHand
     * @param {number} id - The ID of the ray pick.
     * @returns {boolean} <code>true</code> if the pick is associated with the left hand, <code>false</code> if it isn't.
     */
    Q_INVOKABLE bool isLeftHand(unsigned int uid);

    /*@jsdoc
     * Checks if a pick is associated with the right hand: a ray or parabola pick with <code>joint</code> property set to
     * <code>"_CONTROLLER_RIGHTHAND"</code> or <code>"_CAMERA_RELATIVE_CONTROLLER_RIGHTHAND"</code>, or a stylus pick with
     * <code>hand</code> property set to <code>1</code>.
     * @function RayPick.isRightHand
     * @param {number} id - The ID of the ray pick.
     * @returns {boolean} <code>true</code> if the pick is associated with the right hand, <code>false</code> if it isn't.
     */
    Q_INVOKABLE bool isRightHand(unsigned int uid);

    /*@jsdoc
     * Checks if a pick is associated with the system mouse: a ray or parabola pick with <code>joint</code> property set to
     * <code>"Mouse"</code>.
     * @function RayPick.isMouse
     * @param {number} id - The ID of the ray pick.
     * @returns {boolean} <code>true</code> if the pick is associated with the system mouse, <code>false</code> if it isn't.
     */
    Q_INVOKABLE bool isMouse(unsigned int uid);
};

#endif // hifi_RayPickScriptingInterface_h
