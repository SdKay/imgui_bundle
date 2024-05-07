/*
A more complex app demo,

It demonstrates:
- How to use a specific application state (instead of using static variables)
- How to set up a complex docking layouts (with several possible layouts):
- How to use the status bar
- How to use default menus (App and view menu), and how to customize them
- How to display a log window
- How to load additional fonts
*/

#include "immapp/immapp.h"
#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"
#include "demo_utils/api_demos.h"

#include "movex_tool/window_factory.hpp"
#include "movex_tool/app_gui.hpp"

#include <sstream>

ImFont * gTitleFont;
void LoadFonts() // This is called by runnerParams.callbacks.LoadAdditionalFonts
{
    // First, load the default font (the default font should be loaded first)
    HelloImGui::ImGuiDefaultSettings::LoadDefaultFont_WithFontAwesomeIcons();
    // Then load the title font
    // gTitleFont = HelloImGui::LoadFontTTF("fonts/DroidSans.ttf", 18.f);
    gTitleFont = HelloImGui::LoadFontTTF_WithFontAwesomeIcons("fonts/DroidSans.ttf", 18.f, false);
}

//////////////////////////////////////////////////////////////////////////
//    Save additional settings in the ini file
//////////////////////////////////////////////////////////////////////////
// This demonstrates how to store additional info in the application settings
// Use this sparingly!
// This is provided as a convenience only, and it is not intended to store large quantities of text data.

// Warning, the save/load function below are quite simplistic!
std::string MyAppSettingsToString(const mtool::MyAppSettings& myAppSettings)
{
    std::stringstream ss;
    ss << myAppSettings.name << "\n";
    ss << myAppSettings.value;
    return ss.str();
}
mtool::MyAppSettings StringToMyAppSettings(const std::string& s)
{
    std::stringstream ss(s);
    mtool::MyAppSettings myAppSettings;
    ss >> myAppSettings.name;
    ss >> myAppSettings.value;
    return myAppSettings;
}

// Note: LoadUserSettings() and SaveUserSettings() will be called in the callbacks `PostInit` and `BeforeExit`:
//     runnerParams.callbacks.PostInit = [&guiContext]   { LoadMyAppSettings(guiContext);};
//     runnerParams.callbacks.BeforeExit = [&guiContext] { SaveMyAppSettings(guiContext);};
void LoadMyAppSettings(mtool::GuiContext& guiContext) //
{
    guiContext.myAppSettings = StringToMyAppSettings(HelloImGui::LoadUserPref("mtool::MyAppSettings"));
}
void SaveMyAppSettings(const mtool::GuiContext& guiContext)
{
    HelloImGui::SaveUserPref("mtool::MyAppSettings", MyAppSettingsToString(guiContext.myAppSettings));
}

//////////////////////////////////////////////////////////////////////////
//    Gui functions used in this demo
//////////////////////////////////////////////////////////////////////////


void DemoDockingFlags()
{
    ImGui::PushFont(gTitleFont); ImGui::Text("Main dock space node flags"); ImGui::PopFont();
    ImGui::TextWrapped(R"(
This will edit the ImGuiDockNodeFlags for "MainDockSpace".
Most flags are inherited by children dock spaces.
    )");
    struct DockFlagWithInfo {
        ImGuiDockNodeFlags flag;
        std::string label;
        std::string tip;
    };
    std::vector<DockFlagWithInfo> all_flags = {
        {ImGuiDockNodeFlags_NoSplit, "NoSplit", "prevent Dock Nodes from being split"},
        {ImGuiDockNodeFlags_NoResize, "NoResize", "prevent Dock Nodes from being resized"},
        {ImGuiDockNodeFlags_AutoHideTabBar, "AutoHideTabBar",
         "show tab bar only if multiple windows\n"
         "You will need to restore the layout after changing (Menu \"View/Restore Layout\")"},
        {ImGuiDockNodeFlags_NoDockingInCentralNode, "NoDockingInCentralNode",
         "prevent docking in central node\n"
         "(only works with the main dock space)"},
        // {ImGuiDockNodeFlags_PassthruCentralNode, "PassthruCentralNode", "advanced"},
    };
    auto & mainDockSpaceNodeFlags = HelloImGui::GetRunnerParams()->dockingParams.mainDockSpaceNodeFlags;
    for (auto flag: all_flags)
    {
        ImGui::CheckboxFlags(flag.label.c_str(), &mainDockSpaceNodeFlags, flag.flag);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s", flag.tip.c_str());
    }
}

// The menu gui
void ShowMenuGui()
{
    if (ImGui::BeginMenu("My Menu"))
    {
        bool clicked = ImGui::MenuItem("Test me", "", false);
        if (clicked)
        {
            HelloImGui::Log(HelloImGui::LogLevel::Warning, "It works");
        }
        ImGui::EndMenu();
    }
}

