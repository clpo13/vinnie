# Build the main executable and link it with libvin
exe = executable('vinnie', 'vinnie.c',
    include_directories : incdir,
    link_with : libvin,
    install : true)
  
# Run the executable as a basic check of functionality.
test('basic', exe, args : ['-v'])
