// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierCurveActor.generated.h"

UCLASS()
class MYVRPROJECT_API ABezierCurveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABezierCurveActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=MySettings)
	class USceneComponent* p0;

	UPROPERTY(EditAnywhere, Category=MySettings)
	class USceneComponent* p1;

	UPROPERTY(EditAnywhere, Category=MySettings)
	class USceneComponent* p2;

	UPROPERTY(EditAnywhere, Category=MySettings, meta = (ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f))
	float t = 0;

private:
	void DrawBezierCurve(FVector loc0, FVector loc1, FVector loc2);

};
