// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "PickUpActor.h"
#include "MotionControllerComponent.h"


UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

}


void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentObject != nullptr)
	{
		deltaLoc = player->rightController->GetComponentLocation() - prevLoc;
		prevLoc = player->rightController->GetComponentLocation();

		//deltaQuat = player->rightController->GetComponentQuat() * prevQuat.Inverse();
		deltaQuat = player->rightController->GetComponentQuat() - prevQuat;
		prevQuat = player->rightController->GetComponentQuat();
	}
}

void UGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
}

void UGrabComponent::GrabObject()
{
	//player->rightLog->SetText(FText::FromString(FString("Try Grabbed!")));

	if (currentObject != nullptr) return;

	UWorld* world = GetWorld();

#pragma region 1. 라인 트레이스를 이용할 경우

	/*if (world != nullptr)
	{
		FHitResult hitInfo;
		FVector startLoc = player->rightHand->GetComponentLocation();
		FVector endLoc = startLoc + player->rightHand->GetRightVector() * 30.0f;

		if (world->LineTraceSingleByProfile(hitInfo, startLoc, endLoc, FName("PickUpPreset")))
		{
			currentObject = Cast<APickUpActor>(hitInfo.GetActor());

			if (currentObject != nullptr)
			{
				currentObject->Grabbed(player->rightHand, EAttachmentRule::SnapToTarget);
			}
		}
	}*/
#pragma endregion

	// 2. 스피어 트레이스를 이용할 경우

	// 3. 오버랩 스피어를 이용할 경우
	TArray<FOverlapResult> hitInfos;

	if (world->OverlapMultiByProfile(hitInfos, player->rightHand->GetComponentLocation(), player->rightHand->GetComponentQuat(), FName("PickUpPreset"), FCollisionShape::MakeSphere(25.0f)))
	{
		FString objects;
		float minDistance = 25.0f;
		int32 idx = 0;

		//for (const FOverlapResult& obj : hitInfos)
		for (int32 i = 0; i < hitInfos.Num(); i++)
		{
			if (hitInfos[i].GetActor()->IsA<APickUpActor>())
			{
				//objects.Append(obj.GetActor()->GetActorNameOrLabel() + "\r\n");
				float dist = FVector::Distance(player->rightHand->GetComponentLocation(), hitInfos[i].GetActor()->GetActorLocation());
				if (dist < minDistance)
				{
					minDistance = dist;
					idx = i;
				}
			}
		}

		currentObject = Cast<APickUpActor>(hitInfos[idx].GetActor());
		if (currentObject != nullptr)
		{
			currentObject->Grabbed(player->rightHand, EAttachmentRule::SnapToTarget);
			prevLoc = player->rightController->GetComponentLocation();
			player->rightLog->SetText(FText::FromString(objects));
		}
	}
	else
	{
		player->rightLog->SetText(FText::FromString(FString(TEXT("Not Sensing..."))));
	}

	// 디버깅용 스피어 그리기
	//DrawDebugSphere(world, player->rightHand->GetComponentLocation(), 25.0f, 30, FColor::Magenta, false, 3, 0, 1);
}

void UGrabComponent::ReleaseObject()
{
	if (currentObject == nullptr) return;

	currentObject->Released(deltaLoc, deltaQuat);
	currentObject = nullptr;
}

