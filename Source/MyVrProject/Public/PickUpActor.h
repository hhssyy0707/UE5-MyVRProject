// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UCLASS()
class MYVRPROJECT_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpActor();

	UPROPERTY(EditAnywhere, Category="MySettings|Component")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Component")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	FVector locationOffset = FVector(0, 0, 10);

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	float throwPower = 500;

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	float rotPower = 100;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Grabbed(class USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules);
	void Released(FVector deltaPosition, FQuat deltaRotaion);
};
