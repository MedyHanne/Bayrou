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
    UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<AEndZone> endZone;
    /*UPROPERTY(EditAnywhere) TObjectPtr<UJadeChallengeWidget> jadeChallengeWidget = nullptr;
    UPROPERTY(EditAnywhere) TObjectPtr<UWinPopupWidget> winPopupWidget = nullptr;*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float timeLimit = 10.0f;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> mat;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> onGoingMat;
    UPROPERTY(EditAnywhere) TObjectPtr<UMaterial> looseMat;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite) float currentTime = 0.0f;
    UPROPERTY(EditAnywhere) TArray<TObjectPtr<AActor>> allPlatforms;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isPlayerDashing = false;

    bool raceStarted = false;
    bool raceCompleted = false;

public:
    FORCEINLINE bool HasWin() { return currentTime <= timeLimit; }
    FORCEINLINE bool GetRaceStarted() { return raceStarted; }
    FORCEINLINE void SetRaceStarted(bool _value) { raceStarted = _value; }
    FORCEINLINE bool GetRaceCompleted() { return raceCompleted; }
    FORCEINLINE void SetRaceCompleted(bool _value) { raceCompleted = _value; }
    FORCEINLINE float GetTimeLimit() { return timeLimit; }
    FORCEINLINE float GetCurrentTime() { return currentTime; }
    FORCEINLINE bool IsPlayerDashing() { return isPlayerDashing; }

public:
    AChallengeOfJade();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    void ChallengeFailed();
    //void SetReset(AResetChallengeOfJadeActor* _reset);
private:
    void Init();
    void UpdateTime(float _deltaTime);
    void ChallengeSucceeded(AActor* _player);
    void SetMaterial(UMaterial* _mat);
    UFUNCTION()void OnPlayerReachEnd(AActor* _overlappedActor);
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    void SetMeshCollision(ECollisionResponse _rep);
    //UMainWidget* GetMainWidget();

};
