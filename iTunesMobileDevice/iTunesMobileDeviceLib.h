
#include <Windows.h>

typedef unsigned int mach_error_t;
typedef unsigned int afc_error_t;

static HINSTANCE MobileDeviceDllHandle = NULL;

#include "TypeDefs.h"
#include "StaticFunctionPointers.h"

#define GET_METHOD_PROC_ADDR(v) method_##v## = (tf_##v##)GetProcAddress(dllHandle, #v); \
	if (!method_##v##) \
	{ \
		MessageBoxA(NULL, #v, "Error loading method", MB_OK | MB_ICONERROR); \
		return -1; \
	} \

static mach_error_t LoadReadMobileDeviceLibrary()
{
	/*while (!IsDebuggerPresent())
		Sleep(100);
	DebugBreak();*/

	if (MobileDeviceDllHandle)
		return 0;

	HINSTANCE dllHandle;
	DWORD retaddr;

	dllHandle = LoadLibraryA("iTunesMobileDeviceReal.dll");
	if (!dllHandle)
	{
		MessageBoxA(NULL, "Failed to load iTunesMobileDeviceReal.dll!", "Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	GET_METHOD_PROC_ADDR(AFCErrnoToAFCError);
	GET_METHOD_PROC_ADDR(AMDeviceRelease);
	GET_METHOD_PROC_ADDR(AMDeviceRetain);
	GET_METHOD_PROC_ADDR(AFCConnectionClose);
	GET_METHOD_PROC_ADDR(AMDeviceConnect);
	GET_METHOD_PROC_ADDR(AMDeviceGetInterfaceType);
	GET_METHOD_PROC_ADDR(AMDeviceNotificationSubscribe);
	GET_METHOD_PROC_ADDR(AMDeviceStartHouseArrestService);
	GET_METHOD_PROC_ADDR(AMDeviceStartService);
	GET_METHOD_PROC_ADDR(AMDeviceStartServiceWithOptions);
	GET_METHOD_PROC_ADDR(AMDeviceStartSession);
	GET_METHOD_PROC_ADDR(AMDeviceStopSession);
	GET_METHOD_PROC_ADDR(AMDeviceTransferApplication);
	GET_METHOD_PROC_ADDR(AMDeviceTransferPath);
	GET_METHOD_PROC_ADDR(AMDeviceUninstallApplication);
	GET_METHOD_PROC_ADDR(AMDeviceUnpair);
	GET_METHOD_PROC_ADDR(AMDeviceUpgradeApplication);
	GET_METHOD_PROC_ADDR(AMDeviceValidatePairing);
	GET_METHOD_PROC_ADDR(AFCLockCreate);
	GET_METHOD_PROC_ADDR(AFCLockFree);
	GET_METHOD_PROC_ADDR(AFCLockLock);
	GET_METHOD_PROC_ADDR(AFCLockTryLock);
	GET_METHOD_PROC_ADDR(AFCLockUnlock);
	GET_METHOD_PROC_ADDR(AFCStringCopy);
	GET_METHOD_PROC_ADDR(AMSAddAppleSearchPathsToEnvironmentFromReg);
	GET_METHOD_PROC_ADDR(MISProfileCopyPayload);
	GET_METHOD_PROC_ADDR(MISProfileCopySignerSubjectSummary);
	GET_METHOD_PROC_ADDR(MISProfileCreateDataRepresentation);
	GET_METHOD_PROC_ADDR(MISProfileCreateWithData);
	GET_METHOD_PROC_ADDR(MISProfileCreateWithFile);
	GET_METHOD_PROC_ADDR(MISProfileGetValue);
	GET_METHOD_PROC_ADDR(MISProfileIsMutable);
	GET_METHOD_PROC_ADDR(MISProfileValidateSignature);
	GET_METHOD_PROC_ADDR(MISProfileValidateSignatureWithAnchors);
	GET_METHOD_PROC_ADDR(MISProfileWriteToFile);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileCheckValidity);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetCreationDate);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetDeveloperCertificates);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetExpirationDate);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetName);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetProvisionedDevices);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetUUID);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileGetVersion);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileIncludesDevice);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileProvisionsAllDevices);
	GET_METHOD_PROC_ADDR(MISProvisioningProfileValidateSignature);
	GET_METHOD_PROC_ADDR(USBMuxListenForDevices);
	GET_METHOD_PROC_ADDR(AFCConnectionCopyLastErrorInfo);
	GET_METHOD_PROC_ADDR(AFCConnectionCreate);
	GET_METHOD_PROC_ADDR(AFCConnectionGetContext);
	GET_METHOD_PROC_ADDR(AFCConnectionGetFSBlockSize);
	GET_METHOD_PROC_ADDR(AFCConnectionGetIOTimeout);
	GET_METHOD_PROC_ADDR(AFCConnectionGetSecureContext);
	GET_METHOD_PROC_ADDR(AFCConnectionGetSocketBlockSize);
	GET_METHOD_PROC_ADDR(AFCConnectionGetStatus);
	GET_METHOD_PROC_ADDR(AFCConnectionGetTypeID);
	GET_METHOD_PROC_ADDR(AFCConnectionInvalidate);
	GET_METHOD_PROC_ADDR(AFCConnectionIsValid);
	GET_METHOD_PROC_ADDR(AFCConnectionOpen);
	GET_METHOD_PROC_ADDR(AFCConnectionProcessOperation);
	GET_METHOD_PROC_ADDR(AFCConnectionProcessOperations);
	GET_METHOD_PROC_ADDR(AFCConnectionScheduleWithRunLoop);
	GET_METHOD_PROC_ADDR(AFCConnectionSetCallBack);
	GET_METHOD_PROC_ADDR(AFCConnectionSetContext);
	GET_METHOD_PROC_ADDR(AFCConnectionSetDisposeSecureContextOnInvalidate);
	GET_METHOD_PROC_ADDR(AFCConnectionSetFSBlockSize);
	GET_METHOD_PROC_ADDR(AFCConnectionSetFatalError);
	GET_METHOD_PROC_ADDR(AFCConnectionSetIOTimeout);
	GET_METHOD_PROC_ADDR(AFCConnectionSetSecureContext);
	GET_METHOD_PROC_ADDR(AFCConnectionSetSocketBlockSize);
	GET_METHOD_PROC_ADDR(AFCConnectionSubmitOperation);
	GET_METHOD_PROC_ADDR(AFCConnectionUnscheduleFromRunLoop);
	GET_METHOD_PROC_ADDR(AFCCopyErrorString);
	GET_METHOD_PROC_ADDR(AFCCopyPacketTypeString);
	GET_METHOD_PROC_ADDR(AFCDeviceInfoOpen);
	GET_METHOD_PROC_ADDR(AFCDirectoryClose);
	GET_METHOD_PROC_ADDR(AFCDirectoryCreate);
	GET_METHOD_PROC_ADDR(AFCDirectoryOpen);
	GET_METHOD_PROC_ADDR(AFCDirectoryRead);
	GET_METHOD_PROC_ADDR(AFCDiscardBodyData);
	GET_METHOD_PROC_ADDR(AFCDiscardData);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateCloseOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateGetPositionOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateLockOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateReadAtPositionOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateReadOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateSetImmutableHintOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateSetPositionOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateSetSizeOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateUnlockOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateWriteAtPositionOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorCreateWriteOperation);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorGetTypeID);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorInvalidate);
	GET_METHOD_PROC_ADDR(AFCFileDescriptorIsValid);
	GET_METHOD_PROC_ADDR(AFCFileInfoOpen);
	GET_METHOD_PROC_ADDR(AFCFileRefClose);
	GET_METHOD_PROC_ADDR(AFCFileRefLock);
	GET_METHOD_PROC_ADDR(AFCFileRefOpen);
	GET_METHOD_PROC_ADDR(AFCFileRefRead);
	GET_METHOD_PROC_ADDR(AFCFileRefSeek);
	GET_METHOD_PROC_ADDR(AFCFileRefSetFileSize);
	GET_METHOD_PROC_ADDR(AFCFileRefTell);
	GET_METHOD_PROC_ADDR(AFCFileRefUnlock);
	GET_METHOD_PROC_ADDR(AFCFileRefWrite);
	GET_METHOD_PROC_ADDR(AFCFlushData);
	GET_METHOD_PROC_ADDR(AFCGetClientVersionString);
	GET_METHOD_PROC_ADDR(AFCKeyValueClose);
	GET_METHOD_PROC_ADDR(AFCKeyValueRead);
	GET_METHOD_PROC_ADDR(AFCLinkPath);
	GET_METHOD_PROC_ADDR(AFCOperationCopyPacketData);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetConnectionInfo);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetDeviceInfo);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetFileHash);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetFileHashWithRange);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetFileInfo);
	GET_METHOD_PROC_ADDR(AFCOperationCreateGetSizeOfPathContents);
	GET_METHOD_PROC_ADDR(AFCOperationCreateLinkPath);
	GET_METHOD_PROC_ADDR(AFCOperationCreateMakeDirectory);
	GET_METHOD_PROC_ADDR(AFCOperationCreateOpenFile);
	GET_METHOD_PROC_ADDR(AFCOperationCreatePacketHeaderDictionary);
	GET_METHOD_PROC_ADDR(AFCOperationCreateReadDirectory);
	GET_METHOD_PROC_ADDR(AFCOperationCreateRemovePath);
	GET_METHOD_PROC_ADDR(AFCOperationCreateRemovePathAndContents);
	GET_METHOD_PROC_ADDR(AFCOperationCreateRenamePath);
	GET_METHOD_PROC_ADDR(AFCOperationCreateSetConnectionOptions);
	GET_METHOD_PROC_ADDR(AFCOperationCreateSetModTime);
	GET_METHOD_PROC_ADDR(AFCOperationGetContext);
	GET_METHOD_PROC_ADDR(AFCOperationGetResultObject);
	GET_METHOD_PROC_ADDR(AFCOperationGetResultStatus);
	GET_METHOD_PROC_ADDR(AFCOperationGetState);
	GET_METHOD_PROC_ADDR(AFCOperationGetTypeID);
	GET_METHOD_PROC_ADDR(AFCOperationSetContext);
	GET_METHOD_PROC_ADDR(AFCReadData);
	GET_METHOD_PROC_ADDR(AFCReadPacket);
	GET_METHOD_PROC_ADDR(AFCReadPacketBody);
	GET_METHOD_PROC_ADDR(AFCReadPacketHeader);
	GET_METHOD_PROC_ADDR(AFCRemovePath);
	GET_METHOD_PROC_ADDR(AFCRenamePath);
	GET_METHOD_PROC_ADDR(AFCSendData);
	GET_METHOD_PROC_ADDR(AFCSendDataPacket);
	GET_METHOD_PROC_ADDR(AFCSendHeader);
	GET_METHOD_PROC_ADDR(AFCSendPacket);
	GET_METHOD_PROC_ADDR(AFCSendStatus);
	GET_METHOD_PROC_ADDR(AFCValidateHeader);
	GET_METHOD_PROC_ADDR(AMDCopyArrayOfDevicesMatchingQuery);
	GET_METHOD_PROC_ADDR(AMDCopyAuthenticationIdentityForDevice);
	GET_METHOD_PROC_ADDR(AMDCopyErrorText);
	GET_METHOD_PROC_ADDR(AMDCopySystemBonjourUniqueID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceCopyAuthInstallPreflightOptions);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceCopyBoardConfig);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetBoardID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetChipID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetECID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetLocationID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetProductID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetProductType);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetProductionMode);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetProgress);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetSecurityDomain);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetSecurityEpoch);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceGetTypeID);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceIsBootstrapOnly);
	GET_METHOD_PROC_ADDR(AMDFUModeDeviceRequestAbbreviatedSendSync);
	GET_METHOD_PROC_ADDR(AMDGetPairingRecordDirectoryPath);
	GET_METHOD_PROC_ADDR(AMDListenForNotifications);
	GET_METHOD_PROC_ADDR(AMDObserveNotification);
	GET_METHOD_PROC_ADDR(AMDPostNotification);
	GET_METHOD_PROC_ADDR(AMDSecureListenForNotifications);
	GET_METHOD_PROC_ADDR(AMDSecureObserveNotification);
	GET_METHOD_PROC_ADDR(AMDSecurePostNotification);
	GET_METHOD_PROC_ADDR(AMDSecureShutdownNotificationProxy);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionCreate);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionGetSecureIOContext);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionGetSocket);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionGetTypeID);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionInvalidate);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionReceive);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionReceiveMessage);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionSend);
	GET_METHOD_PROC_ADDR(AMDServiceConnectionSendMessage);
	GET_METHOD_PROC_ADDR(AMDSetLogLevel);
	GET_METHOD_PROC_ADDR(AMDShutdownNotificationProxy);
	GET_METHOD_PROC_ADDR(AMDeviceActivate);
	GET_METHOD_PROC_ADDR(AMDeviceArchiveApplication);
	GET_METHOD_PROC_ADDR(AMDeviceCheckCapabilitiesMatch);
	GET_METHOD_PROC_ADDR(AMDeviceCopyAuthInstallPreflightOptions);
	GET_METHOD_PROC_ADDR(AMDeviceCopyDeviceIdentifier);
	GET_METHOD_PROC_ADDR(AMDeviceCopyDeviceLocation);
	GET_METHOD_PROC_ADDR(AMDeviceCopyProvisioningProfiles);
	GET_METHOD_PROC_ADDR(AMDeviceCopyValue);
	GET_METHOD_PROC_ADDR(AMDeviceCopyValueWithError);
	GET_METHOD_PROC_ADDR(AMDeviceCreateHouseArrestService);
	GET_METHOD_PROC_ADDR(AMDeviceCreateWakeupToken);
	GET_METHOD_PROC_ADDR(AMDeviceDeactivate);
	GET_METHOD_PROC_ADDR(AMDeviceDisconnect);
	GET_METHOD_PROC_ADDR(AMDeviceEnterRecovery);
	GET_METHOD_PROC_ADDR(AMDeviceExtendedPairWithOptions);
	GET_METHOD_PROC_ADDR(AMDeviceGetConnectionID);
	GET_METHOD_PROC_ADDR(AMDeviceGetInterfaceSpeed);
	GET_METHOD_PROC_ADDR(AMDeviceGetTypeID);
	GET_METHOD_PROC_ADDR(AMDeviceGetUserInfo);
	GET_METHOD_PROC_ADDR(AMDeviceGetWirelessBuddyFlags);
	GET_METHOD_PROC_ADDR(AMDeviceInstallApplication);
	GET_METHOD_PROC_ADDR(AMDeviceInstallProvisioningProfile);
	GET_METHOD_PROC_ADDR(AMDeviceIsPaired);
	GET_METHOD_PROC_ADDR(AMDeviceIsValid);
	GET_METHOD_PROC_ADDR(AMDeviceLookupApplicationArchives);
	GET_METHOD_PROC_ADDR(AMDeviceLookupApplications);
	GET_METHOD_PROC_ADDR(AMDeviceNotificationUnsubscribe);
	GET_METHOD_PROC_ADDR(AMDevicePair);
	GET_METHOD_PROC_ADDR(AMDevicePairWithOptions);
	GET_METHOD_PROC_ADDR(AMDevicePowerAssertionCreate);
	GET_METHOD_PROC_ADDR(AMDevicePowerAssertionGetTypeID);
	GET_METHOD_PROC_ADDR(AMDevicePreflightOperationCreate);
	GET_METHOD_PROC_ADDR(AMDevicePreflightOperationGetRunLoopSource);
	GET_METHOD_PROC_ADDR(AMDevicePreflightOperationGetTypeID);
	GET_METHOD_PROC_ADDR(AMDevicePreflightOperationInvalidate);
	GET_METHOD_PROC_ADDR(AMDeviceRemoveApplicationArchive);
	GET_METHOD_PROC_ADDR(AMDeviceRemoveProvisioningProfile);
	GET_METHOD_PROC_ADDR(AMDeviceRemoveValue);
	GET_METHOD_PROC_ADDR(AMDeviceRequestAbbreviatedSendSync);
	GET_METHOD_PROC_ADDR(AMDeviceRestoreApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSecureArchiveApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSecureCheckCapabilitiesMatch);
	GET_METHOD_PROC_ADDR(AMDeviceSecureInstallApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSecureRemoveApplicationArchive);
	GET_METHOD_PROC_ADDR(AMDeviceSecureRestoreApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSecureStartService);
	GET_METHOD_PROC_ADDR(AMDeviceSecureTransferPath);
	GET_METHOD_PROC_ADDR(AMDeviceSecureUninstallApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSecureUpgradeApplication);
	GET_METHOD_PROC_ADDR(AMDeviceSetUserInfo);
	GET_METHOD_PROC_ADDR(AMDeviceSetValue);
	GET_METHOD_PROC_ADDR(AMDeviceSetWirelessBuddyFlags);
	GET_METHOD_PROC_ADDR(AMDeviceWakeupOperationCreateWithToken);
	GET_METHOD_PROC_ADDR(AMDeviceWakeupOperationGetTypeID);
	GET_METHOD_PROC_ADDR(AMDeviceWakeupOperationInvalidate);
	GET_METHOD_PROC_ADDR(AMDeviceWakeupOperationSchedule);
	GET_METHOD_PROC_ADDR(AMDeviceWakeupUsingToken);
	GET_METHOD_PROC_ADDR(AMRAuthInstallCopyLocalizedStringForServerError);
	GET_METHOD_PROC_ADDR(AMRAuthInstallCopyPreflightOptions);
	GET_METHOD_PROC_ADDR(AMRAuthInstallFinalize);
	GET_METHOD_PROC_ADDR(AMRAuthInstallPreflight);
	GET_METHOD_PROC_ADDR(AMRAuthInstallRegisterProxyCredentialsCallback);
	GET_METHOD_PROC_ADDR(AMRLog);
	GET_METHOD_PROC_ADDR(AMRLogv);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceCopyAuthInstallPreflightOptions);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceCopyBoardConfig);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceCopyEnvironmentVariableFromDevice);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceCopyIMEI);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceCopySerialNumber);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetBoardID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetChipID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetECID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetLocationID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetProductID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetProductType);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetProductionMode);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetProgress);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetSecurityDomain);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetSecurityEpoch);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceGetTypeID);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceIsBootstrapOnly);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceReboot);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceRequestAbbreviatedSendSync);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceSendBlindCommandToDevice);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceSendCommandToDevice);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceSendFileToDevice);
	GET_METHOD_PROC_ADDR(AMRecoveryModeDeviceSetAutoBoot);
	GET_METHOD_PROC_ADDR(AMRecoveryModeGetSoftwareBuildVersion);
	GET_METHOD_PROC_ADDR(AMRestorableBuildCopyRestoreBundleURL);
	GET_METHOD_PROC_ADDR(AMRestorableBuildCopySupportedBoardConfigs);
	GET_METHOD_PROC_ADDR(AMRestorableBuildCopySupportedVariants);
	GET_METHOD_PROC_ADDR(AMRestorableBuildCreate);
	GET_METHOD_PROC_ADDR(AMRestorableCommitStashBag);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyAMDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyAuthInstallPreflightOptions);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyBoardConfig);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyDFUModeDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyDefaultRestoreOptions);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyRecoveryModeDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyRestoreModeDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopyRestoreOptionsFromDocument);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopySerialDevicePath);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCopySerialNumber);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceCreateFromAMDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceEnableExtraDFUDevices);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetDFUModeDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetECID);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetFusingInfo);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetLocationID);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetProductID);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetProductType);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetRecoveryModeDevice);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceGetState);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceRegisterForNotifications);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceRestore);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceSendBlindCommand);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceSendCommand);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceSendFile);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceSetLogFileURL);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceSetProxyCredentialsCallback);
	GET_METHOD_PROC_ADDR(AMRestorableDeviceUnregisterForNotifications);
	GET_METHOD_PROC_ADDR(AMRestorableEnableLogStreaming);
	GET_METHOD_PROC_ADDR(AMRestorableGetIdentifyingErrorCode);
	GET_METHOD_PROC_ADDR(AMRestorableLogToFile);
	GET_METHOD_PROC_ADDR(AMRestorablePersonalizeCopyManifestTag);
	GET_METHOD_PROC_ADDR(AMRestorablePersonalizeSendFile);
	GET_METHOD_PROC_ADDR(AMRestorableSetGlobalLocationIDFilter);
	GET_METHOD_PROC_ADDR(AMRestorableSetGlobalLogFileURL);
	GET_METHOD_PROC_ADDR(AMRestorableSetLogLevel);
	GET_METHOD_PROC_ADDR(AMRestoreCreateBootArgsByAddingArg);
	GET_METHOD_PROC_ADDR(AMRestoreCreateBootArgsByRemovingArg);
	GET_METHOD_PROC_ADDR(AMRestoreCreateDefaultOptions);
	GET_METHOD_PROC_ADDR(AMRestoreCreatePathsForBundle);
	GET_METHOD_PROC_ADDR(AMRestoreDisableFileLogging);
	GET_METHOD_PROC_ADDR(AMRestoreEnableExtraDFUDevices);
	GET_METHOD_PROC_ADDR(AMRestoreEnableFileLogging);
	GET_METHOD_PROC_ADDR(AMRestoreGetSupportedPayloadVersion);
	GET_METHOD_PROC_ADDR(AMRestoreGetTransformedDFUType);
	GET_METHOD_PROC_ADDR(AMRestoreGetTransformedFirmwareTypeValue);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCopyBoardConfig);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCopyEcid);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCopyIMEI);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCopyRestoreLog);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCopySerialNumber);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceCreate);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceGetDeviceID);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceGetLocationID);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceGetProgress);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceGetTypeID);
	GET_METHOD_PROC_ADDR(AMRestoreModeDeviceReboot);
	GET_METHOD_PROC_ADDR(AMRestoreModeGetLastFailureLog);
	GET_METHOD_PROC_ADDR(AMRestorePerformDFURestore);
	GET_METHOD_PROC_ADDR(AMRestorePerformRecoveryModeRestore);
	GET_METHOD_PROC_ADDR(AMRestorePerformRestoreModeRestore);
	GET_METHOD_PROC_ADDR(AMRestorePerformRestoreModeRestoreWithError);
	GET_METHOD_PROC_ADDR(AMRestoreRegisterForDeviceNotifications);
	GET_METHOD_PROC_ADDR(AMRestoreSetLogLevel);
	GET_METHOD_PROC_ADDR(AMRestoreUnregisterForDeviceNotifications);
	GET_METHOD_PROC_ADDR(AMSArchiveBackup);
	GET_METHOD_PROC_ADDR(AMSBackupWithOptions);
	GET_METHOD_PROC_ADDR(AMSBeginSync);
	GET_METHOD_PROC_ADDR(AMSBeginSyncForDataClasses);
	GET_METHOD_PROC_ADDR(AMSCancelBackupRestore);
	GET_METHOD_PROC_ADDR(AMSCancelCrashReportCopy);
	GET_METHOD_PROC_ADDR(AMSCancelSync);
	GET_METHOD_PROC_ADDR(AMSCancelSyncDiagnostics);
	GET_METHOD_PROC_ADDR(AMSChangeBackupPassword);
	GET_METHOD_PROC_ADDR(AMSCleanup);
	GET_METHOD_PROC_ADDR(AMSClearDataClasses);
	GET_METHOD_PROC_ADDR(AMSConnectToCrashReportCopyTarget);
	GET_METHOD_PROC_ADDR(AMSCopyApplicationListFromBackup);
	GET_METHOD_PROC_ADDR(AMSCopyCrashReportPath);
	GET_METHOD_PROC_ADDR(AMSCopyCrashReportsFromTarget);
	GET_METHOD_PROC_ADDR(AMSCopySourcesForRestoreCompatibleWith);
	GET_METHOD_PROC_ADDR(AMSDisconnectFromCrashReportCopyTarget);
	GET_METHOD_PROC_ADDR(AMSEnableCloudBackup);
	GET_METHOD_PROC_ADDR(AMSEnableSyncServices);
	GET_METHOD_PROC_ADDR(AMSGetAOSUsername);
	GET_METHOD_PROC_ADDR(AMSGetApplicationProviderInfo);
	GET_METHOD_PROC_ADDR(AMSGetBackupInfo);
	GET_METHOD_PROC_ADDR(AMSGetBackupPasswordFromKeychainForTarget);
	GET_METHOD_PROC_ADDR(AMSGetCalendarDayLimit);
	GET_METHOD_PROC_ADDR(AMSGetClientIdentifierAndDisplayNameForTarget);
	GET_METHOD_PROC_ADDR(AMSGetCollectionsForDataClassName);
	GET_METHOD_PROC_ADDR(AMSGetCrashReportCopyPreferencesForTarget);
	GET_METHOD_PROC_ADDR(AMSGetDataChangeAlertInfo);
	GET_METHOD_PROC_ADDR(AMSGetDataClassInfoForTarget);
	GET_METHOD_PROC_ADDR(AMSGetDefaultOutlookCalendarMapping);
	GET_METHOD_PROC_ADDR(AMSGetLastSyncDateForDataClass);
	GET_METHOD_PROC_ADDR(AMSGetNewRecordCalendarName);
	GET_METHOD_PROC_ADDR(AMSGetNewRecordGroupName);
	GET_METHOD_PROC_ADDR(AMSGetNumberOfCrashReportsToCopy);
	GET_METHOD_PROC_ADDR(AMSGetNumberOfCrashReportsToSubmit);
	GET_METHOD_PROC_ADDR(AMSGetSourcesForRestore);
	GET_METHOD_PROC_ADDR(AMSGetSupportedDataClassNames);
	GET_METHOD_PROC_ADDR(AMSInitialize);
	GET_METHOD_PROC_ADDR(AMSIsSyncServicesEnabled);
	GET_METHOD_PROC_ADDR(AMSRefreshCollectionsForDataClassName);
	GET_METHOD_PROC_ADDR(AMSRegisterCallbacks);
	GET_METHOD_PROC_ADDR(AMSRegisterClientWithTargetIdentifierAndDisplayName);
	GET_METHOD_PROC_ADDR(AMSResetSyncData);
	GET_METHOD_PROC_ADDR(AMSRestoreWithApplications);
	GET_METHOD_PROC_ADDR(AMSRunSyncDiagnostics);
	GET_METHOD_PROC_ADDR(AMSSetBackupPasswordInKeychain);
	GET_METHOD_PROC_ADDR(AMSSetCalendarDayLimit);
	GET_METHOD_PROC_ADDR(AMSSetCrashReportCopyPreferencesForTarget);
	GET_METHOD_PROC_ADDR(AMSSetDataChangeAlertInfo);
	GET_METHOD_PROC_ADDR(AMSSetDataClassInfoForTarget);
	GET_METHOD_PROC_ADDR(AMSSetDefaultOutlookCalendarMapping);
	GET_METHOD_PROC_ADDR(AMSSetDesignatedProviderForDataClassName);
	GET_METHOD_PROC_ADDR(AMSSetFilteredCollectionNamesForDataClassName);
	GET_METHOD_PROC_ADDR(AMSSetNewRecordCalendarName);
	GET_METHOD_PROC_ADDR(AMSSetNewRecordGroupName);
	GET_METHOD_PROC_ADDR(AMSSubmitCrashReportsFromTarget);
	GET_METHOD_PROC_ADDR(AMSSubmitRestoreLogFromPath);
	GET_METHOD_PROC_ADDR(AMSUnregisterTarget);
	GET_METHOD_PROC_ADDR(ASRServerHandleConnection);
	GET_METHOD_PROC_ADDR(RCGetSystemPartitionExtrasSizeForDevice);
	GET_METHOD_PROC_ADDR(USBMuxConnectByPort);
	GET_METHOD_PROC_ADDR(USBMuxListenerClose);
	GET_METHOD_PROC_ADDR(USBMuxListenerCreate);
	GET_METHOD_PROC_ADDR(USBMuxListenerSetDebug);
	GET_METHOD_PROC_ADDR(kAFCErrorCodeKey);
	GET_METHOD_PROC_ADDR(kAFCErrorDebugDescriptionKey);
	GET_METHOD_PROC_ADDR(kAFCErrorDescriptionKey);
	GET_METHOD_PROC_ADDR(kAFCErrorDomain);
	GET_METHOD_PROC_ADDR(kAFCErrorDomainKey);
	GET_METHOD_PROC_ADDR(kAFCErrorExtendedInfoKey);
	GET_METHOD_PROC_ADDR(kAFCErrorFileLineKey);
	GET_METHOD_PROC_ADDR(kAFCErrorFileNameKey);
	GET_METHOD_PROC_ADDR(kAFCErrorLocalizedDescriptionKey);
	GET_METHOD_PROC_ADDR(kAFCErrorLocalizedFailureReasonKey);
	GET_METHOD_PROC_ADDR(kAFCErrorLocalizedRecoverySuggestionKey);
	GET_METHOD_PROC_ADDR(kAFCErrorUnderlyingErrorKey);
	GET_METHOD_PROC_ADDR(kAFCErrorVersionKey);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeyHeaderLength);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeyPacketData);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeyPacketID);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeyPacketLength);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeyPacketType);
	GET_METHOD_PROC_ADDR(kAFCHeaderKeySignature);
	GET_METHOD_PROC_ADDR(kAMRestorableInvalidClientID);

	
	MobileDeviceDllHandle = dllHandle;

	return 0;
}