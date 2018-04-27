src = ['vinnie.c', 'vin.c']
exe = executable('vinnie', src,
  include_directories : incdir,
  install : true)
  
# Run the executable as a basic check of functionality.
test('basic', exe, args : ['-v'])
