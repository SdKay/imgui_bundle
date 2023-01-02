from typing import List
from imgui_bundle import imgui, hello_imgui, imgui_md, imgui_toggle, ImVec2, immapp, ImVec4, icons_fontawesome
from imgui_bundle import imgui_command_palette as imcmd


@immapp.static(knob_value=0, knob_int_value=0)
def demo_knobs():
    static = demo_knobs
    from imgui_bundle import imgui_knobs

    imgui_md.render(
        """
# Knobs
  [imgui-knobs](https://github.com/altschuler/imgui-knobs) provides knobs for ImGui."""
    )
    knob_types = {
        "tick": imgui_knobs.ImGuiKnobVariant_.tick,
        "dot": imgui_knobs.ImGuiKnobVariant_.dot,
        "space": imgui_knobs.ImGuiKnobVariant_.space,
        "stepped": imgui_knobs.ImGuiKnobVariant_.stepped,
        "wiper": imgui_knobs.ImGuiKnobVariant_.wiper,
        "wiper_dot": imgui_knobs.ImGuiKnobVariant_.wiper_dot,
        "wiper_only": imgui_knobs.ImGuiKnobVariant_.wiper_only,
    }

    def show_float_knobs(knob_size: float):
        imgui.push_id(f"{knob_size}_float")
        for knob_typename, knob_type in knob_types.items():
            changed, static.knob_value = imgui_knobs.knob(
                knob_typename,
                p_value=static.knob_value,
                v_min=0.0,
                v_max=1.0,
                speed=0,
                variant=knob_type,
                steps=10,
                size=knob_size,
            )
            imgui.same_line()
        imgui.new_line()
        imgui.pop_id()

    def show_int_knobs(knob_size: float):
        imgui.push_id(f"{knob_size}_int")
        for knob_typename, knob_type in knob_types.items():
            changed, static.knob_int_value = imgui_knobs.knob_int(
                knob_typename,
                p_value=static.knob_int_value,
                v_min=0,
                v_max=10,
                speed=0,
                variant=knob_type,
                steps=10,
                size=knob_size,
            )
            imgui.same_line()
        imgui.new_line()
        imgui.pop_id()

    knobs_size_small = immapp.em_size() * 2.5
    knobs_size_big = knobs_size_small * 1.3

    imgui.begin_group()
    imgui.text("Some small knobs")
    show_float_knobs(knobs_size_small)
    imgui.end_group()

    imgui.same_line()

    imgui.begin_group()
    imgui.text("Some big knobs (int values)")
    show_int_knobs(knobs_size_big)
    imgui.end_group()


def demo_spinner():
    from imgui_bundle import imspinner

    imgui_md.render(
        """
# Spinners
  [imspinner](https://github.com/dalerank/imspinner) provides spinners for ImGui."""
    )

    color = imgui.ImColor(0.3, 0.5, 0.9, 1.0)
    imgui.text("spinner_moving_dots")
    imgui.same_line()
    imspinner.spinner_moving_dots("spinner_moving_dots", 3.0, color, 28.0)
    imgui.same_line()

    radius = imgui.get_font_size() / 1.8
    imgui.text("spinner_arc_rotation")
    imgui.same_line()
    imspinner.spinner_arc_rotation("spinner_arc_rotation", radius, 4.0, color)
    imgui.same_line()

    radius1 = imgui.get_font_size() / 2.5
    imgui.text("spinner_ang_triple")
    imgui.same_line()
    imspinner.spinner_ang_triple("spinner_ang_triple", radius1, radius1 * 1.5, radius1 * 2.0, 2.5, color, color, color)


@immapp.static(flag=True)
def demo_toggle():
    static = demo_toggle
    imgui_md.render(
        """
# Toggle Switch
  [imgui_toggle](https://github.com/cmdwtf/imgui_toggle) provides toggle switches for ImGui."""
    )

    _changed, static.flag = imgui_toggle.toggle("Default Toggle", static.flag)
    imgui.same_line()

    _changed, static.flag = imgui_toggle.toggle("Animated Toggle", static.flag, imgui_toggle.ToggleFlags_.animated)
    imgui.same_line()

    toggle_config = imgui_toggle.material_style()
    toggle_config.animation_duration = 0.4
    _changed, static.flag = imgui_toggle.toggle("Material Style (with slowed anim)", static.flag, config=toggle_config)

    imgui.same_line()
    _changed, static.flag = imgui_toggle.toggle("iOS style", static.flag, config=imgui_toggle.ios_style(size_scale=0.2))

    imgui.same_line()
    _changed, static.flag = imgui_toggle.toggle(
        "iOS style (light)", static.flag, config=imgui_toggle.ios_style(size_scale=0.2, light_mode=True)
    )


