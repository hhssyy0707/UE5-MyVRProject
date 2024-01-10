// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "MoveComponent.h"
#include "NiagaraComponent.h"
#include "GrabComponent.h"
#include "VRHandAnimComponent.h"
#include "VRBodyAnimInstance.h"
#include "GazeComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetPointerComp.h"
#include "MyCarActor.h"
#include "EngineUtils.h"
#include "CarControllerComponent.h"



AVR_Player::AVR_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(RootComponent);

	GazeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gaze Mesh"));
	GazeMeshComp->SetupAttachment(cameraComp);
	GazeMeshComp->SetRelativeLocation(FVector(100.f,0,0));
	GazeMeshComp->SetRelativeRotation(FRotator(-90,-90,0));
	GazeMeshComp->SetWorldScale3D(FVector(0.1f));

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(cameraComp);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	leftController->SetRelativeLocation(FVector(50, -30, -10));
	leftController->SetTrackingMotionSource(FName("Left"));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(-90, -45, -180));

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftHand);
	leftLog->SetRelativeLocation(FVector(-20, 10, 0));
	leftLog->SetRelativeRotation(FRotator(0, -90, -90));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	leftLog->SetWorldSize(20);
	leftLog->SetTextRenderColor(FColor(255, 255, 0));

	//240103
	LeftPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Pointer"));
	LeftPointer->SetupAttachment(leftHand);

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->SetRelativeLocation(FVector(50, 30, -10));
	rightController->SetTrackingMotionSource(FName("Right"));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(90, 45, 0));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightHand);
	rightLog->SetRelativeLocation(FVector(20, 10, 0));
	rightLog->SetRelativeRotation(FRotator(0, -90, 90));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetWorldSize(20);
	rightLog->SetTextRenderColor(FColor(255, 255, 0));

	//240103
	RightPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	RightPointer->SetupAttachment(rightHand);

	teleportFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport Effect"));
	teleportFX->SetupAttachment(leftHand);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 액터 컴포넌트
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));
	grabComp = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));

	// 애니메이션 컴포넌트
	HandAnimComp = CreateDefaultSubobject<UVRHandAnimComponent>(TEXT("VR Hand Anim Component"));

	GazeComp = CreateDefaultSubobject<UGazeComponent>(TEXT("Gaze Component")); //입력은 안하고 붙이는 것만 할 거야

	//240103 UI 클릭하기 위한 위젯포인터 컴포넌트 추가
	WidgetPointerComp = CreateDefaultSubobject<UWidgetPointerComp>(TEXT("Widget Pointer Component"));

	CarControllerComp = CreateDefaultSubobject<UCarControllerComponent>(TEXT("Car Controller Component"));
}

void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	// 헤드 마운트 디스플레이 장비의 트래킹(추적) 기준 위치를 Stage로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	// 입력 매핑 설정하기
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr && imc != nullptr)
		{
			subsys->AddMappingContext(imc, 0);
		}
	}

	//231228
	bodyAnim = Cast<UVRBodyAnimInstance>(GetMesh()->GetAnimInstance());

	//240104
	//필드에 차 액터를 찾아서 변수에 할당한다.
	for (TActorIterator<AMyCarActor> car(GetWorld()); car; ++car) {
		MyFirstCar = *car;
	}
}

void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bodyAnim != nullptr) {
		bodyAnim->LeftHandLocation = leftController->GetComponentLocation();
		bodyAnim->LeftHandRotation = leftController->GetComponentRotation();

		bodyAnim->RightHandLocation = rightController->GetComponentLocation();
		bodyAnim->RightHandRotation = rightController->GetComponentRotation();

		bodyAnim->HeadLocation = cameraComp->GetComponentLocation();
		bodyAnim->HeadRotation = cameraComp->GetComponentRotation();
	}

	if (RecenterTick)
	{
		recenterTimer += DeltaTime;
	}

	/*if (MyFirstCar != nullptr) {
		MyFirstCar->RotateCar(0.1f);
	}*/
}

