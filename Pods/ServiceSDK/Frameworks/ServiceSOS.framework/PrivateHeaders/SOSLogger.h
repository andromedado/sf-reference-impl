/*
 * Copyright 2016 salesforce.com, inc.
 * All rights reserved.
 *
 * Use of this software is subject to the salesforce.com Developerforce Terms of
 * Use and other applicable terms that salesforce.com may make available, as may be
 * amended from time to time. You may not decompile, reverse engineer, disassemble,
 * attempt to derive the source code of, decrypt, modify, or create derivative
 * works of this software, updates thereto, or any part thereof. You may not use
 * the software to engage in any development activity that infringes the rights of
 * a third party, including that which interferes with, damages, or accesses in an
 * unauthorized manner the servers, networks, or other properties or services of
 * salesforce.com or any third party.
 *
 * WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, THE SOFTWARE IS PROVIDED
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. IN NO EVENT SHALL
 * SALESFORCE.COM HAVE ANY LIABILITY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO,
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, PUNITIVE, OR CONSEQUENTIAL DAMAGES, OR
 * DAMAGES BASED ON LOST PROFITS, DATA OR USE, IN CONNECTION WITH THE SOFTWARE,
 * HOWEVER CAUSED AND, WHETHER IN CONTRACT, TORT OR UNDER ANY OTHER THEORY OF
 * LIABILITY, WHETHER OR NOT YOU HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGES.
 */

#import <Foundation/Foundation.h>
#import "SOSSessionManager.h"
@import ServiceCore.ServiceCommon;
@import ServiceCore.ServiceCommon.Private;
@import ServiceCore.SalesforceOffline;

NS_ASSUME_NONNULL_BEGIN
extern const NSInteger kSOSLoggingSeverityLevelError;
extern const NSInteger kSOSLoggingSeverityLevelWarning;
extern const NSString *kSOSRequestDateFormatter;
extern const NSString *kSOSLoggerStartedAtField;
extern const NSString *kSOSLoggerEndedAtField;
extern const NSString *kSOSLoggerDescriptionField;
extern const NSString *kSOSResultField;
extern const NSString *kSOSPacketLossRatioField;
extern const NSString *kSOSBandwidthField;
extern const NSString *kSOSTestTypeField;
extern const NSString *kSOSOpenTokNetworkTestValue;
extern const NSString *kSOSStatusField;
extern const NSString *kSOSOrientationField;
extern const NSString *kSOSCallStateField;
extern const NSString *kSOSDescription;
extern const NSString *kSOSRecording;
extern const NSString *kSOSDeviceField;
extern const NSString *kSOSApplicationField;
extern const NSString *kSOSSDKField;
extern const NSString *kSOSOSField;
extern const NSString *kSOSBatteryLevelField;
extern const NSString *kSOSConnectivityBackgoundedField;
extern const NSString *kSOSConnectivityTechnologyField;
extern const NSString *kSOSOrgIdField;
extern const NSString *kSOSServiceField;
extern const NSString *kSOSClientTimestampField;
extern const NSString *kSOSClientTypeField;
extern const NSString *kSOSSessionIdField;
extern const NSString *kSOSDeploymentIdField;

/**
 *  List of Timer-specific logging types which can be tracked.
 */
typedef NS_ENUM(NSInteger, SOSTelemetryLogStream) {
    /**
     * Telemetry stream for user confirmation.
     */
    SOSTelemetryLogStreamUserConfirmation = 0,
    /**
     * Telemetry stream for network tests.
     */
    SOSTelemetryLogStreamNetworkTest,
    /**
     * Telemetry stream for waiting in the LA queue.
     */
    SOSTelemetryLogStreamWaiting,
    /**
     * Telemetry stream for when joining a session.
     */
    SOSTelemetryLogStreamJoining,
    /**
     * Telemetry stream for being connected to a session.
     */
    SOSTelemetryLogStreamConnected
};

/**
 *  SOSLog Timer Code enum.
 *  See the schema for information: https://github.com/goinstant/schema/blob/master/schemas/common/messages/timer.json
 */
typedef NS_ENUM(NSInteger, SOSLogTimerCode) {
    /**
     *  userequest-to-inqueue
     */
    SOSLogUserRequestToInqueue = 0,
    /**
     *  networkteststart-to-networktestend
     */
    SOSLogNetworkTestStartToNetworkTestEnd,
    /**
     *  inqueue-to-agentaccept
     */
    SOSLogInQueueToAgentAccept,
    /**
     *  agentaccept-to-connected
     */
    SOSLogAgentAcceptToConnected,
    /**
     *  capture-screen-to-camera
     */
    SOSLogCaptureScreenToCamera,
    /**
     *  capture-camera-to-screen
     */
    SOSLogCaptureCameraToScreen,
    /**
     *  capture-swap-camera
     */
    SOSLogCaptureSwapCamera,
    /**
     *  onload-to-widget-ready
     */
    SOSLogOnloadToWidgetReady
};


@interface SOSLogger : SCSLogger

/**
 *  SOSLogging singleton which manages all logging messages generated by SOS.
 */
- (id)initWithSOS:(SOSSessionManager *__weak)sos withCompletion:(void(^)(BOOL ready))completion;;

- (void)cleanUpLoggingSession;

+ (void)lifeCycleStates:(NSDictionary *)lifeCycleStates;
+ (void)lifeCycleStates:(NSDictionary *)lifeCycleStates stopReason:(SOSStopReason)stopReason;
+ (void)eventLogDictionaryWithEvent:(NSString*)event lifeCycle:(NSString*)lifeCycle;
+ (void)logDeviceInformation;
+ (void)fieldMasking:(BOOL)isMasked;
+ (void)AVSessionReference:(NSString*)sessionRef;
+ (void)networkTestLogDictionaryWithStats:(NSDictionary*)stats;
+ (void)connectionStatusLogDictionaryWithStats:(NSDictionary*)stats;
+ (void)phoneCallLogDictionary:(NSString*)callState;
+ (void)recording:(BOOL)recording;
+ (void)sessionInfo:(NSDictionary*)sessionInfo;
+ (void)dataLogDictionaryWithStats:(NSDictionary*)stats;
+ (void)agentAvailability:(NSString *)response;
+ (void)error:(NSString *)error severity:(NSInteger)severity;
+ (void)error:(NSString *)error type:(NSString *)type domain:(NSString*)domain code:(NSString*)code severity:(NSInteger)severity;
+ (void)qos:(NSDictionary *)qos;

+ (void)batteryLevel:(float)level;
+ (void)orientation:(NSString *)orientation;
+ (void)appIsBackgrounded:(BOOL)isBackgrounded;
+ (void)connectivityStatus:(SFSDKReachabilityNetworkStatus)status;
+ (void)debug:(NSString *)debug;
+ (void)logTelemetry:(NSDictionary *)data;
+ (void)addTimestampForStream:(SOSTelemetryLogStream)stream;
+ (void)sendTimestampLogForStream:(SOSTelemetryLogStream)fromStream description:(SOSLogTimerCode)description;

@end

NS_ASSUME_NONNULL_END
