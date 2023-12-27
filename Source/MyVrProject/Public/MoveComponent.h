// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category="MySettings")
	float lineSpeed = 500;

	UPROPERTY(EditAnywhere, Category="MySettings")
	float teleportDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category="MySettings")
	TSubclassOf<class ATeleportRingActor> teleportRingBP;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs);


private:
	class AVR_Player* player;
	FVector targetLocation;
	class ATeleportRingActor* teleportRingInst;

	void ShowLine(const FInputActionValue& value);
	void DrawTrajectory(FVector startLoc, FVector dir, float speed, int32 segment, float interval);
	void DrawTrajectoryBezier(FVector startLoc, FVector dir, int32 segment);
	void Teleport();
};
