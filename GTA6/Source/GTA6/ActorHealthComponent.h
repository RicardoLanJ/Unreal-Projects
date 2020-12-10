// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/UnrealNetwork.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorHealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GTA6_API UActorHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorHealthComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float DefaultHealth;
	UPROPERTY(BlueprintReadOnly, Replicated)
		float Health;

	/** Call By Take any Damage, so run on Server*/
	UFUNCTION()
		void TakeDamage_OnServer(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser);


public:
	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
