// UnrealShooter


#include "UI/USGoToMenuWidget.h"
#include "Components/Button.h"
#include "USGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSGoToMenuWidget, All, All)

 void UUSGoToMenuWidget::NativeOnInitialized() 
 {
     Super::NativeOnInitialized();

     if (GoToMenuButton)
     {
         GoToMenuButton->OnClicked.AddDynamic(this, &UUSGoToMenuWidget::OnGoToMenu);
     }
 }

 void UUSGoToMenuWidget::OnGoToMenu() 
 {
     if (!GetWorld()) return;
    

     const auto USGameInstance = GetWorld()->GetGameInstance<UUSGameInstance>();
     if (!USGameInstance) return;

     if (USGameInstance->GetMenuLevelName().IsNone())
     {
         UE_LOG(LogUSGoToMenuWidget, Error, TEXT("Menu Level name Is NONE"));
         return;
     }

     UGameplayStatics::OpenLevel(this, USGameInstance->GetMenuLevelName());
 }