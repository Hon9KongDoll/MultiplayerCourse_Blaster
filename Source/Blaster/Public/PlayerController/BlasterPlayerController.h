#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABlasterPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void Jump();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> BlasterInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;
};
