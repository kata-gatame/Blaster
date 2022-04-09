#pragma once

UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left UMETA(Displayname = "Turning Left"),
	ETIP_Right UMETA(Displayname = "Turning Right"),
	ETIP_NotTurning UMETA(Displayname = "Not Turning"),

	ETIP_MAXLeft UMETA(Displayname = "DefaultMAX")
};