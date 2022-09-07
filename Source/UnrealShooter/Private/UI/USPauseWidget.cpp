// UnrealShooter


#include "UI/USPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

 void UUSPauseWidget::NativeOnInitialized() 
 {
     Super::NativeOnInitialized();

     if (ClearPauseButton)
     {
         ClearPauseButton->OnClicked.AddDynamic(this, &UUSPauseWidget::OnClearPause);
     }
     
 }

 void UUSPauseWidget::OnClearPause() 
 {
     if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

     GetWorld()->GetAuthGameMode()->ClearPause();
 }