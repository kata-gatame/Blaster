// kata.codes
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;

UCLASS()
class BLASTER_API AProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

protected:
	virtual void BeginPlay() override;

public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
};