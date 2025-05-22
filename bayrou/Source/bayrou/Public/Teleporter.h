#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

class ACharacter;

UCLASS()
class BAYROU_API ATeleporter : public AActor
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere) TObjectPtr<AActor> target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isActivated = true;
    TObjectPtr<ACharacter> characterRef;

public:
    FORCEINLINE bool IsActivated() { return isActivated; }
    FORCEINLINE void SetIsActivated(bool _value) { isActivated = _value; }

public:
    ATeleporter();

protected:
    virtual void BeginPlay() override;
private:
    UFUNCTION()void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()void TeleportPlayer();

};
