// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRHandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UVRHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

	public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float PoseAlphaGrasp_cpp = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float PoseAlphaIndexCurl_cpp = 0;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float PoseAlphaPoint_cpp = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float PoseAlphaThumbUp_cpp = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float CurrentPoseAlphaThumbUp_cpp = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	float CurrentPoseAlphaPoint_cpp = 0;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = MySettings)
	bool bMirror_cpp = false;
};
