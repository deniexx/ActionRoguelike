// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class USSaveGame;
class UEnvQueryInstanceBlueprintWrapper;
class UDataTable;
class USMonsterData;

USTRUCT(BlueprintType)
struct FMonsterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FMonsterInfoRow()
	{
		Weight = 1.0f;
		SpawnCost = 5.0f;
		KillReward = 150.0f;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId MonsterID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float KillReward;
};

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASGameModeBase();
	
	virtual void StartPlay() override;

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:

	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;
	
	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UDataTable* MonsterTable;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;
	
	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnMonsterLoaded(FPrimaryAssetId LoadedID, FVector SpawnLocation);

	// UPROPERTY(EditDefaultsOnly, Category = "AI")
	// TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 CreditsPerKill;

	UPROPERTY()
	USSaveGame* CurrentSaveGame;

	FString SlotName;

	// Exec funstions
	UFUNCTION(Exec)
	void KillAll();
};
