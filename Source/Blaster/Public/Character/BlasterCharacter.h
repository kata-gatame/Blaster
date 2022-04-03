// kata.codes
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UCombatComponent;
class UWidgetComponent;

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Player", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	AWeapon* OverlappingWeapon;

	FString CharacterName;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* Combat;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

protected:
	virtual void BeginPlay() override;

	// movement
	void Move(float Value);
	void Strafe(float Value);
	void Turn(float Value);
	void Look(float Value);

	// actions
	void EquipButtonPressed();
	void CrouchButtonPressed();

public:
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	
	FORCEINLINE FString GetCharacterName() const { return CharacterName; }
};