void ShowAppMenuItems()
{
    if (ImGui::MenuItem("A Custom app menu item"))
        HelloImGui::Log(HelloImGui::LogLevel::Info, "Clicked on A Custom app menu item");
}


//////////////////////////////////////////////////////////////////////////
//    Docking Layouts and Docking windows
//////////////////////////////////////////////////////////////////////////

//
// 1. Define the Docking splits (two versions are available)
//
std::vector<HelloImGui::DockingSplit> CreateDefaultDockingSplits()
{
    //    Define the default docking splits,
    //    i.e. the way the screen space is split in different target zones for the dockable windows
    //     We want to split "MainDockSpace" (which is provided automatically) into three zones, like this:
    //
    //    ___________________________________________
    //    |        |                                |
    //    | Command|                                |
    //    | Space  |    MainDockSpace               |
    //    |        |                                |
    //    |        |                                |
    //    |        |                                |
    //    -------------------------------------------
    //    |     MiscSpace                           |
    //    -------------------------------------------
    //

    // Then, add a space named "MiscSpace" whose height is 25% of the app height.
    // This will split the preexisting default dockspace "MainDockSpace" in two parts.
    HelloImGui::DockingSplit splitMainMisc;
    splitMainMisc.initialDock = "MainDockSpace";
    splitMainMisc.newDock = "MiscSpace";
    splitMainMisc.direction = ImGuiDir_Down;
    splitMainMisc.ratio = 0.25f;

    // Then, add a space to the left which occupies a column whose width is 25% of the app width
    HelloImGui::DockingSplit splitMainCommand;
    splitMainCommand.initialDock = "MainDockSpace";
    splitMainCommand.newDock = "CommandSpace";
    splitMainCommand.direction = ImGuiDir_Left;
    splitMainCommand.ratio = 0.25f;

    std::vector<HelloImGui::DockingSplit> splits {splitMainMisc, splitMainCommand};
    return splits;
}

std::vector<HelloImGui::DockingSplit> CreateAlternativeDockingSplits()
{
    //    Define alternative docking splits for the "Alternative Layout"
    //    ___________________________________________
    //    |                |                        |
    //    | Misc           |                        |
    //    | Space          |    MainDockSpace       |
    //    |                |                        |
    //    -------------------------------------------
    //    |                                         |
    //    |                                         |
    //    |     CommandSpace                        |
    //    |                                         |
    //    -------------------------------------------

    HelloImGui::DockingSplit splitMainCommand;
    splitMainCommand.initialDock = "MainDockSpace";
    splitMainCommand.newDock = "CommandSpace";
    splitMainCommand.direction = ImGuiDir_Down;
    splitMainCommand.ratio = 0.5f;

    HelloImGui::DockingSplit splitMainMisc;
    splitMainMisc.initialDock = "MainDockSpace";
    splitMainMisc.newDock = "MiscSpace";
    splitMainMisc.direction = ImGuiDir_Left;
    splitMainMisc.ratio = 0.5f;

    std::vector<HelloImGui::DockingSplit> splits {splitMainCommand, splitMainMisc};
    return splits;
}

//
// 2. Define the Dockable windows
//
std::vector<HelloImGui::DockableWindow> CreateDockableWindows(mtool::GuiContext& guiContext)
{
    HelloImGui::DockableWindow navagationWindow = mtool::CreateWindow("navagation", "CommandSpace", guiContext);
    HelloImGui::DockableWindow logsWindow = mtool::CreateWindow("logger", "MiscSpace", guiContext);
    HelloImGui::DockableWindow homeWindow = mtool::CreateWindow("home", "MainDockSpace", guiContext);
    HelloImGui::DockableWindow dataVisualizationWindow = mtool::CreateWindow("data_visualization", "MainDockSpace", guiContext);
    HelloImGui::DockableWindow canvasWindow = mtool::CreateWindow("canvas", "MainDockSpace", guiContext);
    // dataVisualizationWindow.imGuiWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
    // dataVisualizationWindow.windowSize = ImVec2(-1,-1);
    HelloImGui::DockableWindow dearImGuiDemoWindow = mtool::CreateWindow("Dear ImGui Demo", "MainDockSpace", guiContext);
    return std::vector<HelloImGui::DockableWindow>{
        navagationWindow,
        logsWindow,
        homeWindow,
        canvasWindow,
        dataVisualizationWindow,
        dearImGuiDemoWindow
    };
};

