// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "TeamRoomNotify.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "VoiceClient.generated.h"

/**
 * 
 */
UCLASS()
class TENCENTVOICEFORUNREAL_API UVoiceClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UVoiceClient();
	~UVoiceClient();

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

public:
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get or New a voice client instance(if not exist), singleton object
		static UVoiceClient* GetVoiceClient();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set VoiceEngine AppInfo. successed return true, otherwise return false
		bool SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Initialise engine
		void InitVoiceEngine();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application pause
		void OnPause();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application resume
		void OnResume();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set your Notify or Callback, successed return true, otherwise return false
		bool SetNotify(UObject* NotifyToUse);

	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get current Notify
		UObject* GetNotify();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Join team room, successed return true, otherwise return false
		bool JoinTeamRoom(const FString& RoomName, int32 msTimeout);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Open Microphone
		void OpenMic();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Close Microphone
		void CloseMic();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Open speaker
		void OpenSpeaker();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Close speaker
		void CloseSpeaker();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Quit room, successed return true, otherwise return false
		bool QuitRoom(const FString& RoomName, int32 msTimeout);

private:
	// The UVoiceClient instance handle(static)
	static UVoiceClient* VoiceClient;
	// The TencentVoiceEngine handle
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
	// The current Notify or Callback handle
	class UObject* CurrentNotify;
};
