#include <memory>
#include "Engine.h"
#include "ObjScene.h"

int main(int argc, char const *argv[])
{
    Geno3D::Engine game(800, 450, "Geno3D");
    std::shared_ptr<Geno3D::ObjScene> scene;
    if (argc > 2) {
        scene = std::make_shared<Geno3D::ObjScene>(argv[1], 15, -50, argv[2]);
    }
    else {
        scene = std::make_shared<Geno3D::ObjScene>(argv[1], 15, -50);
    }
    game.scene = std::move(scene);
    game.run();
    return 0;
}
