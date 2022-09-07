// UnrealShooter

using UnrealBuildTool;

public class UnrealShooter : ModuleRules
{
    public UnrealShooter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Niagara", "PhysicsCore","GameplayTasks","NavigationSystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {

            "UnrealShooter/Public/Player",
            "UnrealShooter/Public/Components",
            "UnrealShooter/Public/Dev, " +
            "UnrealShooter/Public/Weapon",
            "UnrealShooter/Public/Ui",
            "UnrealShooter/Public/Animations",
            "UnrealShooter/Public/Pickups",
            "UnrealShooter/Public/Weapon/Components",
            "UnrealShooter/Public/AI",
            "UnrealShooter/Public/AI/Tasks",
            "UnrealShooter/Public/AI/Services",
            "UnrealShooter/Public/AI/EQS",
            "UnrealShooter/Public/AI/Decorators",
            "UnrealShooter/Public/Menu",
            "UnrealShooter/Public/Sound"



        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
