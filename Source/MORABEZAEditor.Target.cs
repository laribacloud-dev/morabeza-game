using UnrealBuildTool;

public class MORABEZAEditorTarget : TargetRules
{
    public MORABEZAEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.Add("MORABEZA");
    }
}
