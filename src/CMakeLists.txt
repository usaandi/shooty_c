add_executable(
    main
    main.cpp
    Point.cpp
    core/Game.cpp
    config/GameConfig.cpp
    nav/NavMesh.cpp
    nav/PathFinding.cpp
    core/scene/GameScene2D.cpp
    projectile/BaseProjectile.cpp
    config/SoldierTypeConfig.cpp
    renderer/SoldierRenderer.cpp
    renderer/ProjectileRenderer.cpp
    soldier/BaseSoldier.cpp
    soldier/PlayerSoldier.cpp
    soldier/AISoldier.cpp
    weapon/BaseWeapon.cpp
    weapon/assault_rifle/M16.cpp
    weapon/factory/WeaponFactory.cpp
    ui/Hud.cpp
)

target_include_directories(main 
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

# Link SFML libraries
target_link_libraries(main
    sfml-graphics
    sfml-window
    sfml-system
)