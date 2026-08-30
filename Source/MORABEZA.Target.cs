using UnrealBuildTool;
using System.Collections.Generic;

public class MORABEZATarget : TargetRules
{
    public MORABEZATarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("MORABEZA");
    }
}
