# General project settings
project('vinnie', 'c',
  version : '0.1.1-alpha',
  license : 'MIT',
  default_options : ['warning_level=3',
                     'c_std=c11'])

# Disable a Clang warning generated by Check when compiling tests.
# https://github.com/libcheck/check/issues/58
disable_gnu_warning = []
if meson.get_compiler('c').get_id() == 'clang'
  disable_gnu_warning = ['-Wno-gnu-zero-variadic-macro-arguments']
endif

# Generate config.h file.
conf_data = configuration_data()
conf_data.set('version', meson.project_version())
conf_data.set('name', meson.project_name())
configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

# Also include current (i.e. build) directory to pick up generated config.h.
incdir = include_directories('include', '.')

# Miscellaneous documentation directory: $PREFIX/share/doc/vinnie
doc_install_dir = join_paths(get_option('datadir'),
  'doc',
  meson.project_name())

install_data(['README.md', 'LICENSE'], install_dir : doc_install_dir)

# Only build API docs if specified with `-Dwith_doc=true`. Print a warning if Doxygen fails.
docopt = get_option('with_doc')
if docopt
  r = run_command('scripts/doxy.sh')
  if r.returncode() != 0
    errortxt = r.stderr().strip()
    warning(errortxt)
  else
    #output = r.stdout().strip()
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
