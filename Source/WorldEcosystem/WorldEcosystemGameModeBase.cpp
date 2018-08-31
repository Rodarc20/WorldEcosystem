// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldEcosystemGameModeBase.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AWorldEcosystemGameModeBase::AWorldEcosystemGameModeBase() {
	double secs = FTimespan(FDateTime::Now().GetTicks()).GetTotalSeconds();
	int32 seed = (int32)(((int64)secs) % INT_MAX);
    FMath::RandInit(seed);

    PrimaryActorTick.bCanEverTick = false;//esto hacia falta en el tutprial, sin esto unreal no llama a la funcion tick en cada cuadro

    static ConstructorHelpers::FClassFinder<USimulationHUD> HUDWidgetClass(TEXT("WidgetBlueprintGeneratedClass'/Game/WorldEcosystem/UMG/SimulationHUDBP.SimulationHUDBP_C'"));
    //deberia buscar una grafica
    if (HUDWidgetClass.Succeeded()) {
        TypeHUDWidget = HUDWidgetClass.Class;
    }
}

AWorldEcosystemGameModeBase::AWorldEcosystemGameModeBase(const FObjectInitializer & ObjectInitializer) {
	double secs = FTimespan(FDateTime::Now().GetTicks()).GetTotalSeconds();
	int32 seed = (int32)(((int64)secs) % INT_MAX);
    FMath::RandInit(seed);
    PrimaryActorTick.bCanEverTick = false;//esto hacia falta en el tutprial, sin esto unreal no llama a la funcion tick en cada cuadro
    static ConstructorHelpers::FClassFinder<USimulationHUD> HUDWidgetClass(TEXT("WidgetBlueprintGeneratedClass'/Game/WorldEcosystem/UMG/SimulationHUDBP.SimulationHUDBP_C'"));
    //deberia buscar una grafica
    if (HUDWidgetClass.Succeeded()) {
        TypeHUDWidget = HUDWidgetClass.Class;
    }

}

void AWorldEcosystemGameModeBase::BeginPlay() {
    Super::BeginPlay();

    if (TypeHUDWidget) {
        VisualizationHUDReference = CreateWidget<USimulationHUD>(GetWorld(), TypeHUDWidget);//le doy el mundo sobre el que se instancia, y lo que instanciare
        if (VisualizationHUDReference) {
            VisualizationHUDReference->AddToViewport();
            //VisualizationHUDReference->SetUserFocus()
        }
    }
    UWorld * World = GetWorld();
    if (World) {
        APlayerController * PlayerController = UGameplayStatics::GetPlayerController(World, 0);
        PlayerController->bShowMouseCursor = true;
        FInputModeGameAndUI Mode = FInputModeGameAndUI();
        //Mode.SetWidgetToFocus(VisualizationHUDReference->TakeWidget());
        PlayerController->SetInputMode(FInputModeGameAndUI());

        TArray<AActor *> EcosistemasEncontrados;
        UGameplayStatics::GetAllActorsOfClass(World, AEcosistema::StaticClass(), EcosistemasEncontrados);
        //UE_LOG(LogClass, Log, TEXT("Numero de Ecosistemasencontradas: %d"), ConexionesExcontradas.Num());
        if (EcosistemasEncontrados.Num()) {
            AEcosistema * const Ecosistema = Cast<AEcosistema>(EcosistemasEncontrados[0]);
            if (Ecosistema) {
                //UE_LOG(LogClass, Log, TEXT("Ecosistema Encontrada"));
                EcosistemaReference = Ecosistema;
                if (VisualizationHUDReference) {
                    VisualizationHUDReference->EcosistemaReference = Ecosistema;
                }
            }
        }
    }

}

void AWorldEcosystemGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AWorldEcosystemGameModeBase::CargarValoresDefault() {
}



