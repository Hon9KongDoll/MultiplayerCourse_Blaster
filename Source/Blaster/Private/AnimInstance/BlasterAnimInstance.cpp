#include "AnimInstance/BlasterAnimInstance.h"
#include "Character/BlasterCharacter.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BlasterCharacter)
	{
		GroundSpeed = BlasterCharacter->GetVelocity().Size2D();

		bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();

		// GetCurrentAcceleration : ���ص�ǰ���ٶ�
		bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	}
}