void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 기존 입력 데이터를 Enhanced 입력 데이터 형태로 변환한다.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		// 입력 키 바인딩하기
		/*enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Bool);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Bool);*/
		/*enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Float);
		enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Float);
		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Triggered, this, &AVR_Player::RightThumbstickInput);
		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Completed, this, &AVR_Player::RightThumbstickInput);
		enhancedInputComponent->BindAction(ia_moveInput, ETriggerEvent::Triggered, this, &AVR_Player::PlayerMove);
		enhancedInputComponent->BindAction(ia_rotateInput, ETriggerEvent::Triggered, this, &AVR_Player::PlayerRotate);*/

		enhancedInputComponent->BindAction(ia_inputs[10], ETriggerEvent::Started, this, &AVR_Player::RecenterStart);
		enhancedInputComponent->BindAction(ia_inputs[10], ETriggerEvent::Triggered, this, &AVR_Player::Recenter);
		enhancedInputComponent->BindAction(ia_inputs[10], ETriggerEvent::Completed, this, &AVR_Player::StopRecenter);
		enhancedInputComponent->BindAction(ia_inputs[10], ETriggerEvent::Canceled, this, &AVR_Player::StopRecenter);

		// A버튼 누를 때 뷰 재정렬
		enhancedInputComponent->BindAction(ia_inputs[11], ETriggerEvent::Triggered, this, &AVR_Player::PlayerRotate);

		// 컴포넌트에 입력 이벤트 넘겨주기
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		grabComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		HandAnimComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
		WidgetPointerComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs); //240103 추가
		CarControllerComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs); //240104 추가
	}
}

void AVR_Player::RightTriggerInput_Bool(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Pressed!")));

		////231229 HO코드 추가
		//BasicTeleport(3000, rightHand->GetRightVector().GetSafeNormal(), rightController->GetComponentLocation());

	}
	else
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Released!")));
	}

}

void AVR_Player::RightTriggerInput_Float(const FInputActionValue& value)
{
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("RightTrigger : %.2f"), value.Get<float>())));

	BasicTeleport(500, rightController->GetForwardVector(), rightController->GetComponentLocation());
}

void AVR_Player::RightTriggerInput_Touch(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Touched!")));
	}
	else
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Untouched!")));
	}
}

void AVR_Player::RightThumbstickInput(const FInputActionValue& value)
{
	FVector2D inputValue = value.Get<FVector2D>();

	//231229 HO코드 추가
	AddControllerYawInput(inputValue.X);

	rightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), inputValue.X, inputValue.Y)));
}

void AVR_Player::PlayerMove(const FInputActionValue& value)
{
	/*
	// 1. 플레이어가 입력(상w하s좌a우d + 썸스틱)한대로
	FVector inputDir = FVector(value.Get<FVector2D>().X, value.Get<FVector2D>().Y, 0);
	//UE_LOG(LogTemp, Log, TEXT("X: %.2f, Y: %.2f, Z: %.2f"), inputDir.X, inputDir.Y, inputDir.Z);

	// 2. 회전을 하지 않은 상태에서의 방향을 현재 회전된 방향에 맞춰 변환한다.
	FVector modifiedDir = GetTransform().TransformVector(inputDir);

	// 3. 이동한다.
	AddMovementInput(modifiedDir);
	*/


	const FVector2D InputValue = value.Get<FVector2D>();

	const FVector Dir = FVector(InputValue.X, InputValue.Y, 0);

	const FVector WorldDir = FTransform(GetControlRotation()).TransformVector(Dir);

	leftLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), Dir.X, Dir.Y)));

	AddMovementInput(WorldDir);
}

void AVR_Player::PlayerRotate(const FInputActionValue& value)
{
	// 입력(좌우: mouse 가로 방향)한대로 
	float inputDir = value.Get<float>();

	// 회전한다.
	AddControllerYawInput(inputDir);
}

void AVR_Player::BasicTeleport(float sightRange, FVector direction, FVector pivot)
{
	// 가리킨 지점(direction 방향으로 sightRange 거리만큼 발사한 라인이 땅과 닿은 지점)으로

	FHitResult hitInfo;
	FVector startVec = pivot;
	FVector endVec = pivot + direction * sightRange;
	bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility);

	// 만일, 닿았다면 나를 이동시킨다.
	if (bIsCollide)
	{
		//SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		// 닿았다면 닿은 지점까지 라인을 그린다.
		DrawDebugLine(GetWorld(), startVec, hitInfo.ImpactPoint, FColor::Red);
	}
	// 닿지 않았다면 최대 지점까지 라인을 그린다.
	else 
	{
		DrawDebugLine(GetWorld(), startVec, endVec, FColor::Red);
	}

	
}

void AVR_Player::Recenter(const FInputActionValue& value)
{
	// 플레이어 시점 재정렬
	recenterTimer += GetWorld()->DeltaRealTimeSeconds;
	if (recenterTimer < 2) {
		return;
	}
	else {
		UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(0, EOrientPositionSelector::OrientationAndPosition);
		recenterTimer = 0;
	}
}

void AVR_Player::StopRecenter(const FInputActionValue& value)
{
	recenterTimer = 0;
	RecenterTick = false;
}

void AVR_Player::RecenterStart(const FInputActionValue& value)
{
	RecenterTick = true;
}

