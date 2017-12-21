// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "TeamRoomNotify.generated.h"

using namespace gcloud_voice;

/**
 * 
 */
UCLASS()
class TENCENTVOICEFORUNREAL_API UTeamRoomNotify : public UObject, public IGCloudVoiceNotify
{
	GENERATED_BODY()

public:
	UTeamRoomNotify(const FObjectInitializer& ObjectInitializer);
	virtual ~UTeamRoomNotify();

public:
	virtual void OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID) override;
	virtual void OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID) override;
	virtual void OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName) override;
	virtual void OnMemberVoice(const unsigned int *members, int count) override;
	virtual void OnMemberVoice(const char *roomName, unsigned int member, int status) override;
	virtual void OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath) override;
	virtual void OnApplyMessageKey(GCloudVoiceCompleteCode code) override;
	virtual void OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result) override;
	virtual void OnRecording(const unsigned char* pAudioData, unsigned int nDataLength) override;
	virtual void OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath) override;
	virtual void OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role) override;
};
