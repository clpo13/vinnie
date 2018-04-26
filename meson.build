project('vinnie', 'c',
  version : '0.1.0',
  license : 'MIT',
  default_options : ['warning_level=3',
                     'c_std=c11'])

# Generate config.h file.
conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('name', meson.project_name())
configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

# Also include current directory to pick up generated config.h.
incdir = include_directories('include', '.')

# Miscellaneous documentation directory: $PREFIX/share/doc/vinnie
doc_install_dir = join_paths(get_option('datadir'),
  'doc',
  meson.project_name())

install_data(['README.md', 'LICENSE'], install_dir : doc_install_dir)

# Only build API docs if specified. Print a warning if doxygen isn't found.
docopt = get_option('with_doc')
if docopt
  r = run_command('scripts/doxy.sh')
  if r.returncode() != 0
    warning('Documentation was not built.')
    errortxt = r.stderr().strip()
  else
    output = r.stdout().strip()
    install_subdir('docs/html', install_dir : doc_install_dir)
  endif
endif

# Alternately, generate documentation manually with `ninja doc`.
run_target('doc', command : 'scripts/doxy.sh')

# If Check library is present, build the tests; otherwise, skip them.
check_dep = dependency('check', required : false)
if check_dep.found()
  subdir('test')
endif

# Main source code directory
subdir('src')
