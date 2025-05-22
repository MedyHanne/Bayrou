#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengeOfJade.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AEndZone;

UCLASS()
class BAYROU_API AChallengeOfJade : public AActor
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UBoxComponent> startTrigger;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<AEndZone> endZone;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float timeLimit = 10.0f;
    UPROPERTY(EditAnywhere) TObjectPtr<AActor> right;
    UPROPERTY(EditAnywhere) TObjectPtr<AActor> left;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> mat;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> onGoingMat;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> looseMat;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float currentTime = 0.0f;
    UPROPERTY(EditAnywhere) TArray<TObjectPtr<AActor>> allPlatforms;

    bool raceStarted = false;
    bool raceCompleted = false;

public:
    FORCEINLINE bool HasWin() { return currentTime <= timeLimit; }
    FORCEINLINE bool GetRaceStarted() { return raceStarted; }
    FORCEINLINE void SetRaceStarted(bool _value) { raceStarted = _value; }

public:
    AChallengeOfJade();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    void ChallengeFailed();
private:
    void Init();
    void UpdateTime(float _deltaTime);
    void ChallengeSucceeded(AActor* _player);
    void SetMaterial(UMaterial* _mat);
    UFUNCTION()void OnPlayerEnterStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()void OnPlayerReachEnd(AActor* _overlappedActor);

};
