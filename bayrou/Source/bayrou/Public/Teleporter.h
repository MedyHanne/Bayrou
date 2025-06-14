#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

class ACharacter;

UCLASS()
class BAYROU_API ATeleporter : public AActor
{
	GENERATED_BODY()
protected:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivate);
    UPROPERTY(BlueprintAssignable, BlueprintType) FOnActivate onActivate;
public:
    UPROPERTY(EditAnywhere) TObjectPtr<AActor> target;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isActivated = true;
    TObjectPtr<ACharacter> characterRef;

public:
    FORCEINLINE bool IsActivated() { return isActivated; }
    FORCEINLINE void SetIsActivated(bool _value) { isActivated = _value; }
    FORCEINLINE FOnActivate& OnActivate() { return onActivate; }

public:
    ATeleporter();

protected:
    virtual void BeginPlay() override;
private:
    UFUNCTION()void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()void TeleportPlayer();

};
