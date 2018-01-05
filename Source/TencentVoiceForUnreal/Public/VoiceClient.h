// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "VoiceClient.generated.h"

class UNotifyBase;

/**
 * 
 */

UENUM()
enum class EVoiceMode : uint8
{
	RealTime = 0, // realtime mode for TeamRoom or NationalRoom
	Messages,     // voice message mode
	Translation,  // speach to text mode
	RSTT, // real-time speach to text mode
	HIGHQUALITY = 4, //high quality realtime voice, will cost more network traffic
};

UCLASS()
class TENCENTVOICEFORUNREAL_API UVoiceClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UVoiceClient(const FObjectInitializer& ObjectInitializer);
	~UVoiceClient();

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

public:
	// Set thie VoiceClient room status
	void SetRoomStatus(bool RoomStatus);

	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get or New a voice client instance(if not exist), (singleton object)
		static UVoiceClient* GetVoiceClient();

	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get this VoiceClient room status
		bool GetRoomStatus();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set VoiceEngine AppInfo. successed return true, otherwise return false
		bool SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Initialise engine
		void InitVoiceEngine();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set engine voice mode
		void SetMode(EVoiceMode VoiceMode);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set engine server info
		void SetServerInfo(const FString& ServerAddr);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application pause
		void OnPause();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application resume
		void OnResume();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set your Notify or Callback, successed return true, otherwise return false.
		bool SetNotify(UNotifyBase* NotifyInstance);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Join team room. if successful, will callback notify OnJoinRoom function
		void JoinTeamRoom(const FString& RoomName, int32 msTimeout);

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
		// Enable a voice client join in multi rooms, ture for open and false for close, if success return true, failed return false.
		bool EnableMultiRoom(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set voice client Mic volume
		void SetMicVolume(int vol);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set voice client Speaker volume
		void SetSpeakerVolume(int vol);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Quit current joined room, if successful, will callback notify OnQuitRoom function
		void QuitCurrentJoinedRoom(int32 msTimeout);

private:
	// The UVoiceClient instance handle (singleton object)
	static UVoiceClient* VoiceClient;
	// The TencentVoiceEngine handle
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
	// Mark this VoiceClient whether in voice room (default value is false)
	bool bRoomStatus;
	// Current joined room name
	FString CurrentRoomName;
};
