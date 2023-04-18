// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{

}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    //Get the player pawn/tank
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(InFireRange())
    {
        // If in range, rotate turret toward Tank
        RotateTurret(Tank->GetActorLocation());
    }

}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }
    if(InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Tank)
    {
        // Find the distance to the Tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // Check to see if th Tank is in range
        if(Distance <= FireRange)
        {
            // If in range, rotate turret toward Tank
            return true;
        }
        
    }

    return false;
}