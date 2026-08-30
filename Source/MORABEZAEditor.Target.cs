using UnrealBuildTool;

public class MORABEZAEditorTarget : TargetRules
{
    public MORABEZAEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("MORABEZA");
    }
}
