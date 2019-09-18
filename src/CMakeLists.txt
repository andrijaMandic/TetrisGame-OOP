add_executable(main main.cpp game.cpp board.cpp tetrimino.cpp score.cpp playstate.cpp gamestate.cpp
                     game.h board.h tetrimino.h score.h playstate.h gamestate.h)
target_link_libraries(main ${SFML_LIBRARIES})

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/Gasalt-Regular.ttf
                ${CMAKE_CURRENT_BINARY_DIR} )

