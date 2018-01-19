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

UENUM(BlueprintType)
enum class EVoiceMemberRole : uint8
{
	/* member who can open microphone and say */
	Anchor = 1,
	/* member who can only hear anchor's voice */
	Audience,
};

UENUM(BlueprintType)
enum class EVoiceMode : uint8
{
	/* realtime mode for TeamRoom or NationalRoom */
	RealTime = 0,
	/* voice message mode */
	Messages,
	/* speach to text mode */
	Translation,
	/* real-time speach to text mode */
	RSTT,
	/* high quality realtime voice, will cost more network traffic */
	HIGHQUALITY = 4,
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

	/**
	 * Get or New a voice client instance(if not exist), singleton object.
	 *
	 * @return UVoiceClient pointer
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		static UVoiceClient* GetVoiceClient();

	/**
	 * Get this voice client status
	 *
	 * @return This voice client whether in voice room
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		bool GetRoomStatus() const;

	/**
	 * Set VoiceEngine AppInfo.
	 *
	 * @param appID your game ID from gcloud.qq.com
	 * @param appKey your game key from gcloud.qq.com
	 * @param openID player's openID from QQ or Wechat. or a unit role ID.
	 * @return successed return true, otherwise return false
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		bool SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	/**
	 * Init the voice engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void InitVoiceEngine();

	/**
	 * Set the mode for engine
	 *
	 * @param VoiceMoede Mode to set
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void SetMode(EVoiceMode VoiceMode);

	/**
	 * Set the server address, just used for foreign game,such as Korea, Europe...
	 * @param ServerAddr url of server
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void SetServerInfo(const FString& ServerAddr);

	/**
	 * On application pause
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void OnPause();

	/**
	 * On application resume
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void OnResume();

	/**
	 * Set the Notify to engine.
	 *
	 * @param NotifyInstance The notify pointer
	 * @return successed return true, otherwise return false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		bool SetNotify(UNotifyBase* NotifyInstance);

	/**
	 * Join team room. if successful, will callback notify OnJoinRoom function
	 *
	 * @param RoomName the voice room name that you want to join
	 * @param msTimeout time for join, it is micro second. value range[5000, 60000]
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void JoinTeamRoom(const FString& RoomName, int32 msTimeout);

	/**
	 * Join national room. if successful, will callback notify OnJoinRoom function
	 *
	 * @param RoomName the voice room name that you want to join
	 * @param MemberRole The role of a member, the audience can only listen to the voice and can not send voice, and the Anchor can both send and listen to the voice.
	 * @param msTimeout time for join, it is micro second. value range[5000, 60000]
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void JoinNationalRoom(const FString& RoomName, EVoiceMemberRole MemberRole, int32 msTimeout);

	/**
	 * Open Microphone
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void OpenMic();

	/**
	 * Close Microphone
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void CloseMic();

	/**
	 * Open speaker
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void OpenSpeaker();

	/**
	 * Close speaker
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void CloseSpeaker();

	/**
	 * Enable a voice client join in multi rooms.
	 *
	 * @param bEnable true for open and false for close.
	 * @return if success return true, failed return false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		bool EnableMultiRoom(bool bEnable);

	/**
	 * Set voice client Mic volume
	 *
	 * @param vol The SDK document does not mention this parameter.
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void SetMicVolume(int vol);

	/**
	 * Set voice client Speaker volume.
	 *
	 * @param vol Android & IOS, value range is 0-800, 100 means original voice volume, 50 means only 1/2 original voice volume,  200 means double original voice volume. Windows value range is 0x0 - 0xFFFF, suggested value bigger than 0xff00, then you can hear you speaker sound
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void SetSpeakerVolume(int vol);

	/**
	 * Quit the specify voice room(Do not distinguish team room or National room), if successful, will callback notify OnQuitRoom function
	 *
	 * @param RoomName The voice room want to quit
	 * @param msTimeout time for quit, it is micro second. value range[5000, 60000]
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void QuitRoom(const FString& RoomName, int32 msTimeout);

	/**
	 * Quit the voice client all joined voice room
	 *
	 * @param msTimeout Time for quit, it is micro second. value range[5000, 60000]
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		void QuitAllRoom(int32 msTimeout);

private:
	// The UVoiceClient instance handle (singleton object)
	static UVoiceClient* VoiceClient;
	// The TencentVoiceEngine handle
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
	// Markup this VoiceClient whether joined voice room and tickable (default value is false)
	bool bRoomStatus;
	// This array storage the voice client has joined room name
	TArray<FString> JoinedRoomName;
};
