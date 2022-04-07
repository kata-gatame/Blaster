// kata.codes
#include "BlasterComponents/CombatComponent.h"
#include "Character/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	BaseWalkSpeed = 600.f;
	AimWalkSpeed = 450.f;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

void UCombatComponent::SetADS(bool bADS)
{
	bIsADS = bADS;
	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = bIsADS ? AimWalkSpeed : BaseWalkSpeed;
	ServerSetADS(bADS);
}

void UCombatComponent::ServerSetADS_Implementation(bool bADS)
{
	bIsADS = bADS;
	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = bIsADS ? AimWalkSpeed : BaseWalkSpeed;
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, EquippedWeapon);
	DOREPLIFETIME(ThisClass, bIsADS);
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	if (const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket")))
	{
		HandSocket->AttachActor(WeaponToEquip, Character->GetMesh());
	}
	EquippedWeapon->SetOwner(Character);
	CorrectOrientation();
}

void UCombatComponent::OnRep_EquippedWeapon() const
{
	if (EquippedWeapon && Character) CorrectOrientation();
}

void UCombatComponent::CorrectOrientation() const
{
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	Character->bUseControllerRotationYaw = true;
}
