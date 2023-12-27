// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "VRDrawFunctionLibrary.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "TeleportRingActor.h"
#include "NiagaraComponent.h"


UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

	// 텔레포트 지점 위치에 표시할 링 이펙트 액터를 생성한다.
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	teleportRingInst = GetWorld()->SpawnActor<ATeleportRingActor>(teleportRingBP, FVector::ZeroVector, FRotator::ZeroRotator, params);

	if (teleportRingInst != nullptr)
	{
		// 눈에 보이지 않게 처리한다.
		teleportRingInst->ring_FX->SetVisibility(false);
	}
}


void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{
	// DrawTrajectory를 바로 바인딩 할 수 없으므로 중계함수를 사용한다
	enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);
	// 트리거에서 손을 놓았을시 순간이동 함수 바인드
	enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Completed, this, &UMoveComponent::Teleport);
}

// 예측선 보이게 하는 함수
void UMoveComponent::ShowLine(const FInputActionValue& value)
{
	bool bIsPressed = value.Get<bool>();

	//player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("%s"), bIsPressed ? *FString("Pressed!") : *FString("Released..."))));

	if (bIsPressed && player != nullptr)
	{
#pragma region 중력 가속도를 이용한 방식
		DrawTrajectory(player->leftController->GetComponentLocation(), player->leftHand->GetForwardVector() * -1 + player->leftHand->GetRightVector(), lineSpeed, 50, 0.1f);

#pragma endregion

#pragma region 베지어 곡선식을 이용한 방식
		//DrawTrajectoryBezier(player->leftHand->GetComponentLocation(), player->leftHand->GetForwardVector() + player->leftHand->GetRightVector(), 50);

#pragma endregion
	}
}

// 예측 선을 계산하고 그리는 함수(중력 방식)
void UMoveComponent::DrawTrajectory(FVector startLoc, FVector dir, float speed, int32 segment, float interval)
{
	// Direction 방향으로 Segment 회만큼 Interval 간격 (초)로 반복해서 이동했을 위치를 계산한다.
	// 계산 결과 값들은 배열에 담아놓는다.


	// 값을 담아놓을 배열.
	TArray<FVector> linePositions;

	for (int32 i = 0; i < segment; i++)
	{
		// dir 방향으로 segment 회만큼 interval 간격(초)으로 반복해서 이동했을 위치를 계산한다.
		float elapsedTime = interval * i;
		FVector gravityVec = FVector(0, 0, GetWorld()->GetDefaultGravityZ());
		FVector newLocation = startLoc + dir * speed * elapsedTime + (0.5f * gravityVec * elapsedTime * elapsedTime);// 자유낙하식 1/2gt^2 라고 함

		// 뭔가에 부딪혔을시 배열에 그만 추가함
		FHitResult hitInfo;
		if (i > 0 && GetWorld()->LineTraceSingleByChannel(hitInfo, linePositions[i - 1], newLocation, ECC_Visibility))
		{
			player->leftLog->SetText(FText::FromString(hitInfo.GetActor()->GetActorNameOrLabel()));

			// 마지막 점을 부딪힌 부분으로 함
			linePositions.Add(hitInfo.ImpactPoint);
			break;
		}

		// 계산 결과 값들은 배열 변수에 담아놓는다.
		linePositions.Add(newLocation);

	}

	// 계산된 위치들을 선으로 연결해서 그린다.
	/*for (int32 i = 0; i < linePositions.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), linePositions[i], linePositions[i + 1], FColor::Green, false, 0, 0, 2.0f);

	}*/


	// 나이아가라 시스템으로 그리기
	//player->teleportFX->SetVisibility(true);// 현오 코드)
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->teleportFX, FName("PointArray"), linePositions);

	// 이동할 곳 저장
	// 마지막 위치에 빨강 상자를 표시한다.
	targetLocation = linePositions[linePositions.Num() - 1];
	//TargetLocation = LinePositions.Last(); // 현오 코드) 이렇게도 가능
	

	// 이펙트 표시하기
	//DrawDebugSolidBox(GetWorld(), targetLocation, FVector(5), FColor::Red);
	if (teleportRingInst != nullptr)
	{
		teleportRingInst->SetActorLocation(targetLocation);
		teleportRingInst->ring_FX->SetVisibility(true);
	}
}

void UMoveComponent::DrawTrajectoryBezier(FVector startLoc, FVector dir, int32 segment)
{
	FHitResult hitInfo;
	FVector endLoc = startLoc + dir * 1000; // 1000 Length
	FVector hitLoc;


	if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility))
	{
		hitLoc = hitInfo.ImpactPoint;
		FVector centorLoc = FVector((hitLoc.X + startLoc.X)*0.5f, (hitLoc.Y + startLoc.Y) * 0.5f, startLoc.Z);

		TArray<FVector> results = UVRDrawFunctionLibrary::CalculateBezierCurve(startLoc, centorLoc, hitLoc, segment);

		if (results.Num() > 0)
		{
			for (int32 i = 0; i < results.Num() - 1; i++)
			{
				DrawDebugLine(GetWorld(), results[i], results[i+1], FColor::Green, false, 0, 0, 2);
			}
		}
	}
	
}

// 목표 지점으로 순간이동하는 함수
void UMoveComponent::Teleport()
{
	// Black Fade In 효과를 준다.
	player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1.0f, teleportDelay, FLinearColor::Black);


	// TeleportDelayTime이 지난후 텔레포트한다.
	if (!targetLocation.IsNearlyZero())
	{
		FTimerHandle teleportTimer;

		GetWorld()->GetTimerManager().SetTimer(teleportTimer, FTimerDelegate::CreateLambda([&]() {
			//1. 플레이어 이동
			player->SetActorLocation(targetLocation + FVector(0, 0, player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
			//2. 링 이펙트 표시 끄기
			teleportRingInst->ring_FX->SetVisibility(false);
			//3. 라인 이펙트의 배열 값 초기화
			TArray<FVector> resetVec = { FVector::ZeroVector, FVector::ZeroVector };
			UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->teleportFX, FName("PointArray"), resetVec);
			}), teleportDelay, false);
	}
}