@immapp.static(
    open_file_dialog=None,
    open_file_multiselect=None,
    save_file_dialog=None,
    select_folder_dialog=None,
)
def demo_portable_file_dialogs():
    static = demo_portable_file_dialogs

    from imgui_bundle import portable_file_dialogs as pfd

    imgui.push_id("pfd")

    imgui_md.render(
        """
# Portable File Dialogs
 [portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs) provides native file dialogs    
    """
    )

    def log_result(what: str):
        hello_imgui.log(hello_imgui.LogLevel.info, what)

    def log_result_list(whats: List[str]):
        for what in whats:
            hello_imgui.log(hello_imgui.LogLevel.info, what)

    if imgui.button("Open file"):
        static.open_file_dialog = pfd.open_file("Select file")
    if static.open_file_dialog is not None and static.open_file_dialog.ready():
        log_result_list(static.open_file_dialog.result())
        static.open_file_dialog = None

    imgui.same_line()

    if imgui.button("Open file (multiselect)"):
        static.open_file_multiselect = pfd.open_file("Select file", options=pfd.opt.multiselect)
    if static.open_file_multiselect is not None and static.open_file_multiselect.ready():
        log_result_list(static.open_file_multiselect.result())
        static.open_file_multiselect = None

    imgui.same_line()

    if imgui.button("Save file"):
        static.save_file_dialog = pfd.save_file("Select file")
    if static.save_file_dialog is not None and static.save_file_dialog.ready():
        log_result(static.save_file_dialog.result())
        static.save_file_dialog = None

    imgui.same_line()

    if imgui.button("Select folder"):
        static.select_folder_dialog = pfd.select_folder("Select folder")
    if static.select_folder_dialog is not None and static.select_folder_dialog.ready():
        log_result(static.select_folder_dialog.result())
        static.select_folder_dialog = None

    imgui.pop_id()


@immapp.static(selected_filename="")
def demo_imfile_dialog():
    static = demo_imfile_dialog  # Access to static variable via static
    from imgui_bundle import im_file_dialog as ifd

    imgui_md.render(
        """
# ImFileDialog
 [ImFileDialog](https://github.com/pthom/ImFileDialog.git) provides file dialogs for ImGui, with images preview.  
 *Not (yet) adapted for High DPI resolution under windows*
    """
    )
    if imgui.button("Open file"):
        ifd.FileDialog.instance().open(
            "ShaderOpenDialog",
            "Open a shader",
            "Image file (*.png*.jpg*.jpeg*.bmp*.tga).png,.jpg,.jpeg,.bmp,.tga,.*",
            True,
        )
    imgui.same_line()
    if imgui.button("Open directory"):
        ifd.FileDialog.instance().open("DirectoryOpenDialog", "Open a directory", "")
    imgui.same_line()
    if imgui.button("Save file"):
        ifd.FileDialog.instance().save("ShaderSaveDialog", "Save a shader", "*.sprj .sprj")

    if len(static.selected_filename) > 0:
        imgui.text(f"Last file selection:\n  {static.selected_filename}")

    # file dialogs
    if ifd.FileDialog.instance().is_done("ShaderOpenDialog"):
        if ifd.FileDialog.instance().has_result():
            # get_results: plural form - ShaderOpenDialog supports multi-selection
            res = ifd.FileDialog.instance().get_results()
            filenames = [f.path() for f in res]
            static.selected_filename = "\n  ".join(filenames)

        ifd.FileDialog.instance().close()

    if ifd.FileDialog.instance().is_done("DirectoryOpenDialog"):
        if ifd.FileDialog.instance().has_result():
            static.selected_filename = ifd.FileDialog.instance().get_result().path()

        ifd.FileDialog.instance().close()

    if ifd.FileDialog.instance().is_done("ShaderSaveDialog"):
        if ifd.FileDialog.instance().has_result():
            static.selected_filename = ifd.FileDialog.instance().get_result().path()

        ifd.FileDialog.instance().close()