//
// 3. Define the layouts:
//        A layout is stored inside DockingParams, and stores the splits + the dockable windows.
//        Here, we provide the default layout, and two alternative layouts.
//
HelloImGui::DockingParams CreateDefaultLayout(mtool::GuiContext& guiContext)
{
    HelloImGui::DockingParams dockingParams;
    // dockingParams.layoutName = "Default"; // By default, the layout name is already "Default"
    dockingParams.dockingSplits = CreateDefaultDockingSplits();
    dockingParams.dockableWindows = CreateDockableWindows(guiContext);
    return dockingParams;
}

std::vector<HelloImGui::DockingParams> CreateAlternativeLayouts(mtool::GuiContext& guiContext)
{
    HelloImGui::DockingParams alternativeLayout;
    {
        alternativeLayout.layoutName = "Alternative Layout";
        alternativeLayout.dockingSplits = CreateAlternativeDockingSplits();
        alternativeLayout.dockableWindows = CreateDockableWindows(guiContext);
    }
    HelloImGui::DockingParams tabsLayout;
    {
        tabsLayout.layoutName = "Tabs Layout";
        tabsLayout.dockableWindows = CreateDockableWindows(guiContext);
        // Force all windows to be presented in the MainDockSpace
        for (auto& window: tabsLayout.dockableWindows)
            window.dockSpaceName = "MainDockSpace";
        // In "Tabs Layout", no split is created
        tabsLayout.dockingSplits = {};
    }
    return {alternativeLayout, tabsLayout};
};


//////////////////////////////////////////////////////////////////////////
//    main(): here, we simply fill RunnerParams, then run the application
//////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
    ChdirBesideAssetsFolder();

    //###############################################################################################
    // Part 1: Define the application state, fill the status and menu bars, and load additional font
    //###############################################################################################

    // Our application state
    mtool::GuiContext guiContext;
    guiContext.title_font = &gTitleFont;
    // Hello ImGui params (they hold the settings as well as the Gui callbacks)
    HelloImGui::RunnerParams runnerParams;

    // Note: by setting the window title, we also set the name of the ini files in which the settings for the user
    // layout will be stored: Docking_demo.ini
    runnerParams.appWindowParams.windowTitle = "mtool";

    runnerParams.imGuiWindowParams.menuAppTitle = "Docking App";
    runnerParams.appWindowParams.windowGeometry.size = {1000, 900};
    runnerParams.appWindowParams.restorePreviousGeometry = true;

    // Set LoadAdditionalFonts callback
    runnerParams.callbacks.LoadAdditionalFonts = LoadFonts;

    //
    // Status bar
    //
    // We use the default status bar of Hello ImGui
    runnerParams.imGuiWindowParams.showStatusBar = true;
    // Add custom widgets in the status bar
    runnerParams.callbacks.ShowStatus = [&guiContext]() { mtool::GuiStatusBar(guiContext); };
    // uncomment next line in order to hide the FPS in the status bar
    // runnerParams.imGuiWindowParams.showStatusFps = false;

    //
    // Menu bar
    //
    runnerParams.imGuiWindowParams.showMenuBar = true;          // We use the default menu of Hello ImGui
    // fill callbacks ShowMenuGui and ShowAppMenuItems, to add items to the default menu and to the App menu
    runnerParams.callbacks.ShowMenus = ShowMenuGui;
    runnerParams.callbacks.ShowAppMenuItems = ShowAppMenuItems;

    //
    // Load user settings at callbacks `PostInit` and save them at `BeforeExit`
    //
    runnerParams.callbacks.PostInit = [&guiContext]   { LoadMyAppSettings(guiContext);};
    runnerParams.callbacks.BeforeExit = [&guiContext] { SaveMyAppSettings(guiContext);};

    //###############################################################################################
    // Part 2: Define the application layout and windows
    //###############################################################################################

    // First, tell HelloImGui that we want full screen dock space (this will create "MainDockSpace")
    runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    // In this demo, we also demonstrate multiple viewports: you can drag windows outside out the main window in order to put their content into new native windows
    runnerParams.imGuiWindowParams.enableViewports = true;
    // Set the default layout (this contains the default DockingSplits and DockableWindows)
    runnerParams.dockingParams = CreateDefaultLayout(guiContext);
    // Add alternative layouts
    runnerParams.alternativeDockingLayouts = CreateAlternativeLayouts(guiContext);

    // uncomment the next line if you want to always start with the layout defined in the code
    //     (otherwise, modifications to the layout applied by the user layout will be remembered)
    // runnerParams.dockingParams.layoutCondition = HelloImGui::DockingLayoutCondition::ApplicationStart;
    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnerParams, addOnsParams);
    //###############################################################################################
    // Part 3: Run the app
    //###############################################################################################
    // HelloImGui::Run(runnerParams, addOnsParams); // Note: with ImGuiBundle, it is also possible to use ImmApp::Run(...)


    return 0;
}
