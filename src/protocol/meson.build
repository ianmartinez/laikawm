# wayland-scanner is a tool which generates C headers and rigging for Wayland
# protocols, which are specified in XML. wlroots requires you to rig these up
# to your build system yourself and provide them in the include path.

# find wayland_scanner to generate C code from
wayland_protos = dependency('wayland-protocols')
wl_protocol_dir = wayland_protos.get_pkgconfig_variable('pkgdatadir')
wayland_scanner_dep = dependency('wayland-scanner', required: false, native: true)
if wayland_scanner_dep.found()
	wayland_scanner = find_program(
		wayland_scanner_dep.get_pkgconfig_variable('wayland_scanner'),
		native: true,
	)
else
	wayland_scanner = find_program('wayland-scanner', native: true)
endif

# protocols that need to be generated
protocols = [
	[wl_protocol_dir, 'stable/xdg-shell/xdg-shell.xml'],
	[wl_protocol_dir, 'unstable/xdg-decoration/xdg-decoration-unstable-v1.xml'],
	['', 'wlr-layer-shell-unstable-v1.xml']
]

# generate *.h and *.c files for protocols
wl_protos_src = []
wl_protos_headers = []
foreach p : protocols
	xml = join_paths(p)
	wl_protos_src += custom_target(
		xml.underscorify() + '_server_c',
		input: xml,
		output: '@BASENAME@-protocol.c',
		command: [wayland_scanner, 'private-code', '@INPUT@', '@OUTPUT@'],
	)
	wl_protos_headers += custom_target(
		xml.underscorify() + '_server_h',
		input: xml,
		output: '@BASENAME@-protocol.h',
		command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
	)
endforeach

lib_protocols = static_library(
	'client_protos',
	wl_protos_src + wl_protos_headers
) # for the include directory

client_protos = declare_dependency(
	link_with: lib_protocols,
	sources: wl_protos_headers,
)