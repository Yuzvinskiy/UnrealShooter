// UnrealShooter

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealShooterTarget : TargetRules
{
    public UnrealShooterTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange(new string[] { "UnrealShooter" });
    }
}
