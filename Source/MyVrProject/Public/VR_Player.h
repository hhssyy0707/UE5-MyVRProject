// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VR_Player.generated.h"

UCLASS()
class MYVRPROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AVR_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UStaticMeshComponent* hmdMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* leftHand;

	//240103 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UWidgetInteractionComponent* LeftPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;

	//240103 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UWidgetInteractionComponent* RightPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UTextRenderComponent* rightLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMoveComponent* moveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UNiagaraComponent* teleportFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UGrabComponent* grabComp;

	//240103 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UWidgetPointerComp* WidgetPointerComp; //제어, 클릭 기능이 들어가있는 컴포넌트
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UVRHandAnimComponent* HandAnimComp;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UStaticMeshComponent* GazeMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UGazeComponent* GazeComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UCarControllerComponent* CarControllerComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputMappingContext* imc;

	UPROPERTY()
	class UVRBodyAnimInstance* bodyAnim;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_rightTriggerBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_rightTriggerFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_rightTriggerTouch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_rightThumbStick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_moveInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_rotateInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* ia_leftTriggerBool;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	TArray<class UInputAction*> ia_inputs;

	UPROPERTY(EditAnywhere, Category = "MySettings|Variables")
	class AMyCarActor* MyFirstCar;


	APlayerController* PC;

	//float RecenterTickTimer{0.f};
	float recenterTimer{0.f};

	UPROPERTY(EditAnywhere)
	float RecenterHoldAmountSeconds{1.0f};

	bool RecenterTick{false};


private:
	void RightTriggerInput_Bool(const FInputActionValue& value);
	void RightTriggerInput_Float(const FInputActionValue& value);
	void RightTriggerInput_Touch(const FInputActionValue& value);
	void RightThumbstickInput(const FInputActionValue& value);
	void PlayerMove(const FInputActionValue& value);
	void PlayerRotate(const FInputActionValue& value);
	void BasicTeleport(float sightRange, FVector direction, FVector pivot);
	
	void Recenter(const FInputActionValue& value);
	void StopRecenter(const FInputActionValue& value);
	void RecenterStart(const FInputActionValue& value);

};
