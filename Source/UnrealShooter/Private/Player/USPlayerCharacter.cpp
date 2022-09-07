// UnrealShooter

#include "Player/USPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/USWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AUSPlayerCharacter::AUSPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{

    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollision = CreateDefaultSubobject<USphereComponent>("CameraCollision");
    CameraCollision->SetupAttachment(CameraComponent);
    CameraCollision->SetSphereRadius(10.0f);
    CameraCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AUSPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollision);
    CameraCollision->OnComponentBeginOverlap.AddDynamic(this, &AUSPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollision->OnComponentEndOverlap.AddDynamic(this, &AUSPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AUSPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void AUSPlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void AUSPlayerCharacter::CheckCameraOverlap() 
{
    const auto HideMesh = CameraCollision->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for (auto MeshChild : MeshChildren)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

void AUSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AUSPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AUSPlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &AUSPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AUSPlayerCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUSPlayerCharacter::Jump);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUSPlayerCharacter::OnRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AUSPlayerCharacter::StopRunning);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUSPlayerCharacter::OnStartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UUSWeaponComponent::StopFire);

    PlayerInputComponent->BindAction("Next Weapon", IE_Pressed, WeaponComponent, &UUSWeaponComponent::NextWeapon);

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &UUSWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &UUSWeaponComponent::Zoom,false);
}

void AUSPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);

    if (IsRunning() && WeaponComponent->IsFiring())
    {
        WeaponComponent->StopFire();
    }
}

void AUSPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AUSPlayerCharacter::OnRunning()
{
    WantsToRun = true;
    if (IsRunning())
    {
        WeaponComponent->StopFire();
    }
}

void AUSPlayerCharacter::StopRunning()
{
    WantsToRun = false;
}

void AUSPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void AUSPlayerCharacter::OnStartFire()
{
    if (IsRunning()) return;
    WeaponComponent->StartFire();
}

bool AUSPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}