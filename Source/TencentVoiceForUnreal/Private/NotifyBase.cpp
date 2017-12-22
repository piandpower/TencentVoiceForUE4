// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyBase.h"

UNotifyBase::UNotifyBase(const FObjectInitializer& ObjectInitializer) : UObject(ObjectInitializer)
{

}

UNotifyBase::~UNotifyBase()
{

}

void UNotifyBase::OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnJoinRoom"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnJoinRoom);
	if (TCallback)
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("OnJoinRoom Callback notequal nullptr!"));
		TCallback->ExecuteIfBound();
	}
	else
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("OnJoinRoom Callback equal nullptr!"));
	}
}

void UNotifyBase::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnStatusUpdate"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnStatusUpdate);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnQuitRoom"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnQuitRoom);
	if (nullptr != TCallback)
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("OnJoinRoom Callback notequal nullptr!"));
		TCallback->ExecuteIfBound();
	}
}

// This function deprecate from GVoice 1.1.14
//void UNotifyBase::OnMemberVoice(const unsigned int *members, int count)
//{
//	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnMemberVoice"));
//}

void UNotifyBase::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnMemberVoice"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnMemberVoice);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnUploadFile"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnUploadFile);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnDownloadFile"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnDownloadFile);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnPlayRecordedFile"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnPlayRecordedFile);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnApplyMessageKey"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnApplyMessageKey);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnSpeechToText"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnSpeechToText);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnRecording"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnRecording);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnStreamSpeechToText"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnStreamSpeechToText);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnRoleChanged"));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnRoleChanged);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::GetNotifyDefaultObject(TSubclassOf<UNotifyBase> NotifyClass, UNotifyBase *& OutObject)
{
	OutObject = Cast<UNotifyBase>(NotifyClass->GetDefaultObject(true));

}

//UNotifyBase * UNotifyBase::GetNotifyInstance(const UObject * Outer, TSubclassOf<UObject> NotifyClass)
//{
//	return NewObject<UNotifyBase>(&Outer, NotifyClass->GetClass());
//}

//UNotifyBase * UNotifyBase::GetNotifyInstance(const UObject* Outer, TSubclassOf<UNotifyBase> NotifyClass)
//{
//	//return NewObject<UNotifyBase>(Outer, NotifyClass->GetClass());
//	FString Temp;
//	NotifyClass->GetName(Temp);
//	UE_LOG(LogTemp, Error, TEXT("Class name is %s"), *Temp);
//	NotifyClass->Get();
//	return nullptr;
//}

void UNotifyBase::SetEventForFunctionName(FuncName FunctionName, FEventCallback Delegate)
{
	if (mapCallback.Find(FunctionName) == NULL)
	{
		mapCallback.Add(FunctionName, Delegate);
		UE_LOG(TencentVoicePlugin, Display, TEXT("%d delegate added!"), static_cast<int32>(FunctionName));
	}
}

void UNotifyBase::RemoveEventForFunctionName(FuncName FunctionName)
{
	mapCallback.Remove(FunctionName);
	UE_LOG(TencentVoicePlugin, Display, TEXT("Remove event by %d!"), static_cast<int32>(FunctionName));
}