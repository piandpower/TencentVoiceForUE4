// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
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
		// Get or New a voice client instance(if not exist),singleton object
		static UVoiceClient* GetVoiceClient();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set VoiceEngine AppInfo.successed return true,otherwise return false
		bool SetAppInfo(const FString& appID, const FString& appKey, int32 RoleID);

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Initialise engine
		void InitEngine();

private:
	static UVoiceClient* VoiceClient;
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
};
