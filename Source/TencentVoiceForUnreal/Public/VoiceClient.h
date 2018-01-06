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

	/** 
	 * Set thie voice room state
	 *
	 * @param RoomStatus Mark this VoiceClient whether in voice room, true for in room and false for out room.
	 */
	void SetRoomStatus(bool RoomStatus);

	/**
	 * Add a room name to JoinedRoomName
	 *
	 * @param RoomName The room name need to add
	 */
	void AddJoinedRoomName(const FString& RoomName);

	/**
	 * Remove a room name from JoinedRoomName
	 *
	 * @Param RoomName The room name need to remove
	 */
	void RemoveJoinedRoomName(const FString& RoomName);

	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get or New a voice client instance(if not exist), (singleton object)
		static UVoiceClient* GetVoiceClient();

	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		/** 
		 * Get the specify voice room state
		 *
		 * @param RoomName The specify room name
		 * @return The specify room state
		 */
		bool GetRoomStatus();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Set VoiceEngine AppInfo.
		 *
		 * @param appID your game ID from gcloud.qq.com
		 * @param appKey your game key from gcloud.qq.com
		 * @param openID player's openID from QQ or Wechat. or a unit role ID.
		 * @param return successed return true, otherwise return false
		 */
		bool SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Init the voice engine.
		void InitVoiceEngine();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Set the mode for engine
		 *
		 * @param VoiceMoede Mode to set
		 */
		void SetMode(EVoiceMode VoiceMode);

	//UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set engine server info
		//void SetServerInfo(const FString& ServerAddr);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application pause
		void OnPause();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// On application resume
		void OnResume();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Set the Notify to engine, successed return true, otherwise return false.
		 *
		 * @param NotifyInstance The notify
		 */
		bool SetNotify(UNotifyBase* NotifyInstance);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Join team room. if successful, will callback notify OnJoinRoom function
		 *
		 * @param RoomName the room to join
         * @param msTimeout time for join, it is micro second. value range[5000, 60000]
		 */
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
		/**
		 * Enable a voice client join in multi rooms.
		 *
		 * @param bEnable true for open and false for close.
		 * @return if success return true, failed return false.
		 */
		bool EnableMultiRoom(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Set voice client Mic volume
		 *
		 * @param vol The SDK document does not mention this parameter. 
		 */
		void SetMicVolume(int vol);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Set voice client Speaker volume.
		 *
		 * @param vol Android & IOS, value range is 0-800, 100 means original voice volume, 50 means only 1/2 original voice volume,  200 means double original voice volume. Windows value range is 0x0 - 0xFFFF, suggested value bigger than 0xff00, then you can hear you speaker sound
		 */ 
		void SetSpeakerVolume(int vol);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		/**
		 * Quit the specify voice room, if successful, will callback notify OnQuitRoom function
		 *
		 * @param RoomName The voice room want to quit
		 * @param msTimeout time for quit, it is micro second. value range[5000, 60000]
		 */
		void QuitRoom(const FString& RoomName, int32 msTimeout);

private:
	// The UVoiceClient instance handle (singleton object)
	static UVoiceClient* VoiceClient;
	// The TencentVoiceEngine handle
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
	// Mark this VoiceClient whether tickable (default value is false)
	bool bRoomStatus;
	// This array storage the voice client has joined room name
	TArray<FString> JoinedRoomName;
};
