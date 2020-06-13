project(
    'laikawm', 
    'c', 'cpp',
    version: '0.0.1',
    default_options: ['c_std=c11', 'cpp_std=c++17']
)

# Arguments for the compiler
build_args = [
    '-DWLR_USE_UNSTABLE',
    '-g'
]

# Include protocols directory
subdir('protocol')

# Add header files
inc = include_directories('include')

# Add implementation files
project_source_files = [
    # Util
    'util.cpp',

    # Events
    'events/cursor_events.cpp',
    'events/input_events.cpp',
    'events/keyboard_events.cpp',
    'events/layer_events.cpp',
    'events/output_events.cpp',
    'events/seat_events.cpp',
    'events/surface_events.cpp',
    'events/view_events.cpp',
    'events/xwayland_events.cpp',

    # Theme
    'theme/color.cpp',
    'theme/image.cpp',
    'theme/theme.cpp',
    
    # Devices
    'devices/keyboard.cpp',
    'devices/output.cpp',    
    
    # Other
    'render.cpp',
    'server.cpp',
    'view.cpp',
    'window_decoration.cpp',
    'laikawm.cpp'
]

# Project dependencies
project_dependencies = [
    dependency('wlroots'),
    dependency('wayland-client'),
    dependency('wayland-server'),
    dependency('xkbcommon'),
    dependency('gdk-pixbuf-2.0'),
    dependency('cairo'),
    dependency('pango'),
    dependency('pangocairo'),
    dependency('librsvg-2.0'),
    client_protos
]

# Set the project target
project_target = executable(
    meson.project_name(),
    project_source_files,
    dependencies: project_dependencies,
    include_directories: inc,  
    c_args: build_args,
    cpp_args: build_args
)
