// UnrealShooter

#include "Player/USBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/USCharacterMovementComponent.h"
#include "Components/USHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/USWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

AUSBaseCharacter::AUSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UUSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UUSHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<UUSWeaponComponent>("WeaponComponent");
   
}

// Called when the game starts or when spawned
void AUSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AUSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AUSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AUSBaseCharacter::OnGroundLanded);
}

void AUSBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called every frame
void AUSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AUSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AUSBaseCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &AUSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AUSBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUSBaseCharacter::Jump);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUSBaseCharacter::OnRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AUSBaseCharacter::StopRunning);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUSBaseCharacter::OnStartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UUSWeaponComponent::StopFire);

    PlayerInputComponent->BindAction("Next Weapon", IE_Pressed, WeaponComponent, &UUSWeaponComponent::NextWeapon);
}

void AUSBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);

    if (IsRunning() && WeaponComponent->IsFiring())
    {
        WeaponComponent->StopFire();
    }
}

void AUSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AUSBaseCharacter::OnRunning()
{
    WantsToRun = true;
    if (IsRunning())
    {
        WeaponComponent->StopFire();
    }
}

void AUSBaseCharacter::StopRunning()
{
    WantsToRun = false;
}

bool AUSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AUSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsNearlyZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AUSBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
}

void AUSBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X)
    {
        return;
    }

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(BaseCharacterLog, Display, TEXT("Final Damage: %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AUSBaseCharacter::OnStartFire()
{
    if (IsRunning()) return;
    WeaponComponent->StartFire();
}