def _fake_log_provider() -> str:
    try:
        from fortune import fortune  # type: ignore

        message_provider = fortune
    except ImportError:

        def message_provider() -> str:
            import random

            return random.choice(
                [
                    """pip install fortune-python if you want real fortunes""",
                    """There's such a thing as too much point on a pencil.
               -- H. Allen Smith, "Let the Crabgrass Grow" """,
                    """Santa Claus is watching!""",
                    """I'll meet you... on the dark side of the moon...
                    -- Pink Floyd""",
                    """Money can't buy love, but it improves your bargaining position.
                                    -- Christopher Marlowe""",
                    """Those who in quarrels interpose, must often wipe a bloody nose.""",
                    """Everybody is somebody else's weirdo.
                                    -- Dykstra""",
                ]
            )

    return message_provider()


def demo_logger():
    imgui_md.render(
        """# Log Viewer
A simple Log viewer from [ImGuiAl](https://github.com/leiradel/ImGuiAl)
        """
    )
    if imgui.button("Log some messages"):
        hello_imgui.log(hello_imgui.LogLevel.debug, _fake_log_provider())
        hello_imgui.log(hello_imgui.LogLevel.info, _fake_log_provider())
        hello_imgui.log(hello_imgui.LogLevel.warning, _fake_log_provider())
        hello_imgui.log(hello_imgui.LogLevel.error, _fake_log_provider())

    # hello_imgui.log_gui will display the logs
    imgui.begin_child("Logs", ImVec2(0, 150))
    hello_imgui.log_gui()
    imgui.end_child()


@immapp.static(was_inited=False, show_command_palette=False, counter=0)
def demo_command_palette():
    static = demo_command_palette

    def init_command_palette():
        static.command_palette_context = imcmd.ContextWrapper()
        highlight_font_color = ImVec4(1.0, 0.0, 0.0, 1.0)
        imcmd.set_style_color(imcmd.ImCmdTextType.highlight, imgui.color_convert_float4_to_u32(highlight_font_color))
        # Add theme command: a two steps command, with initial callback + SubsequentCallback
        select_theme_cmd = imcmd.Command()
        select_theme_cmd.name = "Select theme"
        def select_theme_cmd_initial_cb():
            imcmd.prompt(["Classic", "Dark", "Light"])
        def select_theme_cmd_subsequent_cb(selected_option: int):
            if selected_option == 0:
                imgui.style_colors_classic()
            elif selected_option == 1:
                imgui.style_colors_dark()
            elif selected_option == 2:
                imgui.style_colors_light()
        select_theme_cmd.initial_callback = select_theme_cmd_initial_cb
        select_theme_cmd.subsequent_callback = select_theme_cmd_subsequent_cb
        imcmd.add_command(select_theme_cmd)

        # Simple command that increments a counter
        inc_cmd = imcmd.Command()
        inc_cmd.name = "increment counter";
        def inc_counter():
            static.counter += 1
        inc_cmd.initial_callback = inc_counter
        imcmd.add_command(inc_cmd)

    if not static.was_inited:
        init_command_palette()
        static.was_inited = True

    imgui_md.render(
        """
# Command Palette
[imgui-command-palette](https://github.com/hnOsmium0001/imgui-command-palette.git) provides a Sublime Text or VSCode style command palette in ImGui"""
    )

    io = imgui.get_io()

    if io.key_ctrl and io.key_shift and imgui.is_key_pressed(imgui.Key.p):
        static.show_command_palette = not static.show_command_palette

    if static.show_command_palette:
        static.show_command_palette = imcmd.command_palette_window("CommandPalette", True)

    imgui.new_line()
    imgui.text("Press Ctrl+Shift+P to bring up the command palette")
    imgui.new_line()
    imgui.text(f"{static.counter=}")


def demo_widgets():
    demo_portable_file_dialogs(); imgui.new_line()
    demo_imfile_dialog(); imgui.new_line()
    demo_knobs()
    demo_toggle(); imgui.new_line()
    demo_spinner()
    demo_command_palette(); imgui.new_line()
    demo_logger()


if __name__ == "__main__":
    from imgui_bundle import immapp

    immapp.run(demo_widgets, with_markdown=True, window_size=(1000, 800))  # type: ignore
