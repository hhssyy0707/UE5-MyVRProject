// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRBodyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UVRBodyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector LeftHandLocation;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator LeftHandRotation;


	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector RightHandLocation;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator RightHandRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector HeadLocation;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator HeadRotation;

};
