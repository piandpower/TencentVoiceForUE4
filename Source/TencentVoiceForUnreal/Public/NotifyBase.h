// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "CoreUObject.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "VoiceClient.h"
#include "TencentVoiceForUnreal.h"
#include "NotifyBase.generated.h"

using namespace gcloud_voice;

DECLARE_DYNAMIC_DELEGATE(FEventCallback);

/**
 * 
 */
UENUM()
enum class EFunctionName : uint8
{
	EOnJoinRoom				UMETA(DisplayName="OnJoinRoom"),
	EOnStatusUpdate			UMETA(DisplayName="OnStatusUpdate"),
	EOnQuitRoom				UMETA(DisplayName="OnQuitRoom"),
	EOnMemberVoice			UMETA(DisplayName="OnMemberVoice"),
	EOnUploadFile			UMETA(DisplayName="OnUploadFile"),
	EOnDownloadFile			UMETA(DisplayName="OnDownloadFile"),
	EOnPlayRecordedFile		UMETA(DisplayName="OnPlayRecordedFile"),
	EOnApplyMessageKey		UMETA(DisplayName="OnApplyMessageKey"),
	EOnSpeechToText			UMETA(DisplayName="OnSpeechToText"),
	EOnRecording			UMETA(DisplayName="OnRecording"),
	EOnStreamSpeechToText	UMETA(DisplayName="OnStreamSpeechToText"),
	EOnRoleChanged			UMETA(DisplayName="OnRoleChanged")
};

UCLASS(BlueprintType)
class TENCENTVOICEFORUNREAL_API UNotifyBase : public UObject, public IGCloudVoiceNotify
{
	GENERATED_BODY()

public:
	UNotifyBase(const FObjectInitializer& ObjectInitializer);
	virtual ~UNotifyBase();

public:
	virtual void OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID) override;
	virtual void OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID) override;
	virtual void OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName) override;
	virtual void OnMemberVoice(const char *roomName, unsigned int member, int status) override;
	virtual void OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath) override;
	virtual void OnApplyMessageKey(GCloudVoiceCompleteCode code) override;
	virtual void OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result) override;
	virtual void OnRecording(const unsigned char* pAudioData, unsigned int nDataLength) override;
	virtual void OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath) override;
	virtual void OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role) override;

public:
	/**
	 * Get the notify instance (singleton object)
	 *
	 * @return UNotifyBase pointer
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		static UNotifyBase* GetNotifyInstance();

	/**
	 * Set event for specify function name, when the callback function was called and successed, this event will be called
	 *
	 * @param FunctionName The function that you want to set event
	 * @param Delegate The event you want to set
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void SetEventForFunctionName(EFunctionName FunctionName, UPARAM(DisplayName = "Event") FEventCallback Delegate);

	/**
	 * Remove event for function name
	 *
	 * @param FunctionName The function thar you want to remove event
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		
		void RemoveEventForFunctionName(EFunctionName FunctionName);

	//UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
	//	// New a notify instance (singleton object)
	//	static UNotifyBase* NewNotifyInstance(TSubclassOf<UNotifyBase> NotifyClass);

protected:
	// The UNotifyBase instance handle (singleton object)
	static UNotifyBase* NotifyInstance;
	// Callback event map
	TMap<EFunctionName, FEventCallback> CallbackMap;
	// The VoiceClient instance handle
	class UVoiceClient* VoiceClient;
};
