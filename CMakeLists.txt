project(tutorial)

add_executable(tutorial tutorial.c)

install(TARGETS tutorial RUNTIME DESTINATION bin)
