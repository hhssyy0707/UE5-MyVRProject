// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyboardActor.generated.h"

UCLASS()
class MYVRPROJECT_API AKeyboardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKeyboardActor();
	
	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Resources")
	class USoundBase* keySound;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	class UMaterialInstanceDynamic* keyMat;

	UFUNCTION()
	void OnHitKey(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetKeyColor();
};
