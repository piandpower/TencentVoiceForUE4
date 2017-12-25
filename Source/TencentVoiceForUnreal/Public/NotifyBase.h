// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "TencentVoiceForUnreal.h"
#include "NotifyBase.generated.h"

using namespace gcloud_voice;

DECLARE_DYNAMIC_DELEGATE(FEventCallback);

/**
 * 
 */
UENUM()
enum class FuncName : uint8
{
	_OnJoinRoom = 0,
	_OnStatusUpdate,
	_OnQuitRoom,
	_OnMemberVoice,
	_OnUploadFile,
	_OnDownloadFile,
	_OnPlayRecordedFile,
	_OnApplyMessageKey,
	_OnSpeechToText,
	_OnRecording,
	_OnStreamSpeechToText,
	_OnRoleChanged
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
	// This function deprecate from GVoice 1.1.14
	//virtual void OnMemberVoice(const unsigned int *members, int count) override;
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
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get your notify or callback instance. (This function always returns NewObject!)
		static UNotifyBase* GetNotifyInstance(TSubclassOf<UNotifyBase> NotifyClass);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set event for function name, when the callback function was called, this event will be called
		void SetEventForFunctionName(FuncName FunctionName, UPARAM(DisplayName = "Event") FEventCallback Delegate);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Remove event for function name
		void RemoveEventForFunctionName(FuncName FunctionName);

protected:
	TMap<FuncName, FEventCallback> mapCallback;
};
