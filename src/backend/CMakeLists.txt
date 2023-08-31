set(SOURCE_FILES
        model/model.h model/model.cpp
        model/block.h model/block.cpp
        model/score_manager.h model/score_manager.cpp
        model/game_speed_manager.h model/game_speed_manager.cpp
        model/placed_squares.h model/placed_squares.cpp
        model/game_state_manager.cpp model/game_state_manager.h
        config.h
        square.h square.cpp
        block_factory.h block_factory.cpp
        block_movement_manager.h block_movement_manager.cpp
        random_generator.h
        coordinates.h coordinates.cpp
        rotation_coefficients.h rotation_coefficients.cpp
        speed_level.cpp speed_level.h
        log_manager.h
        rotation_coefficients_database.h
        common.h
        simulation_result.cpp simulation_result.h
        rotation_state.cpp rotation_state.h
        active_block_manager.cpp active_block_manager.h)

add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt${QT_VERSION_MAJOR}::Gui)
