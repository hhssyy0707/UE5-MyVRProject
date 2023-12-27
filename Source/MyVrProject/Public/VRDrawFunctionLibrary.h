// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VRDrawFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UVRDrawFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TArray<FVector> CalculateBezierCurve(FVector p0, FVector p1, FVector p2, int32 segment);
	
};
