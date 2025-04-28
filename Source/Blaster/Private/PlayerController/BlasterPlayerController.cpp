#include "PlayerController/BlasterPlayerController.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

ABlasterPlayerController::ABlasterPlayerController()
{
	bReplicates = true;
}

void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			check(BlasterInputMappingContext);

			PlayerSubsystem->AddMappingContext(BlasterInputMappingContext, 0);
		}
	}
}

void ABlasterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABlasterPlayerController::Move);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ABlasterPlayerController::Turn);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABlasterPlayerController::Jump);
	}
}

void ABlasterPlayerController::Move(const FInputActionValue& InputActionValue)
{
	FVector2D InputVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputVector.X);
	}
}

void ABlasterPlayerController::Turn(const FInputActionValue& InputActionValue)
{
	FVector2D InputVector = InputActionValue.Get<FVector2D>();
	AddYawInput(InputVector.X);
	AddPitchInput(-InputVector.Y);
}

void ABlasterPlayerController::Jump()
{
	if (ACharacter* ControllerCharacter = Cast<ACharacter>(GetPawn()))
	{
		ControllerCharacter->Jump();
	}
}
