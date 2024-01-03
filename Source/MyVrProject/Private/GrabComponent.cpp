 // Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "PickUpActor.h"
#include "MotionControllerComponent.h"
#include "Haptics/HapticFeedbackEffect_Curve.h"


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
		// 순서 중요 (계산 후 갱신하기)
		deltaLoc = player->rightController->GetComponentLocation() - prevLoc;
		prevLoc = player->rightController->GetComponentLocation();

		// 정석 방식
		//deltaQuat = player->rightController->GetComponentQuat() * prevQuat.Inverse(); // 역행렬 곱해주기
		// 언리얼에서만 가능
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
	float shereRadius = 25.0f;

	if (world->OverlapMultiByProfile(hitInfos, player->rightHand->GetComponentLocation(), player->rightHand->GetComponentQuat(), FName("PickUpPreset"), FCollisionShape::MakeSphere(shereRadius)))
	{
		//hitInfos -> 배열, 감지된 것 뭐뭐있는지 출력해보자
		FString objects;

		// 가장 가까운 놈 한 놈만 잡고싶다!
		float minDistance = shereRadius;// 최댓값(제일 멀어봤자 인식범위(shereRadius) 안
		int32 idx = 0;

		//for (const FOverlapResult& obj : hitInfos) // const 참조 형태로 최대한 메모리 덜 쓰도록 
		for (int32 i = 0; i < hitInfos.Num(); i++)
		{
			if (hitInfos[i].GetActor()->IsA<APickUpActor>())
			{
				//Text 출력
				//objects.Append(obj.GetActor()->GetActorNameOrLabel() + "\r\n");
				float dist = FVector::Distance(player->rightHand->GetComponentLocation(), hitInfos[i].GetActor()->GetActorLocation());
				if (dist < minDistance)
				{
					minDistance = dist;
					idx = i;
				}
			}

			// 잡기 1.
			//Cast<APickUpActor>(obj.GetActor())->Grabbed(player->RightHandMesh, EAttachmentRule::SnapToTarget); // EAttachmentRule 추가 231227
			//Cast<APickUpActor>(hitInfos[idx].GetActor())->Grabbed(player->RightHandMesh, EAttachmentRule::SnapToTarget);
		}

		// 잡기 2.
		currentObject = Cast<APickUpActor>(hitInfos[idx].GetActor());
		if (currentObject != nullptr)
		{
			currentObject->Grabbed(player->rightHand, EAttachmentRule::SnapToTarget);
			prevLoc = player->rightController->GetComponentLocation();// 초기화 부분 , 안하면 델타 너무 커진다?
			
			//player->rightLog->SetText(FText::FromString(objects));
			//231229
			prevQuat = player->rightController->GetComponentQuat();

			// 진동 효과를 준다.
			if (nullptr != player->PC && nullptr != GrabHaptic)
			{
				player->PC->PlayHapticEffect(GrabHaptic, EControllerHand::Right, 1, false);
			}
		}
	}
	else
	{
		// 닿은게 없으면
		player->rightLog->SetText(FText::FromString(FString(TEXT("Not Sensing..."))));
	}

	// 디버깅용 스피어 그리기
	//DrawDebugSphere(world, player->rightHand->GetComponentLocation(), shereRadius, 30, FColor::Magenta, false, 3, 0, 1);
}

void UGrabComponent::ReleaseObject()
{
	// 물체를 잡고있을때만 실행
	if (currentObject == nullptr) return;

	currentObject->Released(deltaLoc, deltaQuat);
	currentObject = nullptr;
}

