//
//  AccountServicesScriptingInterface.h
//  interface/src/scripting
//
//  Created by Thijs Wenker on 9/10/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AccountServicesScriptingInterface_h
#define hifi_AccountServicesScriptingInterface_h

#include <QObject>
#include <QScriptContext>
#include <QScriptEngine>
#include <QScriptValue>
#include <QString>
#include <QStringList>

#include <AccountManager.h>
#include <DiscoverabilityManager.h>

class DownloadInfoResult {
public:
    DownloadInfoResult();
    QList<float> downloading;  // List of percentages
    float pending;
};

Q_DECLARE_METATYPE(DownloadInfoResult)

QScriptValue DownloadInfoResultToScriptValue(QScriptEngine* engine, const DownloadInfoResult& result);
void DownloadInfoResultFromScriptValue(const QScriptValue& object, DownloadInfoResult& result);

class AccountServicesScriptingInterface : public QObject {
    Q_OBJECT

    /**jsdoc
     * The <code>AccountServices</code> API provides functions related to user connectivity, visibility, and asset download 
     * progress.
     * 
     * @hifi-interface
     * @hifi-client-entity
     *
     * @namespace AccountServices
     * @property {string} username - The user name if the user is logged in, otherwise <code>"Unknown user"</code>.
     *     <em>Read-only.</em>
     * @property {boolean} loggedIn - <code>true</code> if the user is logged in, otherwise <code>false</code>. 
     *     <em>Read-only.</em>
     * @property {string} findableBy - The user's visibility to other people:<br />
     *     <code>"none"</code> - user appears offline.<br />
     *     <code>"friends"</code> - user is visible only to friends.<br />
     *     <code>"connections"</code> - user is visible to friends and connections.<br />
     *     <code>"all"</code> - user is visible to everyone.
     * @property {string} metaverseServerURL - The metaverse server that the user is authenticated against when logged in 
     *     &mdash; typically <code>"https://metaverse.highfidelity.com"</code>. <em>Read-only.</em>
     */

    Q_PROPERTY(QString username READ getUsername NOTIFY myUsernameChanged)
    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged)
    Q_PROPERTY(QString findableBy READ getFindableBy WRITE setFindableBy NOTIFY findableByChanged)
    Q_PROPERTY(QUrl metaverseServerURL READ getMetaverseServerURL CONSTANT)
    
public:
    static AccountServicesScriptingInterface* getInstance();

    const QString getUsername() const;
    bool loggedIn() const { return _loggedIn; }
    QUrl getMetaverseServerURL() { return DependencyManager::get<AccountManager>()->getMetaverseServerURL(); }
    
public slots:

    /**jsdoc
     * Get information on the progress of downloading assets in the domain.
     * @function AccountServices.getDownloadInfo
     * @returns {AccountServices.DownloadInfoResult} Information on the progress of assets download.
     */
    DownloadInfoResult getDownloadInfo();

    /**jsdoc
     * Cause a {@link AccountServices.downloadInfoChanged|downloadInfoChanged} signal to be triggered with information on the 
     * current progress of the download of assets in the domain.
     * @function AccountServices.updateDownloadInfo
     */
    void updateDownloadInfo();

    /**jsdoc
     * Check whether the user is logged in.
     * @function AccountServices.isLoggedIn
     * @returns {boolean} <code>true</code> if the user is logged in, <code>false</code> otherwise.
     * @example <caption>Report whether you are logged in.</caption>
     * var isLoggedIn = AccountServices.isLoggedIn();
     * print("You are logged in: " + isLoggedIn);  // true or false
     */
    bool isLoggedIn();

    /**jsdoc
     * Prompts the user to log in (the login dialog is displayed) if they're not already logged in.
     * @function AccountServices.checkAndSignalForAccessToken
     * @returns {boolean} <code>true</code> if the user is already logged in, <code>false</code> otherwise.
     */
    bool checkAndSignalForAccessToken();

    /**jsdoc
     * Logs the user out.
     * @function AccountServices.logOut
     */
    void logOut();
    
private slots:
    void loggedOut();
    void checkDownloadInfo();
    
    QString getFindableBy() const;
    void setFindableBy(const QString& discoverabilityMode);
    void discoverabilityModeChanged(Discoverability::Mode discoverabilityMode);

    void onUsernameChanged(const QString& username);

signals:

    /**jsdoc
     * Not currently used.
     * @function AccountServices.connected
     * @returns {Signal}
     */
    void connected();

    /**jsdoc
     * Triggered when the user logs out.
     * @function AccountServices.disconnected
     * @param {string} reason - Has the value, <code>"logout"</code>.
     * @returns {Signal}
     */
    void disconnected(const QString& reason);

    /**jsdoc
     * Triggered when the username logged in with changes, i.e., when the user logs in or out.
     * @function AccountServices.myUsernameChanged
     * @param {string} username - The username logged in with if the user is logged in, otherwise <code>""</code>.
     * @returns {Signal}
     * @example <caption>Report when your username changes.</caption>
     * AccountServices.myUsernameChanged.connect(function (username) {
     *     print("Username changed: " + username);
     * });
     */
    void myUsernameChanged(const QString& username);

    /**jsdoc
     * Triggered when the progress of the download of assets for the domain changes.
     * @function AccountServices.downloadInfoChanged
     * @param {AccountServices.DownloadInfoResult} downloadInfo - Information on the progress of assets download.
     * @returns {Signal}
     */
    void downloadInfoChanged(DownloadInfoResult info);

    /**jsdoc
     * Triggered when the user's visibility to others changes.
     * @function AccountServices.findableByChanged
     * @param {string} findableBy - The user's visibility to other people:<br />
     *     <code>"none"</code> - user appears offline.<br />
     *     <code>"friends"</code> - user is visible only to friends.<br />
     *     <code>"connections"</code> - user is visible to friends and connections.<br />
     *     <code>"all"</code> - user is visible to everyone.
     * @returns {Signal}
     * @example <caption>Report when your visiblity changes.</caption>
     * AccountServices.findableByChanged.connect(function (findableBy) {
     *     print("Findable by changed: " + findableBy);
     * });
     * 
     * var originalFindableBy = AccountServices.findableBy;
     * Script.setTimeout(function () {
     *     // Change visiblity.
     *     AccountServices.findableBy = originalFindableBy === "none" ? "all" : "none";
     * }, 2000);
     * Script.setTimeout(function () {
     *     // Restore original visibility.
     *     AccountServices.findableBy = originalFindableBy;
     * }, 4000);
     */
    void findableByChanged(const QString& discoverabilityMode);

    /**jsdoc
     * Triggered when the login status of the user changes.
     * @function AccountServices.loggedInChanged
     * @param {boolean} loggedIn - <code>true</code> if the user is logged in, otherwise <code>false</code>.
     * @returns {Signal}
     * @example <caption>Report when your login status changes.</caption>
     * AccountServices.loggedInChanged.connect(function(loggedIn) {
     *     print("Logged in: " + loggedIn);
     * });
     */
    void loggedInChanged(bool loggedIn);

private:
    AccountServicesScriptingInterface();
    ~AccountServicesScriptingInterface();
    
    bool _downloading;
    bool _loggedIn{ false };
};

#endif // hifi_AccountServicesScriptingInterface_h
