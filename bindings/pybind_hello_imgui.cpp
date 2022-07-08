#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>

#include "hello_imgui/hello_imgui.h"

namespace py = pybind11;

void py_init_module_hello_imgui(py::module& m);
void py_init_module_imgui(py::module& m);
void py_init_module_implot(py::module& m);

void py_init_module_lg_hello_imgui(py::module& m)
{
    auto module_imgui =  m.def_submodule("imgui");
    py_init_module_imgui(module_imgui);

    auto module_himgui =  m.def_submodule("hello_imgui");
    py_init_module_hello_imgui(module_himgui);

    auto module_implot =  m.def_submodule("implot");
    py_init_module_implot(module_implot);
}


void py_init_module_hello_imgui(py::module& m)
{
    using namespace HelloImGui;
    using namespace HelloImGui::internal;
    using namespace HelloImGui::ImGuiDefaultSettings;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  AUTOGENERATED CODE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // <litgen_pydef> // Autogenerated code below! Do not edit!
    ////////////////////    <generated_from:hello_imgui_amalgamation.h>    ////////////////////
    // <namespace HelloImGui>
    auto pyClassAssetFileData = py::class_<AssetFileData>
        (m, "AssetFileData", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("data", &AssetFileData::data, "")
        .def_readwrite("data_size", &AssetFileData::dataSize, "")
        ;


    m.def("load_asset_file_data",
        LoadAssetFileData, py::arg("asset_path"));

    m.def("free_asset_file_data",
        FreeAssetFileData, py::arg("asset_file_data"));

    m.def("asset_file_full_path",
        assetFileFullPath, py::arg("asset_relative_filename"));

    m.def("override_assets_folder",
        overrideAssetsFolder,
        py::arg("folder"),
        " Advanced: forces the assets folder location\n (when using this, automatic assets installation on mobile platforms may not work)");
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    m.def("image_from_asset",
        ImageFromAsset, py::arg("asset_path"), py::arg("size") = ImVec2(0, 0), py::arg("uv0") = ImVec2(0, 0), py::arg("uv1") = ImVec2(1,1), py::arg("tint_col") = ImVec4(1,1,1,1), py::arg("border_col") = ImVec4(0,0,0,0));

    m.def("image_button_from_asset",
        ImageButtonFromAsset, py::arg("asset_path"), py::arg("size") = ImVec2(0, 0), py::arg("uv0") = ImVec2(0, 0), py::arg("uv1") = ImVec2(1,1), py::arg("frame_padding") = -1, py::arg("bg_col") = ImVec4(0,0,0,0), py::arg("tint_col") = ImVec4(1,1,1,1));

    m.def("im_texture_id_from_asset",
        ImTextureIdFromAsset, py::arg("asset_path"));


    // <namespace internal>
    m.def("free_image_from_asset_map",
        Free_ImageFromAssetMap);
    // </namespace internal>
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    auto pyClassAppWindowParams = py::class_<AppWindowParams>
        (m, "AppWindowParams", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("window_title", &AppWindowParams::windowTitle, "")
        .def_readwrite("window_size", &AppWindowParams::windowSize, "")
        .def_readwrite("maximized", &AppWindowParams::maximized, "")
        .def_readwrite("full_screen", &AppWindowParams::fullScreen, "")
        .def_readwrite("window_position", &AppWindowParams::windowPosition, "")
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    py::enum_<DefaultImGuiWindowType>(m, "DefaultImGuiWindowType", py::arithmetic(), "")
        .value("provide_full_screen_window", DefaultImGuiWindowType::ProvideFullScreenWindow, "")
        .value("provide_full_screen_dock_space", DefaultImGuiWindowType::ProvideFullScreenDockSpace, "")
        .value("no_default_window", DefaultImGuiWindowType::NoDefaultWindow, "");


    auto pyClassImGuiWindowParams = py::class_<ImGuiWindowParams>
        (m, "ImGuiWindowParams", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("default_im_gui_window_type", &ImGuiWindowParams::defaultImGuiWindowType, "")
        .def_readwrite("background_color", &ImGuiWindowParams::backgroundColor, "")
        .def_readwrite("show_menu_bar", &ImGuiWindowParams::showMenuBar, "")
        .def_readwrite("show_menu_app", &ImGuiWindowParams::showMenu_App, "")
        .def_readwrite("show_menu_view", &ImGuiWindowParams::showMenu_View, "")
        .def_readwrite("show_status_bar", &ImGuiWindowParams::showStatusBar, "")
        .def_readwrite("show_status_fps", &ImGuiWindowParams::showStatus_Fps, "")
        .def_readwrite("config_windows_move_from_title_bar_only", &ImGuiWindowParams::configWindowsMoveFromTitleBarOnly, "")
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    m.def("load_font_ttf",
        LoadFontTTF, py::arg("font_filename"), py::arg("font_size"), py::arg("use_full_glyph_range") = false, py::arg("config") = ImFontConfig());

    m.def("load_font_ttf_with_font_awesome_icons",
        LoadFontTTF_WithFontAwesomeIcons, py::arg("font_filename"), py::arg("font_size"), py::arg("use_full_glyph_range") = false, py::arg("config_font") = ImFontConfig(), py::arg("config_icons") = ImFontConfig());

    m.def("merge_font_awesome_to_last_font",
        MergeFontAwesomeToLastFont, py::arg("font_size"), py::arg("config") = ImFontConfig());


    // <namespace ImGuiDefaultSettings>
    m.def("load_default_font_with_font_awesome_icons",
        LoadDefaultFont_WithFontAwesomeIcons);

    m.def("setup_default_im_gui_config",
        SetupDefaultImGuiConfig);

    m.def("setup_default_im_gui_style",
        SetupDefaultImGuiStyle);
    // </namespace ImGuiDefaultSettings>
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    auto pyClassMobileCallbacks = py::class_<MobileCallbacks>
        (m, "MobileCallbacks", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("on_destroy", &MobileCallbacks::OnDestroy, "")
        .def_readwrite("on_low_memory", &MobileCallbacks::OnLowMemory, "")
        .def_readwrite("on_pause", &MobileCallbacks::OnPause, "")
        .def_readwrite("on_resume", &MobileCallbacks::OnResume, "")
        ;


    auto pyClassRunnerCallbacks = py::class_<RunnerCallbacks>
        (m, "RunnerCallbacks", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("show_gui", &RunnerCallbacks::ShowGui, "")
        .def_readwrite("show_menus", &RunnerCallbacks::ShowMenus, "")
        .def_readwrite("show_status", &RunnerCallbacks::ShowStatus, "")
        .def_readwrite("post_init", &RunnerCallbacks::PostInit, "")
        .def_readwrite("before_exit", &RunnerCallbacks::BeforeExit, "")
        .def_readwrite("any_backend_event_callback", &RunnerCallbacks::AnyBackendEventCallback, "")
        .def_readwrite("load_additional_fonts", &RunnerCallbacks::LoadAdditionalFonts, "")
        .def_readwrite("setup_im_gui_config", &RunnerCallbacks::SetupImGuiConfig, "")
        .def_readwrite("setup_im_gui_style", &RunnerCallbacks::SetupImGuiStyle, "")
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    auto pyClassDockingSplit = py::class_<DockingSplit>
        (m, "DockingSplit", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("initial_dock", &DockingSplit::initialDock, "")
        .def_readwrite("new_dock", &DockingSplit::newDock, "")
        .def_readwrite("direction", &DockingSplit::direction, "")
        .def_readwrite("ratio", &DockingSplit::ratio, "")
        ;


    auto pyClassDockableWindow = py::class_<DockableWindow>
        (m, "DockableWindow", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("label", &DockableWindow::label, "")
        .def_readwrite("dock_space_name", &DockableWindow::dockSpaceName, "")
        .def_readwrite("gui_fonction", &DockableWindow::GuiFonction, "")
        .def_readwrite("is_visible", &DockableWindow::isVisible, "")
        .def_readwrite("can_be_closed", &DockableWindow::canBeClosed, "")
        .def_readwrite("call_begin_end", &DockableWindow::callBeginEnd, "")
        .def_readwrite("include_in_view_menu", &DockableWindow::includeInViewMenu, "")
        .def_readwrite("im_gui_window_flags", &DockableWindow::imGuiWindowFlags, "")
        .def_readwrite("window_size", &DockableWindow::windowSize, "")
        .def_readwrite("window_size_condition", &DockableWindow::windowSizeCondition, "")
        .def_readwrite("window_position", &DockableWindow::windowPosition, "")
        .def_readwrite("window_position_condition", &DockableWindow::windowPositionCondition, "")
        .def_readwrite("focus_window_at_next_frame", &DockableWindow::focusWindowAtNextFrame, "")
        ;


    auto pyClassDockingParams = py::class_<DockingParams>
        (m, "DockingParams", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("docking_splits", &DockingParams::dockingSplits, "")
        .def_readwrite("dockable_windows", &DockingParams::dockableWindows, "")
        .def_readwrite("reset_user_dock_layout", &DockingParams::resetUserDockLayout, "")
        .def_readwrite("was_dock_layout_applied", &DockingParams::wasDockLayoutApplied, "wasDockLayoutApplied is an internal variable")
        .def("dockable_window_of_name",
            &DockingParams::dockableWindowOfName, py::arg("name"))
        .def("focus_dockable_window",
            &DockingParams::focusDockableWindow, py::arg("window_name"))
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    auto pyClassBackendPointers = py::class_<BackendPointers>
        (m, "BackendPointers", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("glfw_window", &BackendPointers::glfwWindow, "")
        .def_readwrite("sdl_window", &BackendPointers::sdlWindow, "")
        .def_readwrite("sdl_gl_context", &BackendPointers::sdlGlContext, "")
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    auto pyClassRunnerParams = py::class_<RunnerParams>
        (m, "RunnerParams", "")
        .def(py::init<>()) // implicit default constructor
        .def_readwrite("callbacks", &RunnerParams::callbacks, "")
        .def_readwrite("app_window_params", &RunnerParams::appWindowParams, "")
        .def_readwrite("im_gui_window_params", &RunnerParams::imGuiWindowParams, "")
        .def_readwrite("docking_params", &RunnerParams::dockingParams, "")
        .def_readwrite("backend_pointers", &RunnerParams::backendPointers, "")
        .def_readwrite("app_shall_exit", &RunnerParams::appShallExit, "")
        .def_readwrite("fps", &RunnerParams::fps, "")
        ;
    // </namespace HelloImGui>


    // <namespace HelloImGui>
    m.def("run",
        py::overload_cast<RunnerParams &>(Run), py::arg("runner_params"));

    m.def("run",
        py::overload_cast<VoidFunction, ImVec2, std::string>(Run), py::arg("gui_fonction"), py::arg("window_size") = ImVec2(800.f, 600.f), py::arg("window_title") = "");
    // </namespace HelloImGui>
    ////////////////////    </generated_from:hello_imgui_amalgamation.h>    ////////////////////

    // </litgen_pydef> // Autogenerated code end
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  AUTOGENERATED CODE END !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
