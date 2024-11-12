project('nibbler', ['cpp'], default_options : ['warning_level=2', 'cpp_std=c++17', 'optimization=3'])

add_project_arguments('-fsanitize=address,undefined', language: 'c')



subdir('core')
subdir('sfml')
subdir('raylib')
subdir('sdl')
subdir('audio')
