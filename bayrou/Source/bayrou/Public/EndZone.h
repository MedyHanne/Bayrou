#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndZone.generated.h"

class UBoxComponent;
class USpotLightComponent;
class UStaticMeshComponent;
class ATargetArrow;
class ATeleporter;
class AChallengeOfJade;

UCLASS()
class BAYROU_API AEndZone : public AActor
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndZoneReached, AActor*, _overlappingActor);
	UPROPERTY() FOnEndZoneReached onEndZoneReached;

protected:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)UBoxComponent* endTrigger;
	UPROPERTY() USpotLightComponent* spotLight;*/
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh;
	UPROPERTY(EditAnywhere) TObjectPtr<AChallengeOfJade> challenge;
	UPROPERTY(EditAnywhere) TObjectPtr<ATargetArrow> arrow;
	UPROPERTY(EditAnywhere) TObjectPtr<ATeleporter> teleporter;

	UPROPERTY(EditAnywhere) TObjectPtr<USpotLightComponent> beaconLight;

	UPROPERTY(EditAnywhere) float blinkingStartTime = 5.0f;

	float blinkTimer = 0.0f;
	bool blinkState = true;

	bool hasFinish = false;
	bool isActive = false;


public:
	FORCEINLINE FOnEndZoneReached& OnEndZoneReached() { return onEndZoneReached; }
	FORCEINLINE bool IsActive() { return isActive; }
	FORCEINLINE void SetIsActive(bool _isActive) { isActive = _isActive; }

public:
	AEndZone();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void Init();
	void InitSpotLight();
	UFUNCTION()void HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
